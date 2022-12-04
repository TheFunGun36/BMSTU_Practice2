#pragma once
#include "Model3D.h"
class BmstuLogo : public Model3D {
public:
    BmstuLogo();

private:
    void make_shield(Surface surface, real scale, real z);
    void make_plane(Surface surface, real z);
    void make_plane_bg(Surface surface, real z);
    void add_shape(Surface surface, Vector3D* path, int count);
};

