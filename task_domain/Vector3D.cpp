#include "Vector3D.h"
#include <sstream>

Vector3D::Vector3D() noexcept
    : _x(0)
    , _y(0)
    , _z(0) {}

Vector3D::Vector3D(real x, real y, real z) noexcept
    : _x(x)
    , _y(y)
    , _z(z) {}

real Vector3D::operator[](size_t index) const {
    return index == 0 ? _x : index == 1 ? _y : _z;
}

real& Vector3D::operator[](size_t index) {
    return index == 0 ? _x : index == 1 ? _y : _z;
}

Vector3D& Vector3D::operator=(const Vector3D& other) noexcept {
    _x = other._x;
    _y = other._y;
    _z = other._z;
    return *this;
}

Vector3D& Vector3D::operator+=(const Vector3D& other) noexcept {
    _x += other._x;
    _y += other._y;
    _z += other._z;
    return *this;
}

Vector3D& Vector3D::operator+=(real value) noexcept {
    _x += value;
    _y += value;
    _z += value;
    return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D& other) noexcept {
    return *this += -other;
}

Vector3D& Vector3D::operator-=(real value) noexcept {
    return *this += -value;
}

Vector3D& Vector3D::operator*=(real value) noexcept {
    _x *= value;
    _y *= value;
    _z *= value;
    return *this;
}

Vector3D& Vector3D::operator/=(real value) noexcept {
    _x /= value;
    _y /= value;
    _z /= value;
    return *this;
}

Vector3D Vector3D::operator+(const Vector3D& other) const noexcept {
    Vector3D result(*this);
    result += other;
    return result;
}

Vector3D Vector3D::operator+(real value) const noexcept {
    Vector3D result(*this);
    result += value;
    return result;
}

Vector3D Vector3D::operator-(const Vector3D& other) const noexcept {
    Vector3D result(*this);
    result -= other;
    return result;
}

Vector3D Vector3D::operator-(real value) const noexcept {
    Vector3D result(*this);
    result -= value;
    return result;
}

real Vector3D::operator*(const Vector3D& other) const noexcept {
    return Vector3D::dot_product(*this, other);
}

Vector3D Vector3D::operator*(real value) const noexcept {
    Vector3D result(*this);
    result *= value;
    return result;
}

Vector3D Vector3D::operator/(real value) const noexcept {
    Vector3D result(*this);
    result /= value;
    return result;
}

Vector3D Vector3D::operator-() const noexcept {
    return Vector3D(-_x, -_y, -_z);
}

bool Vector3D::operator==(const Vector3D& other) const noexcept {
    return real_eq(_x, other._x) && real_eq(_y, other._y) && real_eq(_z, other._z);
}

bool Vector3D::operator!=(const Vector3D& other) const noexcept {
    return !(*this == other);
}

Vector3D::operator bool() {
    return *this != Vector3D();
}

Vector3D Vector3D::normalized() const noexcept {
    return *this / length();
}

real Vector3D::length_squared() const noexcept {
    return _x * _x + _y * _y + _z * _z;
}

real Vector3D::length() const noexcept {
    return sqrt(length_squared());
}

void Vector3D::flip() noexcept {
    _x = -_x;
    _y = -_y;
    _z = -_z;
}

real Vector3D::dot_product(const Vector3D& v1, const Vector3D& v2) noexcept {
    return v1._x * v2._x + v1._y * v2._y + v1._z * v2._z;
}

Vector3D Vector3D::cross_product(const Vector3D& v1, const Vector3D& v2) noexcept {
    Vector3D result;
    result.set_x(v1._y * v2._z - v1._z * v2._y);
    result.set_y(v1._z * v2._x - v1._x * v2._z);
    result.set_z(v1._x * v2._y - v1._y * v2._x);
    return result;
}

Vector3D Vector3D::forward() {
    return Vector3D(1, 0, 0);
}

Vector3D Vector3D::backward() {
    return Vector3D(-1, 0, 0);
}

Vector3D Vector3D::left() {
    return Vector3D(0, 1, 0);
}

Vector3D Vector3D::right() {
    return Vector3D(0, -1, 0);
}

Vector3D Vector3D::up() {
    return Vector3D(0, 0, 1);
}

Vector3D Vector3D::down() {
    return Vector3D(0, 0, -1);
}

std::ostream& Vector3D::add_to_stream(std::ostream& stream) const {
    return stream << "(" << x() << ", " << y() << ", " << z() << ")";
}

std::wostream& Vector3D::add_to_stream(std::wostream& stream) const {
    return stream << L"(" << x() << L", " << y() << L", " << z() << L")";
}
