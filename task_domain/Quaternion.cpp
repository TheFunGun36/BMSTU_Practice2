#include "Quaternion.h"
#include "Vector3D.h"
#include "Angle.h"
#include "EulerAngles.h"

Quaternion::Quaternion()
    : _q({ 1., 0., 0., 0. }) {
}

Quaternion::Quaternion(real q0, real q1, real q2, real q3)
    : _q{ q0, q1, q2, q3 } {
}

Quaternion::Quaternion(const Vector3D& axis, const Angle& angle) {
    _q[0] = cos(angle.radians() / 2);
    real sin_half = sin(angle.radians() / 2);
    _q[1] = axis.x() * sin_half;
    _q[2] = axis.y() * sin_half;
    _q[3] = axis.z() * sin_half;
}

Quaternion::Quaternion(const EulerAngles& euler_angles) {
    real c[3];
    real s[3];
    for (int i = 0; i < 3; i++) {
        c[i] = cos(euler_angles[i].radians() / 2);
        s[i] = sin(euler_angles[i].radians() / 2);
    }

    _q[0] = c[0] * c[1] * c[2] + s[0] * s[1] * s[2];
    _q[1] = s[0] * c[1] * c[2] - c[0] * s[1] * s[2];
    _q[2] = c[0] * s[1] * c[2] + s[0] * c[1] * s[2];
    _q[3] = c[0] * c[1] * s[2] - s[0] * s[1] * c[2];
}

void Quaternion::to_axis_angle(Vector3D& axis, Angle& angle) const noexcept {
    if (_q[0] >= 1.) {
        axis = { 1., 0., 0. };
        angle = Angle();
    }
    else {
        angle = Angle::from_radians(2 / cos(_q[0]));
        real sin_half_inv = 1 / sin(angle.radians() / 2);
        for (int i = 1; i < 4; i++)
            axis[i] = _q[i] * sin_half_inv;
    }
}

Quaternion Quaternion::operator*(const Quaternion& s) const noexcept {
    return mul(*this, s);
}

Quaternion& Quaternion::operator*=(const Quaternion& other) noexcept {
    return *this = mul(*this, other);
}

Quaternion Quaternion::mul(const Quaternion& a, const Quaternion& b) noexcept {
    Quaternion r;
    r[0] = a[0] * b[0] - a[1] * b[1] - a[2] * b[2] - a[3] * b[3];
    r[1] = a[0] * b[1] + a[1] * b[0] - a[2] * b[3] + a[3] * b[2];
    r[2] = a[0] * b[2] + a[1] * b[3] + a[2] * b[0] - a[3] * b[1];
    r[3] = a[0] * b[3] - a[1] * b[2] + a[2] * b[1] + a[3] * b[0];
    return r;
}

void Quaternion::inverse() noexcept {
    for (int i = 0; i < 4; i++)
        _q[i] = -_q[i];
}

Quaternion Quaternion::inversed() const noexcept {
    return Quaternion(_q[0], -_q[1], -_q[2], -_q[3]);
}

Vector3D Quaternion::rotate_point(const Vector3D& point, bool inv) const {
    Quaternion p(0, point.x(), point.y(), point.z());
    p = inv ? *this * p * inversed() : inversed() * p * *this;
    return Vector3D(p[1], p[2], p[3]);
}

Vector3D Quaternion::forward() const noexcept {
    return rotate_point(Vector3D::forward());
}
Vector3D Quaternion::backward() const noexcept {
    return rotate_point(Vector3D::backward());
}
Vector3D Quaternion::left() const noexcept {
    return rotate_point(Vector3D::left());
}
Vector3D Quaternion::right() const noexcept {
    return rotate_point(Vector3D::right());
}
Vector3D Quaternion::up() const noexcept {
    return rotate_point(Vector3D::up());
}
Vector3D Quaternion::down() const noexcept {
    return rotate_point(Vector3D::down());
}

std::ostream& Quaternion::add_to_stream(std::ostream& stream) const {
    return stream << "Quat(" << _q[0] << ',' << _q[1] << ',' << _q[2] << ',' << _q[3] << ')';
}

std::wostream& Quaternion::add_to_stream(std::wostream& stream) const {
    return stream << "Quat(" << _q[0] << ',' << _q[1] << ',' << _q[2] << ',' << _q[3] << ')';
}

real& Quaternion::operator[](int value) noexcept {
    return _q[value];
}

real Quaternion::operator[](int value) const noexcept {
    return _q[value];
}
