#include "Scene.h"

Scene::Scene()
    : _camera(std::make_shared<Camera3D>())
    , _cube(std::make_shared<RubicsCube>()) {
}

bool Scene::load(const QString& filename) {
    // TODO: load Scene
    // File must contain info about all other scene objects.
    return false;
}

bool Scene::loadObject(const QString& filename) {
    // TODO: loadObject
    return false;
}
