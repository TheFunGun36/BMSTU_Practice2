#pragma once
#include "Real.h"
#include "Printable.h"

class Angle : public Printable {
public:
    Angle();

    static Angle from_degrees(real value);
    static Angle from_radians(real value);
    static real to_degrees(real value);
    static real to_radians(real value);
    static real optimize_degrees(real value);
    static real optimize_radians(real value);

    real degrees() const;
    real radians() const;
    void set_degrees(const real& value);
    void set_radians(const real& value);

    real cos() const;
    real sin() const;

    bool operator==(const Angle& other) const;
    bool operator!=(const Angle& other) const;

    Angle& operator=(const Angle& other);

    Angle& operator+=(const Angle& other);
    Angle& operator-=(const Angle& other);
    Angle& operator*=(real value);
    Angle& operator/=(real value);

    Angle operator+(const Angle& other) const;
    Angle operator-(const Angle& other) const;
    Angle operator*(real value) const;
    Angle operator/(real value) const;

    Angle operator-() const;

protected:
    virtual std::ostream& add_to_stream(std::ostream& stream) const override;
    virtual std::wostream& add_to_stream(std::wostream& stream) const override;

private:
    real _radians;
    real _cos;
    real _sin;
};
