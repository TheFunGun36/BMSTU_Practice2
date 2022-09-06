#pragma once
#include "Model3D.h"
#include "Surface.h"

class Cube : public Model3D {
public:
    Cube(Surface fill, Surface border, Vector3D s, Vector3D bs, Vector3D offset);
};

