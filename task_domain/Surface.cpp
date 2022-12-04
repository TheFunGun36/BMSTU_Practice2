#include "Surface.h"

Surface::Surface()
    : diffuse(1.0)
    , points({})
    , ignore_light(false)
    , owner(nullptr) {
}

Surface::Surface(const Vector3D* v1, const Vector3D* v2, const Vector3D* v3)
    : points({ v1, v2, v3 })
    , diffuse(1.0)
    , ignore_light(false)
    , owner(nullptr) {
    calculateNormal();
}

Surface::Surface(const Color& color, real diffuse) 
    : Surface() {
    this->color = color;
    this->diffuse = diffuse;
}

void Surface::calculateNormal() {
    Vector3D v1 = *points[0] - *points[1];
    Vector3D v2 = *points[0] - *points[2];
    normal = Vector3D::cross_product(v1, v2).normalized();
}

void Surface::calculateNormal(const Vector3D& point_inside) {
    calculateNormal();

    Vector3D to_point = *points[0] - point_inside;
    if (to_point * normal < 0)
        normal.flip();
}