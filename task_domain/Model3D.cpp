#include "Model3D.h"

bool Model3D::add_surface(const Surface& surface) {
    this->surface().push_back(new Surface(surface));
    return true;
}

Model3D::~Model3D() {
    for (Surface* surface : surface())
        delete surface;
}
