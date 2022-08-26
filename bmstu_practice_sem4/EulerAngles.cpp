#include "EulerAngles.h"

Angle& EulerAngles::operator[](int index) { return index == 0 ? _x : index == 1 ? _y : _z; }
const Angle& EulerAngles::operator[](int index) const { return index == 0 ? _x : index == 1 ? _y : _z; }

EulerAngles::EulerAngles(const Angle& x, const Angle& y, const Angle& z)
    : _x(x)
    , _y(y)
    , _z(z) {}

EulerAngles& EulerAngles::operator+=(const Angle& other) {
    for (int i = 0; i < 3; i++)
        this[i] += other;
    return *this;
}

EulerAngles& EulerAngles::operator-=(const Angle& other) {
    for (int i = 0; i < 3; i++)
        this[i] -= other;
    return *this;
}

EulerAngles& EulerAngles::operator*=(real value) {
    for (int i = 0; i < 3; i++)
        this[i] *= value;
    return *this;
}

EulerAngles& EulerAngles::operator/=(real value) {
    for (int i = 0; i < 3; i++)
        this[i] /= value;
    return *this;
}

EulerAngles& EulerAngles::operator+=(const EulerAngles& other) {
    for (int i = 0; i < 3; i++)
        this[i] += other[i];
    return *this;
}

EulerAngles& EulerAngles::operator-=(const EulerAngles& other) {
    for (int i = 0; i < 3; i++)
        this[i] -= other[i];
    return *this;
}

EulerAngles& EulerAngles::operator*=(const Vector3D& value) {
    for (int i = 0; i < 3; i++)
        this[i] *= value[i];
    return *this;
}

EulerAngles& EulerAngles::operator/=(const Vector3D& value) {
    for (int i = 0; i < 3; i++)
        this[i] /= value[i];
    return *this;
}

EulerAngles EulerAngles::operator+(const Angle& other) const {
    EulerAngles copy(*this);
    copy += other;
    return copy;
}

EulerAngles EulerAngles::operator-(const Angle& other) const {
    EulerAngles copy(*this);
    copy -= other;
    return copy;
}

EulerAngles EulerAngles::operator*(real value) const {
    EulerAngles copy(*this);
    copy *= value;
    return copy;
}

EulerAngles EulerAngles::operator/(real value) const {
    EulerAngles copy(*this);
    copy /= value;
    return copy;
}

EulerAngles EulerAngles::operator+(const EulerAngles& other) const {
    EulerAngles copy(*this);
    copy += other;
    return copy;
}

EulerAngles EulerAngles::operator-(const EulerAngles& other) const {
    EulerAngles copy(*this);
    copy -= other;
    return copy;
}

EulerAngles EulerAngles::operator*(const Vector3D& value) const {
    EulerAngles copy(*this);
    copy *= value;
    return copy;
}

EulerAngles EulerAngles::operator/(const Vector3D& value) const {
    EulerAngles copy(*this);
    copy /= value;
    return copy;
}

Vector3D EulerAngles::rotate_point(Vector3D point, bool reverse) const noexcept {
    Vector3D result = point;

    if (!reverse) {
        result.set_y(point.y() * x().cos() - point.z() * x().sin());
        result.set_z(point.y() * x().sin() + point.z() * x().cos());
    }
    else {
        result.set_x(point.x() * z().cos() - point.y() * z().sin());
        result.set_y(point.x() * z().sin() + point.y() * z().cos());
    }
    point = result;

    result.set_z(point.z() * y().cos() - point.x() * y().sin());
    result.set_x(point.z() * y().sin() + point.x() * y().cos());
    point = result;

    if (!reverse) {
        result.set_x(point.x() * z().cos() - point.y() * z().sin());
        result.set_y(point.x() * z().sin() + point.y() * z().cos());
    }
    else {
        result.set_y(point.y() * x().cos() - point.z() * x().sin());
        result.set_z(point.y() * x().sin() + point.z() * x().cos());
    }

    return result;
}

std::ostream& EulerAngles::add_to_stream(std::ostream& stream) const {
    return stream << "(" << _x << ", " << _y << ", " << _z << ")";
}

std::wostream& EulerAngles::add_to_stream(std::wostream& stream) const {
    return stream << L"(" << _x << L", " << _y << L", " << _z << L")";
}
