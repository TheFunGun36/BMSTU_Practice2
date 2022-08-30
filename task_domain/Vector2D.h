#pragma once
#include "Real.h"
#include "Printable.h"
#include "Property.h"

class Vector3D;

class Vector2D : public Printable {
    PROPERTY_RW(real, x);
    PROPERTY_RW(real, y);

public:
    Vector2D() noexcept;
    Vector2D(real x, real y) noexcept;
    Vector2D(const Vector2D& other) = default;
    ~Vector2D() = default;

    real operator[](size_t index) const;
    real& operator[](size_t index);

    Vector2D& operator=(const Vector2D& other) noexcept;

    Vector2D& operator+=(const Vector2D& other) noexcept;
    Vector2D& operator+=(real value) noexcept;
    Vector2D& operator-=(const Vector2D& other) noexcept;
    Vector2D& operator-=(real value) noexcept;
    Vector2D& operator*=(real value) noexcept;
    Vector2D& operator/=(real value) noexcept;

    Vector2D operator+(const Vector2D& other) const noexcept;
    Vector2D operator+(real value) const noexcept;
    Vector2D operator-(const Vector2D& other) const noexcept;
    Vector2D operator-(real value) const noexcept;
    Vector2D operator*(real value) const noexcept;
    Vector2D operator/(real value) const noexcept;

    Vector2D operator-() const noexcept;

    bool operator==(const Vector2D& other) const noexcept;
    bool operator!=(const Vector2D& other) const noexcept;
    operator bool();

    Vector2D normalized() const noexcept;
    real length_squared() const noexcept;
    real length() const noexcept;

    void flip() noexcept;

    static real dot_product(Vector2D v1, Vector2D v2);
    static Vector3D cross_product(Vector2D v1, Vector2D v2);

protected:
    virtual std::ostream& add_to_stream(std::ostream& stream) const override;
    virtual std::wostream& add_to_stream(std::wostream& stream) const override;
};