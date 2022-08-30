#pragma once
#include "SceneObject.h"
#include "Surface.h"
#include <vector>

class VisibleObject : public SceneObject {
    PROPERTY_RW(std::vector<Surface*>, surface);

public:
    VisibleObject();
    virtual bool set_visible(bool visible) noexcept override;
};

