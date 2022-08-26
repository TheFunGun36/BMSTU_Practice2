#include "VisibleObject.h"

VisibleObject::VisibleObject() {
    _visible = true;
}

bool VisibleObject::set_visible(bool visible) noexcept {
    _visible = visible;
    return true;
}
