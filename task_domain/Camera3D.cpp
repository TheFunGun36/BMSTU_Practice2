#include "Camera3D.h"

Camera3D::Camera3D()
    : _height(50)
    , _distance(45) {
    transform().set_position(Vector3D(-300, 0, 0));
}
