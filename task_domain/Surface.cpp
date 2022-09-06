#include "Surface.h"

Surface::Surface()
    : diffuse(1.0)
    , points({}) {
}

Surface::Surface(const Vector3D* v1, const Vector3D* v2, const Vector3D* v3)
    : points({ v1, v2, v3 }),
    diffuse(1.0) {
    calculateNormal();
}

Surface::Surface(const Color& color, real diffuse) {
    this->color = color;
    this->diffuse = diffuse;
}

void Surface::calculateNormal() {
    Vector3D v1 = *points[0] - *points[1];
    Vector3D v2 = *points[0] - *points[2];
    normal = Vector3D::cross_product(v1, v2).normalized();
}
