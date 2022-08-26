#include "Scene.h"

bool Scene::load(const QString& filename) {
    // TODO: load Scene
    return false;
}

const std::shared_ptr<Renderer>& Scene::renderer() noexcept {
    return _renderer;
}

bool Scene::loadObject(const QString& filename) {
    // TODO: loadObject
    return false;
}
