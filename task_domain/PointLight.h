#pragma once
#include "SceneObject.h"
class PointLight : public SceneObject {
    PROPERTY_RW(real, intensity);
    PROPERTY_RW(real, radius);
};

