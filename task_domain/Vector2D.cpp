#include "Vector2D.h"
#include "Vector3D.h"
#include <sstream>

Vector2D::Vector2D() noexcept
    : _x(0)
    , _y(0) {}

Vector2D::Vector2D(real x, real y) noexcept
    : _x(x)
    , _y(y) {}

real Vector2D::operator[](size_t index) const {
    return index == 0 ? _x : _y;
}

real& Vector2D::operator[](size_t index) {
    return index == 0 ? _x : _y;
}

Vector2D& Vector2D::operator=(const Vector2D& other) noexcept {
    _x = other._x;
    _y = other._y;
    return *this;
}

Vector2D& Vector2D::operator+=(const Vector2D& other) noexcept {
    _x += other._x;
    _y += other._y;
    return *this;
}

Vector2D& Vector2D::operator+=(real value) noexcept {
    _x += value;
    _y += value;
    return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& other) noexcept {
    return *this += -other;
}

Vector2D& Vector2D::operator-=(real value) noexcept {
    return *this += -value;
}

Vector2D& Vector2D::operator*=(real value) noexcept {
    _x *= value;
    _y *= value;
    return *this;
}

Vector2D& Vector2D::operator/=(real value) noexcept {
    _x /= value;
    _y /= value;
    return *this;
}

Vector2D Vector2D::operator+(const Vector2D& other) const noexcept {
    Vector2D result(*this);
    result += other;
    return result;
}

Vector2D Vector2D::operator+(real value) const noexcept {
    Vector2D result(*this);
    result += value;
    return result;
}

Vector2D Vector2D::operator-(const Vector2D& other) const noexcept {
    return *this + -other;
}

Vector2D Vector2D::operator-(real value) const noexcept {
    return *this + -value;
}

Vector2D Vector2D::operator*(real value) const noexcept {
    Vector2D result(*this);
    result *= value;
    return result;
}

Vector2D Vector2D::operator/(real value) const noexcept {
    Vector2D result(*this);
    result /= value;
    return result;
}

Vector2D Vector2D::operator-() const noexcept {
    return Vector2D(-_x, -_y);
}

bool Vector2D::operator==(const Vector2D& other) const noexcept {
    return real_eq(x(), other.x()) && real_eq(y(), other.y());
}

bool Vector2D::operator!=(const Vector2D& other) const noexcept {
    return !(*this == other);
}

Vector2D::operator bool() {
    return *this != Vector2D();
}

Vector2D Vector2D::normalized() const noexcept {
    return *this / length();
}

real Vector2D::length_squared() const noexcept {
    return _x * _x + _y * _y;
}

real Vector2D::length() const noexcept {
    return sqrt(length_squared());
}

void Vector2D::flip() noexcept {
    set_x(-_x);
    set_y(-_y);
}

real Vector2D::dot_product(Vector2D v1, Vector2D v2) {
    return v1.x() * v2.x() + v1.y() * v2.y();
}

Vector3D Vector2D::cross_product(Vector2D v1, Vector2D v2) {
    return Vector3D(0, 0, v1.x() * v2.y() - v1.y() * v2.x());
}

std::ostream& Vector2D::add_to_stream(std::ostream& stream) const {
    return stream << "(" << x() << ", " << y() << ")";
}

std::wostream& Vector2D::add_to_stream(std::wostream& stream) const {
    return stream << L"(" << x() << L", " << y() << L")";
}
