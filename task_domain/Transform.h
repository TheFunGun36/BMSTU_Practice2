#pragma once
#include "Vector3D.h"
#include "EulerAngles.h"
#include "Quaternion.h"
#include "Property.h"

class Transform : public Printable {
    PROPERTY_RW(Vector3D, position);
    PROPERTY_RW(Vector3D, scale);
    PROPERTY_RW(Quaternion, rotation);
public:
    Transform(const Transform& other) = default;
    Transform(Vector3D position = Vector3D(),
        EulerAngles rotation = EulerAngles(),
        Vector3D scale = Vector3D(1., 1., 1.));

    Vector3D point_to_local(Vector3D point) const noexcept;
    Vector3D point_to_global(Vector3D point) const noexcept;
    Vector3D vector_to_global(Vector3D vector) const noexcept;
    Vector3D vector_to_local(Vector3D vector) const noexcept;

    void translate(const Vector3D& value);
    void rotate_world(const EulerAngles& value);
    void rotate_world(const Quaternion& value);
    void rotate_local(const EulerAngles& value);
    void rotate_local(const Quaternion& value);
    void scale(const Vector3D& value);

protected:
    virtual std::ostream& add_to_stream(std::ostream& stream) const;
    virtual std::wostream& add_to_stream(std::wostream& stream) const;
};