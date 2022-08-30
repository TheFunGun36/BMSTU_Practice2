#pragma once
#include "Vector3D.h"

struct Vertex {
    Vector3D pos;
    Vector3D normal;

    Vertex() = default;
    Vertex(Vector3D pos, Vector3D normal = Vector3D());
};

