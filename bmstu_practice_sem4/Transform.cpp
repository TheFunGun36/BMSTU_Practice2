#include "Transform.h"

Transform::Transform(Vector3D position, EulerAngles rotation, Vector3D scale)
    :_position(position), _rotation(rotation), _scale(scale) {}

Vector3D Transform::point_to_local(Vector3D point) const noexcept {
    point -= _position;
    for (int i = 0; i < 3; i++)
        point[i] /= _scale[i];
    point = _rotation.rotate_point(point, true);
    return point;
}

Vector3D Transform::point_to_global(Vector3D point) const noexcept {
    for (int i = 0; i < 3; i++)
        point[i] *= _scale[i];
    point = _rotation.rotate_point(point);
    point += _position;
    return point;
}

void Transform::translate(const Vector3D& value) {
    _position += value;
}

void Transform::rotate(const EulerAngles& value) {
    _rotation += value;
}

void Transform::rotate(const EulerAngles& value, const Vector3D& center) {
    rotate_x(value.x(), center);
    rotate_y(value.y(), center);
    rotate_z(value.z(), center);
}

void Transform::rotate_x(const Angle& value, const Vector3D& center) {
    Vector3D delta(_position - center);
    _position.set_y(center + delta.y() * value.cos() - delta.z() * value.sin());
    _position.set_z(center + delta.y() * value.sin() + delta.z() * value.cos());
    _rotation.x() += value;
}

void Transform::rotate_y(const Angle& value, const Vector3D& center) {
    Vector3D delta(_position - center);
    _position.set_x(center + delta.x() * value.cos() - delta.z() * value.sin());
    _position.set_z(center + delta.x() * value.sin() + delta.z() * value.cos());
    _rotation.y() += value;
}

void Transform::rotate_z(const Angle& value, const Vector3D& center) {
    Vector3D delta(_position - center);
    _position.set_x(delta.x() * value.cos() - delta.y() * value.sin());
    _position.set_y(delta.x() * value.sin() + delta.y() * value.cos());
    _rotation.z() += value;
}

void Transform::scale(const Vector3D& value) {
    _position.x() *= value.x();
    _position.y() *= value.y();
    _position.z() *= value.z();
}

std::ostream& Transform::add_to_stream(std::ostream& stream) const {
    return stream << "Transform(P:" << _position << ", R:" << _rotation << ", S:" << _scale << ")";
}

std::wostream& Transform::add_to_stream(std::wostream& stream) const {
    return stream << L"Transform(P:" << _position << L", R:" << _rotation << L", S:" << _scale << L")";
}
