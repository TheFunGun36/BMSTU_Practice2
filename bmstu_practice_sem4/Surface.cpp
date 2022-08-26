#include "Surface.h"

Surface::Surface()
    : diffuse(1.0)
    , points({nullptr, nullptr, nullptr}) {
}

Surface::Surface(const Vertex* v1, const Vertex* v2, const Vertex* v3)
    : points({ v1, v2, v3 }),
    diffuse(1.0) {
    calculateNormal();
}

void Surface::calculateNormal() {
    Vector3D v1 = points[0]->pos - points[1]->pos;
    Vector3D v2 = points[0]->pos - points[2]->pos;
    normal = Vector3D::cross_product(v1, v2).normalized();
    if (Vector3D::dot_product(normal, points[0]->normal) < 0.)
        normal.flip();
}
