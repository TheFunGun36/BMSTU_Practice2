#include "Pyramid.h"

Pyramid::Pyramid(Surface surface, const Vector3D& c, real side) {
    constexpr int verticies = 4;
    vertex().resize(verticies);

    constexpr real sqrt3over2 = 0.8660254037844386;
    constexpr real sqrt3over6 = sqrt3over2 / 3.0;
    constexpr real sqrt3over3 = sqrt3over6 * 2.0;
    constexpr real sqrt6over3 = 0.816496580927726;

    vertex()[0] = c + Vector3D(-sqrt3over6, 0.5, 0) * side;
    vertex()[1] = c + Vector3D(-sqrt3over6, -0.5, 0) * side;
    vertex()[2] = c + Vector3D(sqrt3over3, 0, 0) * side;
    vertex()[3] = c + Vector3D(0, 0, sqrt6over3) * side;

    surface.owner = this;
    surface.points = { &vertex()[0], &vertex()[1], &vertex()[2] };
    surface.normal = Vector3D::down();
    add_surface(surface);

    surface.points = { &vertex()[0], &vertex()[1], &vertex()[3] };
    surface.calculateNormal(c);
    add_surface(surface);
    surface.points = { &vertex()[0], &vertex()[2], &vertex()[3] };
    surface.calculateNormal(c);
    add_surface(surface);
    surface.points = { &vertex()[1], &vertex()[2], &vertex()[3] };
    surface.calculateNormal(c);
    add_surface(surface);
}
