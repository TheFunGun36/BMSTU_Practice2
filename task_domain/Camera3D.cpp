#include "Camera3D.h"

Camera3D::Camera3D()
    : _height(50)
    , _distance(45) {
    _pos = Vector3D(-300, 0, 0);
    transform().set_position(_pos);
}

void Camera3D::look_at(const Vector3D& point) {
    transform().set_rotation(Quaternion(point - transform().position(), Angle()));
}

void Camera3D::rotate_horizontal(const Angle& angle) {
    _angles.z() += angle;
    transform().set_rotation(Quaternion(_angles));
    transform().set_position(transform().rotation().rotate_point(_pos));
}

void Camera3D::rotate_vertical(const Angle& angle) {
    _angles.y() += angle;
    transform().set_rotation(Quaternion(_angles));
    transform().set_position(transform().rotation().rotate_point(_pos));
}

real Camera3D::zoom_in(real value) {
    _pos.x() += value;
    return transform().position() += transform().rotation().forward() * value;
}

real Camera3D::zoom_out(real value) {
    _pos.x() -= value;
    return transform().position() += transform().rotation().backward() * value;
}
