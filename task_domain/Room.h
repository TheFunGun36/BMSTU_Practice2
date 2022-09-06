#pragma once
#include "VisibleObject.h"

class Room : public VisibleObject {
public:
    Room();

private:
    std::array<Vector3D, 8> _vertex;
};

