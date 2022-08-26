#pragma once
#include "Camera3D.h"
#include "RubicsCube.h"
#include "Renderer.h"
#include "Property.h"
#include <unordered_map>
#include <qpainter.h>

class Scene {
    using ObjectsMap = std::unordered_map<ObjectId, std::shared_ptr<SceneObject>>;
    PROPERTY_RW(ObjectsMap, objects);
    PROPERTY_RW(Camera3D, camera);
    PROPERTY_RW(std::shared_ptr<RubicsCube>, cube);
    PROPERTY_RO(std::shared_ptr<Renderer>, renderer);

public:
    Scene() = default;
    Scene(const Scene&) = delete;
    Scene(Scene&&) = delete;

    bool load(const QString& filename);

private:
    bool loadObject(const QString& filename);
};

