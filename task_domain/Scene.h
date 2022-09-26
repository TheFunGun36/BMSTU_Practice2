#pragma once
#include "Camera3D.h"
#include "RubicsCube.h"
#include "Property.h"
#include "PointLight.h"
#include <unordered_map>

struct Triangle;

class Scene {
    using VisibleObjectsMap = std::unordered_map<ObjectId, std::shared_ptr<VisibleObject>>;
    using LightSourceMap = std::unordered_map<ObjectId, std::shared_ptr<PointLight>>;
    PROPERTY_RO(bool, cache_valid);

public:
    Scene();
    ~Scene();
    Scene(const Scene&) = delete;
    Scene(Scene&&) = delete;

    void update_cache();

    const Triangle* cache() const noexcept;
    const Triangle* cache_end() const noexcept;

    const Camera3D& camera() const noexcept;
    const RubicsCube& cube() const noexcept;

    Camera3D& camera_ref() noexcept;
    RubicsCube& cube_ref() noexcept;

private:
    size_t calculate_cache_size() const noexcept;

    LightSourceMap _lights;
    std::shared_ptr<Camera3D> _camera;
    std::shared_ptr<RubicsCube> _cube;
    VisibleObjectsMap _objects;

    Triangle* _cache;
    Triangle* _cache_end;
};

