#pragma once
#include "VisibleObject.h"
#include "Vertex.h"
#include "Surface.h"
#include <vector>

class Model3D : public VisibleObject {
    PROPERTY_RW(std::vector<Vertex>, vertex);

public:
    Model3D() = default;
    Model3D(const Model3D&) = delete;
    Model3D(Model3D&&) = delete;

    bool add_surface(const Surface& surface);

    ~Model3D();
};
