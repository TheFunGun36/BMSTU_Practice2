#pragma once
#include "SceneObject.h"

class Camera3D : public SceneObject {
    PROPERTY_RW(real, width);
    PROPERTY_RW(real, height);
    PROPERTY_RW(real, distance);

public:
    Camera3D() = default;
    Camera3D(const Camera3D&) = delete;
    Camera3D(Camera3D&&) = delete;
};

