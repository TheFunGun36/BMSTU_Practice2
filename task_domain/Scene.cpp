#include "Scene.h"
#include "Room.h"

Scene::Scene()
    : _camera(std::make_shared<Camera3D>())
    , _cube(std::make_shared<RubicsCube>()) {
    _objects[_cube->id()] = _cube;

    auto room = std::make_shared<Room>();
    _objects[room->id()] = room;

    auto red_cube = std::make_shared<CubeBordered>(
        Surface({ 200, 150, 150 }, 1.0),
        Surface({ 100, 50, 50 }, 1.0),
        Vector3D(100, 100, 100),
        Vector3D(10, 10, 10),
        Vector3D(150, 150, -25));

    _objects[red_cube->id()] = red_cube;
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
