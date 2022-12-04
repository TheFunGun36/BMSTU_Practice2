#include "Renderer.h"
#include "Camera3D.h"
#include "Vector2D.h"
#include "Scene.h"
#include "Triangle.h"
#include <qpainter.h>
#include <qimage.h>
#include <thread>
#include <stack>
#include <atomic>

Renderer::Renderer(const std::shared_ptr<Scene>& scene)
    : _scene(scene)
    , _no_hit_color(0, 127, 200)
    , _line_counter(0) {}

struct RenderData {
    const Transform& camtransform;
    real camera_distance;
    real pixel_size;
    real height_half;
    real width_half;
    Vector3D ray_start;

    int pixels_x;
    int pixels_y;

    RenderData(
        const Camera3D& camera,
        int pixels_x,
        int pixels_y)
        : camtransform(camera.transform()) {
        this->pixels_x = pixels_x;
        this->pixels_y = pixels_y;

        camera_distance = camera.distance();
        pixel_size = camera.height() / pixels_y;
        height_half = camera.height() / 2.;
        width_half = pixel_size * pixels_x / 2;
        ray_start = camera.transform().position();
    }
};

bool Renderer::render(QImage& image) {
    if (!_scene)
        return false;

    if (!_scene->cache_valid())
        _scene->update_cache();

    int threads_amount = std::thread::hardware_concurrency() - 1;
    if (threads_amount <= 0)
        threads_amount = 4;
    std::thread* threads = new std::thread[threads_amount];

    RenderData* rd = new RenderData(_scene->camera(), image.width(), image.height());

    _line_counter.store(0);
    for (int i = 0; i < threads_amount; ++i)
        threads[i] = std::thread(&Renderer::render_thread, this, std::ref(image), rd);

    for (int i = 0; i < threads_amount; i++)
        threads[i].join();

    delete[]threads;
    delete rd;

    return true;
}

void Renderer::render_thread(QImage& image, const RenderData* rd) {
    int i;
    uint8_t* line = new uint8_t[4 * image.width()];

    while ((i = _line_counter.fetch_add(1)) < rd->pixels_y) {


        for (int j = 0; j < rd->pixels_x; ++j) {
            Vector3D ray_point = {
                rd->camera_distance,
                rd->width_half - (j + 0.5) * rd->pixel_size,
                rd->height_half - (i + 0.5) * rd->pixel_size
            };
            ray_point = rd->camtransform.point_to_global(ray_point);
            Vector3D ray_direction = ray_point - rd->ray_start;

            Color color = calculate_pixel_color(rd->ray_start, ray_direction);

            int pixel = j << 2;
            line[pixel++] = uint8_t(color.b);
            line[pixel++] = uint8_t(color.g);
            line[pixel++] = uint8_t(color.r);
            line[pixel] = uint8_t(0xff);
        }

        memcpy(image.scanLine(i), line, image.bytesPerLine());
    }

    delete[]line;
}

bool Renderer::render_simple(QPixmap& pixmap) {
    if (!_scene)
        return false;

    int x[3];
    int y[3];
    real cam_dist = _scene->camera().distance() + _scene->camera().transform().position().x() * 0.5;
    real scaling = pixmap.height() / _scene->camera().height();
    QPainter qp(&pixmap);
    qp.fillRect(pixmap.rect(), Qt::white);
    qp.setPen(qRgb(0, 0, 0));

    if (!_scene->cache_valid())
        _scene->update_cache();

    for (const Triangle* ct = _scene->cache(); ct < _scene->cache_end(); ++ct) {
        Triangle t = *ct;
        t.to_local(_scene->camera().transform());

        for (int i = 0; i < 3; i++) {
            real k = -cam_dist / (-t.v[i].x() + cam_dist) * scaling;
            x[i] = k * t.v[i].y() + pixmap.width() / 2;
            y[i] = k * t.v[i].z() + pixmap.height() / 2;
        }

        qp.drawLine(x[0], y[0], x[1], y[1]);
        qp.drawLine(x[0], y[0], x[2], y[2]);
        qp.drawLine(x[1], y[1], x[2], y[2]);
    }

    return true;
}

Color Renderer::calculate_pixel_color(Vector3D source, Vector3D direction) {
    constexpr int hits_amount = 9;
    HitInfo hits[hits_amount];

    int i = 0;
    for (; i < hits_amount; i++) {
        hits[i] = throw_ray(source, direction);
        if (!hits[i].hit)
            break;

        source = hits[i].pos;
        direction -= (hits[i].triangle->normal * Vector3D::dot_product(direction, hits[i].triangle->normal) * 2.);
    }
    --i;
    Color result = i == (hits_amount - 1) ? hits[i].triangle->surface->color : _no_hit_color;
    for (; i >= 0; --i) {
        Color clr = hits[i].triangle->surface->color;
        if (!hits[i].triangle->surface->ignore_light) {
            real light = calculate_point_intensity(hits[i].pos, hits[i].triangle->normal);
            clr = Color::intensity(clr, light);
        }
        result = Color::blend(clr, result, hits[i].triangle->surface->diffuse);
    }

    return result;
}

HitInfo Renderer::throw_ray(const Vector3D& start, const Vector3D& direction) const {
    HitInfo result = {};
    result.direction = direction;
    result.distance = INFINITY;

    for (const Triangle* ct = _scene->cache(); ct < _scene->cache_end(); ++ct) {
        if (ct->normal * direction >= 1e-7)
            continue;

        Vector3D hit_pos;
        real distance = triangle_intersection(start, direction, ct, hit_pos);
        if (distance > 0 && distance < result.distance) {
            result.hit = true;
            result.pos = hit_pos;
            result.triangle = ct;
            result.distance = distance;
        }
    }

    return result;
}

real Renderer::triangle_intersection(
    const Vector3D& orig,
    const Vector3D& dir,
    const Triangle* triag,
    Vector3D& intersec) {

    // Алгоритм Моллера — Трумбора
    const real eps = 1e-7;

    // Easier naming for triangle verticies
    Vector3D e1 = triag->v[1] - triag->v[0];
    Vector3D e2 = triag->v[2] - triag->v[0];

    Vector3D p = Vector3D::cross_product(dir, e2);
    real det = Vector3D::dot_product(e1, p);
    if (det > -eps && det < eps)
        return -1;  // det = 0, ray is parallel to triangle

    real det_inv = 1.0 / det;
    Vector3D t = orig - triag->v[0];
    real u = det_inv * Vector3D::dot_product(t, p);
    if (u < -eps || u > 1.0 + eps)
        return -1;

    Vector3D q = Vector3D::cross_product(t, e1);
    real v = det_inv * Vector3D::dot_product(dir, q);
    if (v < -eps || u + v > 1.0 + eps)
        return -1;

    real t1 = det_inv * Vector3D::dot_product(e2, q);
    if (t1 <= eps)
        return -1;

    intersec = orig + dir * t1;
    return t1;
}

real Renderer::calculate_point_intensity(const Vector3D& point, const Vector3D& normal) const {
    real result = 0.;

    for (const auto& light_pair : _scene->lights()) {
        const auto& light = *light_pair.second;
        Vector3D dir = point - light.transform().position();
        real dst_sq = dir.length_squared();

        if (dst_sq > light.radius_sq() || normal * dir >= 1e-7)
            continue;

        HitInfo hit = throw_ray(light.transform().position(), dir);
        if (hit && hit.distance * hit.distance < dst_sq) {
            result += light.intensity() * (light.radius_sq() - dst_sq) / light.radius_sq();
        }
    }
    
    return result;
}