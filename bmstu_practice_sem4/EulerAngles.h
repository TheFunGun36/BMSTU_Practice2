#pragma once
#include "Angle.h"
#include "Vector3D.h"
#include "Property.h"

class EulerAngles : public Printable {
    PROPERTY_RW(Angle, x);
    PROPERTY_RW(Angle, y);
    PROPERTY_RW(Angle, z);

public:
    EulerAngles(const Angle& x = Angle(), const Angle& y = Angle(), const Angle& z = Angle());

    const Angle& operator[](int index) const;
    Angle& operator[](int index);

    EulerAngles& operator+=(const Angle& other);
    EulerAngles& operator-=(const Angle& other);
    EulerAngles& operator*=(real value);
    EulerAngles& operator/=(real value);

    EulerAngles& operator+=(const EulerAngles& other);
    EulerAngles& operator-=(const EulerAngles& other);
    EulerAngles& operator*=(const Vector3D& value);
    EulerAngles& operator/=(const Vector3D& value);

    EulerAngles operator+(const Angle& other) const;
    EulerAngles operator-(const Angle& other) const;
    EulerAngles operator*(real value) const;
    EulerAngles operator/(real value) const;

    EulerAngles operator+(const EulerAngles& other) const;
    EulerAngles operator-(const EulerAngles& other) const;
    EulerAngles operator*(const Vector3D& value) const;
    EulerAngles operator/(const Vector3D& value) const;

    Vector3D rotate_point(Vector3D point, bool reverse = false) const noexcept;

protected:
    virtual std::ostream& add_to_stream(std::ostream& stream) const;
    virtual std::wostream& add_to_stream(std::wostream& stream) const;
};
