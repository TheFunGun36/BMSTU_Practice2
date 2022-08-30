#include "Scene.h"

Scene::Scene()
    : _camera(std::make_shared<Camera3D>())
    , _cube(std::make_shared<RubicsCube>()) {
    _objects[_cube->id()] = _cube;
}

bool Scene::load(const std::string& filename) {
    // TODO: load Scene
    // File must contain info about all other scene objects.
    return false;
}

bool Scene::loadObject(const std::string& filename) {
    // TODO: loadObject
    return false;
}
