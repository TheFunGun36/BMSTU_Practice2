#pragma once
#include "Property.h"
#include "Real.h"
#include "Printable.h"
#include <array>

class Vector3D;
class Angle;
class EulerAngles;

class Quaternion : public Printable {
public:
    Quaternion();
    Quaternion(const Vector3D& axis, const Angle& angle);
    Quaternion(const EulerAngles& euler_angles);

    void to_axis_angle(Vector3D& axis, Angle& angle) const noexcept;

    Quaternion operator*(const Quaternion& other) const noexcept;
    Quaternion& operator*=(const Quaternion& other) noexcept;
    real& operator[](int value) noexcept;
    real operator[](int value) const noexcept;

    static Quaternion mul(const Quaternion& a, const Quaternion& b) noexcept;
    void inverse() noexcept;
    Quaternion inversed() const noexcept;

    Vector3D rotate_point(const Vector3D& point, bool inv = false) const;
    Vector3D forward() const noexcept;
    Vector3D backward() const noexcept;
    Vector3D left() const noexcept;
    Vector3D right() const noexcept;
    Vector3D up() const noexcept;
    Vector3D down() const noexcept;

protected:
    virtual std::ostream& add_to_stream(std::ostream& stream) const;
    virtual std::wostream& add_to_stream(std::wostream& stream) const;

private:
    Quaternion(real q0, real q1, real q2, real q3);
    std::array<real, 4> _q;
};

