#pragma once
#include "Vector3D.h"
#include "EulerAngles.h"
#include "Property.h"

class Transform : public Printable {
    PROPERTY_RW(Vector3D, position);
    PROPERTY_RW(Vector3D, scale);
    PROPERTY_RW(EulerAngles, rotation);
public:
    Transform(const Transform& other) = default;
    Transform(Vector3D position = Vector3D(),
        EulerAngles rotation = EulerAngles(),
        Vector3D scale = Vector3D(1., 1., 1.));

    Vector3D point_to_local(Vector3D point) const noexcept;
    Vector3D point_to_global(Vector3D point) const noexcept;

    void translate(const Vector3D& value);
    void rotate(const EulerAngles& value);
    void scale(const Vector3D& value);

    void rotate(const EulerAngles& value, const Vector3D& center);
    void rotate_x(const Angle& value, const Vector3D& center);
    void rotate_y(const Angle& value, const Vector3D& center);
    void rotate_z(const Angle& value, const Vector3D& center);

protected:
    virtual std::ostream& add_to_stream(std::ostream& stream) const;
    virtual std::wostream& add_to_stream(std::wostream& stream) const;

private:
    Vector3D _position;
    EulerAngles _rotation;
    Vector3D _scale;
};