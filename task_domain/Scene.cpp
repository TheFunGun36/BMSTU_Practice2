#include "Scene.h"
#include "Room.h"
#include "Triangle.h"

Scene::Scene()
    : _cube(std::make_shared<RubicsCube>())
    , _camera(std::make_shared<Camera3D>())
    , _cache_valid(false) {
    _objects[_cube->id()] = _cube;

    auto room = std::make_shared<Room>();
    _objects[room->id()] = room;

    auto red_cube = std::make_shared<CubeBordered>(
        Surface({ 200, 150, 150 }, 1.0),
        Surface({ 100, 50, 50 }, 1.0),
        Vector3D(25, 25, 25),
        Vector3D(2, 2, 2),
        Vector3D(0, 70, 0));

    _objects[red_cube->id()] = red_cube;

    size_t cache_sz = calculate_cache_size();
    _cache = new Triangle[cache_sz];
    _cache_end = _cache + cache_sz;

    // Lights
    auto light = std::make_shared<PointLight>();
    light->transform().set_position({ 150, 150, 100 });
    light->set_radius_sq(200000.);
    light->set_intensity(1.5);
    _lights[light->id()] = light;

    light = std::make_shared<PointLight>();
    light->transform().set_position({ -150, -150, 60 });
    light->set_radius_sq(200000.);
    light->set_intensity(1.2);
    _lights[light->id()] = light;
}

Scene::~Scene() {
    delete[]_cache;
}

void Scene::update_cache() {
    Triangle* p = _cache;
    for (const auto& obj : _objects) {
        for (Surface* surface : obj.second->surface()) {
            const auto& t = surface->owner->transform();
            *p = Triangle(surface);
            p->to_global(t);
            p++;
        }
    }

    _cache_valid = true;
}

const Triangle* Scene::cache() const noexcept {
    return _cache;
}

const Triangle* Scene::cache_end() const noexcept {
    return _cache_end;
}

const RubicsCube& Scene::cube() const noexcept {
    return *_cube;
}

const Scene::LightSourceMap& Scene::lights() const noexcept {
    return _lights;
}

RubicsCube& Scene::cube_ref() noexcept {
    _cache_valid = false;
    return *_cube;
}

Camera3D& Scene::camera_ref() noexcept {
    _cache_valid = false;
    return *_camera;
}

const Camera3D& Scene::camera() const noexcept {
    return *_camera;
}

size_t Scene::calculate_cache_size() const noexcept {
    size_t result = 0;
    for (const auto& obj : _objects)
        result += obj.second->surface().size();
    return result;
}