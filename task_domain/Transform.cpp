#include "Transform.h"

Transform::Transform(Vector3D position, EulerAngles rotation, Vector3D scale)
    : _position(position), _rotation(rotation), _scale(scale) {}

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

Vector3D Transform::vector_to_global(Vector3D vector) const noexcept {
    return _rotation.rotate_point(vector);
}

Vector3D Transform::vector_to_local(Vector3D vector) const noexcept {
    return _rotation.rotate_point(vector, true);
}

void Transform::translate(const Vector3D& value) {
    _position += value;
}

void Transform::rotate_world(const EulerAngles& value) {
    _rotation = _rotation * Quaternion(value);
}

void Transform::rotate_world(const Quaternion& value) {
    _rotation = _rotation * value;
}

void Transform::rotate_local(const EulerAngles& value) {
    _rotation = Quaternion(value) * _rotation;
}

void Transform::rotate_local(const Quaternion& value) {
    _rotation = value * _rotation;
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
