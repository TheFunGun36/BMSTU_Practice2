﻿#include "Renderer.h"
#include "Camera3D.h"
#include "Vector2D.h"
#include "Scene.h"
#include <qpainter.h>
#include <qimage.h>
#include <thread>
#include <stack>

struct Triangle {
    Vector3D v[3];

    Triangle(const Surface& surface) {
        for (int i = 0; i < 3; ++i)
            v[i] = *surface.points[i];
    }

    void to_global(const Transform& t) {
        for (int i = 0; i < 3; i++)
            v[i] = t.point_to_global(v[i]);
    }

    void to_local(const Transform& t) {
        for (int i = 0; i < 3; i++)
            v[i] = t.point_to_local(v[i]);
    }
};

Renderer::Renderer(const std::shared_ptr<Scene>& scene)
    : _scene(scene)
    , _no_hit_color(0, 127, 200) {
}

struct RenderData {
    std::shared_ptr<const Camera3D> camera;
    real width_half;
    real height_half;
    real pixel_size;
};

bool Renderer::render(QImage& image) {
    if (!_scene)
        return false;

    int pixels_x = image.width();
    int pixels_y = image.height();

#ifndef _DEBUG
    const int threads_amount = 7;
    std::thread threads[threads_amount];
    int chunk = pixels_y / threads_amount;
    for (int i = 0; i < threads_amount; ++i) {
        threads[i] = std::thread(
            [this, pixels_x, &image](int yb, int ye) {
                render_part(image, 0, pixels_x, yb, ye);
            },
            i * chunk, (i + 1) * chunk);
    }
    render_part(image, 0, pixels_x, 7 * chunk, pixels_y);
    for (int i = 0; i < threads_amount; i++)
        threads[i].join();
#else
    render_part(image, 0, pixels_x, 0, pixels_y);
#endif

    return true;
}

bool Renderer::render_simple(QPixmap& pixmap) {
    if (!_scene)
        return false;

    int x[3];
    int y[3];
    real cam_dist = _scene->camera()->distance() + _scene->camera()->transform().position().x() * 0.5;
    real scaling = pixmap.height() / _scene->camera()->height();
    QPainter qp(&pixmap);
    qp.fillRect(pixmap.rect(), Qt::white);
    qp.setPen(qRgb(0, 0, 0));

    for (const auto& obj : _scene->objects()) {
        for (auto surf : obj.second->surface()) {
            Triangle triag(*surf);
            triag.to_global(surf->owner->transform());
            triag.to_local(_scene->camera()->transform());

            for (int i = 0; i < 3; i++) {
                real k = -cam_dist / (-triag.v[i].x() + cam_dist) * scaling;
                x[i] = k * triag.v[i].y() + pixmap.width() / 2;
                y[i] = k * triag.v[i].z() + pixmap.height() / 2;
            }

            qp.drawLine(x[0], y[0], x[1], y[1]);
            qp.drawLine(x[0], y[0], x[2], y[2]);
            qp.drawLine(x[1], y[1], x[2], y[2]);
        }
    }

    return true;
}

void Renderer::render_part(QImage& image, int xb, int xe, int yb, int ye) {
    std::shared_ptr<const Camera3D> camera = _scene->camera();

    real pixel_size = camera->height() / image.height();
    real height_half = camera->height() / 2.;
    real width_half = pixel_size * image.width() / 2;
    Vector3D ray_start = camera->transform().position();

    for (int i = yb; i < ye; i++) {
        for (int j = xb; j < xe; j++) {
            Vector3D ray_point = {
                camera->distance(),
                width_half - (j + 0.5) * pixel_size,
                height_half - (i + 0.5) * pixel_size
            };
            ray_point = camera->transform().point_to_global(ray_point);
            Vector3D ray_direction = ray_point - ray_start;

            Color color = calculate_surface_color(ray_start, ray_direction);

            image.setPixelColor(j, i, qRgb(color.r, color.g, color.b));
        }
    }
}

Color Renderer::calculate_surface_color(Vector3D source, Vector3D direction) {
    constexpr int hits_amount = 9;
    HitInfo hits[hits_amount];

    int i = 0;
    for (; i < hits_amount; i++) {
        hits[i] = throw_ray(source, direction);
        if (!hits[i].hit)
            break;

        source = hits[i].pos;
        direction = hits[i].bounce;
    }
    --i;
    Color result = _no_hit_color;
    for (; i >= 0; --i) {
        result = Color::blend(hits[i].surface->color, result, hits[i].surface->diffuse);
    }

    return result;
}

HitInfo Renderer::throw_ray(const Vector3D& start, const Vector3D& direction) const {
    HitInfo result = {};
    result.direction = direction;
    result.distance = INFINITY;
    Vector3D normal;
    real a;

    for (const auto& obj : _scene->objects()) {
        for (Surface* surface : obj.second->surface()) {
            normal = surface->owner->transform().point_to_global(surface->normal);
            if (normal * direction >= 0)
                continue;

            Triangle triangle(*surface);
            triangle.to_global(surface->owner->transform());

            Vector3D hit_pos;
            real distance = triangle_intersection(start, direction, triangle, hit_pos);
            if (distance > 0 && distance < result.distance) {
                result.hit = true;
                result.pos = hit_pos;
                result.surface = surface;
                result.distance = distance;
                result.normal = normal;
            }
        }
    }

    if (result)
        result.bounce = direction - (result.normal * Vector3D::dot_product(direction, result.normal) * 2.);

    return result;
}

real Renderer::triangle_intersection(
    const Vector3D& orig,
    const Vector3D& dir,
    const Triangle& triag,
    Vector3D& intersec) {

    // Алгоритм Моллера — Трумбора
    const real eps = 1e-14;

    // Easier naming for triangle verticies
    Vector3D e1 = triag.v[1] - triag.v[0];
    Vector3D e2 = triag.v[2] - triag.v[0];

    Vector3D p = Vector3D::cross_product(dir, e2);
    real det = Vector3D::dot_product(e1, p);
    if (det > -eps && det < eps)
        return -1;  // det = 0, ray is parallel to triangle

    real det_inv = 1.0 / det;
    Vector3D t = orig - triag.v[0];
    real u = det_inv * Vector3D::dot_product(t, p);
    if (u < 0.0 || u > 1.0)
        return -1;

    Vector3D q = Vector3D::cross_product(t, e1);
    real v = det_inv * Vector3D::dot_product(dir, q);
    if (v < 0.0 || u + v > 1.0)
        return -1;

    real t1 = det_inv * Vector3D::dot_product(e2, q);
    if (t1 <= eps)
        return -1;

    intersec = orig + dir * t1;
    return t1;
}
