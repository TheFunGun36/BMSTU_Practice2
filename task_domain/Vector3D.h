#pragma once
#include "Real.h"
#include "Printable.h"
#include "Property.h"

class Vector3D : public Printable {
    PROPERTY_RW(real, x);
    PROPERTY_RW(real, y);
    PROPERTY_RW(real, z);

public:
    Vector3D() noexcept;
    Vector3D(real x, real y, real z) noexcept;
    Vector3D(const Vector3D& other) = default;
    ~Vector3D() = default;

    real operator[](size_t index) const;
    real& operator[](size_t index);

    Vector3D& operator=(const Vector3D& other) noexcept;

    Vector3D& operator+=(const Vector3D& other) noexcept;
    Vector3D& operator+=(real value) noexcept;
    Vector3D& operator-=(const Vector3D& other) noexcept;
    Vector3D& operator-=(real value) noexcept;
    Vector3D& operator*=(real value) noexcept;
    Vector3D& operator/=(real value) noexcept;

    Vector3D operator+(const Vector3D& other) const noexcept;
    Vector3D operator+(real value) const noexcept;
    Vector3D operator-(const Vector3D& other) const noexcept;
    Vector3D operator-(real value) const noexcept;
    real operator*(const Vector3D& other) const noexcept;
    Vector3D operator*(real value) const noexcept;
    Vector3D operator/(real value) const noexcept;

    Vector3D operator-() const noexcept;

    bool operator==(const Vector3D& other) const noexcept;
    bool operator!=(const Vector3D& other) const noexcept;
    operator bool();

    Vector3D normalized() const noexcept;
    real length_squared() const noexcept;
    real length() const noexcept;

    void flip() noexcept;

    static real dot_product(const Vector3D& v1, const Vector3D& v2) noexcept;
    static Vector3D cross_product(const Vector3D& v1, const Vector3D& v2) noexcept;

    static Vector3D forward();   // positive X direction
    static Vector3D backward();  // negative X direction
    static Vector3D left();      // positive Y direction
    static Vector3D right();     // negative Y direction
    static Vector3D up();        // positive Z direction
    static Vector3D down();      // negative Z direction

protected:
    virtual std::ostream& add_to_stream(std::ostream& stream) const override;
    virtual std::wostream& add_to_stream(std::wostream& stream) const override;
};

