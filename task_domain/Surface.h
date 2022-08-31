#pragma once
#include "Vertex.h"
#include "Color.h"
#include <array>

class VisibleObject;

struct Surface {
    VisibleObject* owner;
    Vector3D normal;
    real diffuse;
    Color color;
    std::array<const Vertex*, 3> points;

    Surface();
    Surface(const Vertex* v1, const Vertex* v2, const Vertex* v3);
    void calculateNormal();
};

