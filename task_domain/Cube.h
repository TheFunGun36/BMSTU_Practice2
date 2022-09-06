#pragma once
#include "Model3D.h"
class Cube : public Model3D {
public:
    Cube(Surface surface, Vector3D size, Vector3D offset);
    void invert_normals();

protected:
    Cube(Surface surface, Vector3D size, Vector3D offset, int extra_verticies);
};

