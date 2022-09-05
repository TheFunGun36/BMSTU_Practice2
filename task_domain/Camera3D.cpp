#include "Camera3D.h"

Camera3D::Camera3D()
    : _height(50)
    , _distance(26) {
    transform().set_position(Vector3D(-80, 0, 0));
}
