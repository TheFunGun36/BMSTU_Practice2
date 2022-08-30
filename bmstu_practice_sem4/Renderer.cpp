#include "Renderer.h"
#include "Camera3D.h"
#include "Vector2D.h"
#include "Scene.h"
#include <qpainter.h>
#include <qimage.h>

Renderer::Renderer(const std::shared_ptr<Scene>& scene)
    : _scene(scene)
    , _hit_count(3)
    , _no_hit_color(0, 127, 200) {}

bool Renderer::render(QImage& image) {
    if (!_scene)
        return false;

    std::shared_ptr<const Camera3D> camera = _scene->camera();

    real pixel_size = camera->height() / image.height();
    real height_half = camera->height() / 2.;
    real width_half = pixel_size * image.width();
    Vector3D ray_start = camera->transform().position();
    HitInfo* hit_buffer = new HitInfo[_hit_count];

    for (int i = 0; i < image.width(); i++) {
        for (int j = 0; j < image.height(); j++) {
            Vector3D ray_point = {
                camera->distance(),
                width_half - (i + 0.5) * pixel_size,
                height_half - (j + 0.5) * pixel_size
            };
            ray_point = camera->transform().point_to_global(ray_point);
            Vector3D ray_direction = ray_point - ray_start;
            HitInfo hit = throw_ray(ray_point, ray_direction);

            Color color = hit ? calculate_surface_color(hit, hit_buffer) : _no_hit_color;

            image.setPixelColor(i, j, qRgb(color.r, color.g, color.b));
        }
    }
    return true;
}

Color Renderer::calculate_surface_color(const HitInfo& hit_info, HitInfo* buffer) {
    assert(_hit_count > 0);
    buffer[0] = hit_info;

    int i;
    for (i = 0; i < _hit_count - 1 && buffer[i].hit && buffer[i].surface->diffuse < 1.0; ++i) {
        Vector3D ray = buffer[i].direction;
        Vector3D normal = buffer[i].surface->normal;
        Vector3D bounce = ray - 2 * (ray * normal) * normal;
        buffer[i + 1] = throw_ray(buffer[i].pos, bounce);
    }

    Color result = _no_hit_color;
    while (i >= 0)
        result = Color::blend(buffer[--i].surface->color, result, buffer[--i].surface->diffuse);

    return result;
}

HitInfo Renderer::throw_ray(const Vector3D& start, const Vector3D& direction) {
    HitInfo result = {};
    result.direction = direction;
    //real distance_squared
    for (const auto& obj : _scene->objects()) {
        if (obj.second->visible()) {
            for (Surface* surface : obj.second->surface()) {
                Vector3D hit_pos;
                if (triangle_intersection(start, direction, *surface, hit_pos)) {
                    real distance_squared = (hit_pos - start).length_squared();
                    if (distance_squared < result.distance_squared) {
                        result.hit = true;
                        result.pos = hit_pos;
                        result.surface = surface;
                        result.distance_squared = distance_squared;
                    }
                }
            }
        }
    }

    return result;
}

bool Renderer::triangle_intersection(
    const Vector3D& orig,
    const Vector3D& dir,
    const Surface& surface,
    Vector3D& intersec) {

    // Алгоритм Моллера — Трумбора
    const real eps = 1e-7;

    // Easier naming for triangle verticies
    Vector3D vertex0 = surface.points[0]->pos;
    Vector3D vertex1 = surface.points[1]->pos;
    Vector3D vertex2 = surface.points[2]->pos;
    Vector3D edge1 = vertex1 - vertex0;
    Vector3D edge2 = vertex2 - vertex0;

    Vector3D h = Vector3D::cross_product(dir, edge2);
    real a = Vector3D::dot_product(edge1, h);
    if (a > -eps && a < eps)
        return false;  // a = 0, ray is parallel to triangle

    real f = 1.0 / a;
    Vector3D s = dir - vertex0;
    real u = f * Vector3D::dot_product(s, h);
    if (u < 0.0 || u > 1.0)
        return false;

    Vector3D q = Vector3D::cross_product(s, edge1);
    real v = f * Vector3D::dot_product(dir, q);
    if (v < 0.0 || u + v > 1.0)
        return false;

    real t = f * Vector3D::dot_product(edge2, q);
    if (t <= eps)
        return false;

    intersec = orig + dir * t;
    return true;
}
