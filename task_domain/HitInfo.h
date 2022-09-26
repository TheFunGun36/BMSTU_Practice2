#pragma once
#include "Property.h"
#include "Vector3D.h"
#include "Surface.h"
#include "VisibleObject.h"

struct Triangle;

struct HitInfo {
    bool hit;
    Vector3D pos;
    Vector3D direction;
    Vector3D bounce;
    const Triangle* triangle;
    real distance;

    operator bool() { return hit; }
};

