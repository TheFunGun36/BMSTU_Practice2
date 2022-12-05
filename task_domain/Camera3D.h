#pragma once
#include "SceneObject.h"

class Camera3D : public SceneObject {
    PROPERTY_RW(real, height);
    PROPERTY_RW(real, distance);

public:
    Camera3D();
    Camera3D(const Camera3D&) = delete;
    Camera3D(Camera3D&&) = delete;

    void look_at(const Vector3D& point);
    void rotate_horizontal(const Angle& angle);
    void rotate_vertical(const Angle& angle);
    real zoom_in(real value);
    real zoom_out(real value);
    void reset();

private:
    EulerAngles _angles;
    Vector3D _pos;
};

