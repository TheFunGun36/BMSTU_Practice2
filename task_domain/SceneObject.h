#pragma once
#include "Vector3D.h"
#include "Transform.h"

class TransformAction;
using ObjectId = size_t;

class SceneObject {
public:
    SceneObject();
    SceneObject(const SceneObject& other) = delete;
    SceneObject(SceneObject&& other) = delete;
    virtual ~SceneObject() = default;

    virtual bool visible() const noexcept;
    virtual ObjectId id() const noexcept;
    virtual const Transform& transform() const noexcept;

    virtual Transform& transform() noexcept;
    virtual bool set_visible(bool visible) noexcept;

protected:
    bool _visible;

private:
    static ObjectId generateId();

    ObjectId _id;
    Transform _transform;
};
