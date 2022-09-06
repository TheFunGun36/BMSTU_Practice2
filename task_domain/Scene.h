#pragma once
#include "Camera3D.h"
#include "RubicsCube.h"
#include "Property.h"
#include "PointLight.h"
#include <unordered_map>

class Scene {
    using VisibleObjectsMap = std::unordered_map<ObjectId, std::shared_ptr<VisibleObject>>;
    using LightSourceMap = std::unordered_map<ObjectId, std::shared_ptr<PointLight>>;
    PROPERTY_RW(VisibleObjectsMap, objects);
    PROPERTY_RW(LightSourceMap, lights);
    PROPERTY_RW(std::shared_ptr<Camera3D>, camera);
    PROPERTY_RO(std::shared_ptr<RubicsCube>, cube);

public:
    Scene();
    Scene(const Scene&) = delete;
    Scene(Scene&&) = delete;

    bool load(const std::string& filename);

private:
    bool loadObject(const std::string& filename);
};

