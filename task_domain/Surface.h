#pragma once
#include "Color.h"
#include "Vector3D.h"
#include <array>

class VisibleObject;

struct Surface {
    VisibleObject* owner;
    Vector3D normal;
    real diffuse;
    Color color;
    bool ignore_light;
    std::array<const Vector3D*, 3> points;

    Surface();
    Surface(const Vector3D* v1, const Vector3D* v2, const Vector3D* v3);
    Surface(const Color& color, real diffuse);
    void calculateNormal();
    void calculateNormal(const Vector3D& point_inside);
};

