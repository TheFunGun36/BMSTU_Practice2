#include "SceneObject.h"

SceneObject::SceneObject()
    : _visible(false)
    , _transform() {
    _id = generateId();
}

bool SceneObject::visible() const noexcept {
    return _visible;
}

ObjectId SceneObject::id() const noexcept {
    return _id;
}

const Transform& SceneObject::transform() const noexcept {
    return _transform;
}

Transform& SceneObject::transform() noexcept {
    return _transform;
}

bool SceneObject::set_visible(bool _visible) noexcept {
    return false;
}

ObjectId SceneObject::generateId() {
    static ObjectId id = 0;
    return id++;
}
