#pragma once
#include "Cube.h"
#include "Surface.h"

class CubeBordered : public Cube {
public:
    CubeBordered(Surface fill, Surface border, Vector3D s, Vector3D bs, Vector3D offset);
};

