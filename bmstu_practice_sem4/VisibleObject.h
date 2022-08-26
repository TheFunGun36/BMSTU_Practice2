#pragma once
#include "SceneObject.h"
class VisibleObject : public SceneObject {
public:
    VisibleObject();
    virtual bool set_visible(bool visible) noexcept override;
};

