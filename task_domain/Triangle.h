#pragma once
#include "Vector3D.h"
#include "Surface.h"
#include "Transform.h"

struct Triangle {
    const Surface* surface;
    Vector3D v[3];
    Vector3D normal;

    Triangle() = default;

    Triangle(const Surface* surface) {
        for (int i = 0; i < 3; ++i)
            v[i] = *surface->points[i];
        normal = surface->normal;
        this->surface = surface;
    }

    void to_global(const Transform& t) {
        for (int i = 0; i < 3; i++)
            v[i] = t.point_to_global(v[i]);
        normal = t.point_to_global(normal);
    }

    void to_local(const Transform& t) {
        for (int i = 0; i < 3; i++)
            v[i] = t.point_to_local(v[i]);
        normal = t.point_to_local(normal);
    }
};

