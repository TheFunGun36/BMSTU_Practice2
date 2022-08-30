#pragma once
#include "Property.h"
#include "Vector3D.h"
#include "Surface.h"

struct HitInfo {
    bool hit;
    Vector3D pos;
    Vector3D direction;
    Surface* surface;
    real distance_squared;

    operator bool() { return hit; }
};

