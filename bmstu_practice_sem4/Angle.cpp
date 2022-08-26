#include "Angle.h"
#define M_PI 3.14159265358979323846

Angle::Angle()
    : _radians(0.)
    , _sin(0.)
    , _cos(1.) {}

Angle Angle::from_degrees(real value) {
    Angle a;
    a.set_degrees(value);
    return a;
}

Angle Angle::from_radians(real value) {
    Angle a;
    a.set_radians(value);
    return a;
}

real Angle::to_degrees(real value) {
    return value * 180 / M_PI;
}

real Angle::to_radians(real value) {
    return value * M_PI / 180;
}

real Angle::optimize_degrees(real value) {
    return fmod(value, 360.) + 360. * (value < 0.);
}

real Angle::optimize_radians(real value) {
    constexpr real pi2 = M_PI * 2;
    return fmod(value, pi2) + pi2 * (value < 0.);
}

real Angle::degrees() const {
    return to_degrees(_radians);
}

real Angle::radians() const {
    return _radians;
}

void Angle::set_degrees(const real& value) {
    _radians = optimize_radians(to_radians(value));
    _sin = std::sin(_radians);
    _cos = std::cos(_radians);
}

void Angle::set_radians(const real& value) {
    _radians = optimize_radians(value);
    _sin = std::sin(_radians);
    _cos = std::cos(_radians);
}

real Angle::cos() const {
    return _cos;
}

real Angle::sin() const {
    return _sin;
}

bool Angle::operator==(const Angle& other) const {
    return real_eq(_radians, other._radians);
}

bool Angle::operator!=(const Angle& other) const {
    return !(*this == other);
}

Angle& Angle::operator=(const Angle& other) {
    _radians = other._radians;
    _cos = other._cos;
    _sin = other._sin;
    return *this;
}

Angle& Angle::operator+=(const Angle& other) {
    set_radians(_radians + other._radians);
    return *this;
}

Angle& Angle::operator-=(const Angle& other) {
    set_radians(_radians - other._radians);
    return *this;
}

Angle& Angle::operator*=(real value) {
    set_radians(_radians * value);
    return *this;
}

Angle& Angle::operator/=(real value) {
    set_radians(_radians / value);
    return *this;
}

Angle Angle::operator+(const Angle& other) const {
    Angle copy(*this);
    copy += other;
    return copy;
}

Angle Angle::operator-(const Angle& other) const {
    Angle copy(*this);
    copy -= other;
    return copy;
}

Angle Angle::operator*(real value) const {
    Angle copy(*this);
    copy *= value;
    return copy;
}

Angle Angle::operator/(real value) const {
    Angle copy(*this);
    copy /= value;
    return copy;
}

std::ostream& Angle::add_to_stream(std::ostream& stream) const {
    return stream << "radians(" << radians() << ")";
}

std::wostream& Angle::add_to_stream(std::wostream& stream) const {
    return stream << L"radians(" << radians() << L")";
}