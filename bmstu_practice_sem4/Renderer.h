#pragma once
#include <memory>
#include "HitInfo.h"

class Scene;
class QPainter;
class QPixmap;
class QImage;
class Camera3D;
struct Triangle;

class Renderer {
    PROPERTY_RW(Color, no_hit_color);

public:
    Renderer(const std::shared_ptr<Scene>& scene);

    bool render(QImage& image);
    bool render_simple(QPixmap& pixmap);

private:

    void render_part(QImage& image, int xb, int xe, int yb, int ye);
    Color calculate_pixel_color(Vector3D source, Vector3D direction);
    HitInfo throw_ray(const Vector3D& start, const Vector3D& direction) const;
    static real triangle_intersection(
        const Vector3D& orig,
        const Vector3D& dir,
        const Triangle& triag,
        Vector3D& intersec);

    std::shared_ptr<Scene> _scene;
};

