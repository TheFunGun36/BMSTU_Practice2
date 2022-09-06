#include "Cube.h"

Cube::Cube(Surface surface, Vector3D s, Vector3D offset)
    : Cube(surface, s, offset, 0) {
}

void Cube::invert_normals() {
    for (Surface* surface : surface())
        surface->normal.flip();
}

Cube::Cube(Surface surface, Vector3D s, Vector3D offset, int extra_verticies) {
    constexpr int cube_verticies = 8;
    vertex().resize(cube_verticies + extra_verticies);

    int i = 0;
    for (int bz = 0; bz <= 1; bz++) {
        for (int by = 0; by <= 1; by++) {
            for (int bx = 0; bx <= 1; bx++) {
                vertex()[i++] = Vector3D(
                    s.x() * bx,
                    s.y() * by,
                    s.z() * bz) + offset;
            }
        }
    }

    surface.owner = this;
    Vector3D normals[] = {
        Vector3D(1., 0., 0.),
        Vector3D(-1., 0., 0.),
        Vector3D(0., 1., 0.),
        Vector3D(0., -1., 0.),
        Vector3D(0., 0., 1.),
        Vector3D(0., 0., -1.)
    };
    i = 0;

#define ADD_SURFACE(x1, x2, x3, x4) \
    surface.normal = normals[i++]; \
    surface.points[0] = &vertex()[x1]; \
    surface.points[1] = &vertex()[x2]; \
    surface.points[2] = &vertex()[x3]; \
    add_surface(surface); \
    surface.points[0] = &vertex()[x4]; \
    add_surface(surface);

    ADD_SURFACE(1, 3, 5, 7);
    ADD_SURFACE(0, 2, 4, 6);
    ADD_SURFACE(2, 3, 6, 7);
    ADD_SURFACE(0, 1, 4, 5);
    ADD_SURFACE(4, 5, 6, 7);
    ADD_SURFACE(0, 1, 2, 3);

#undef ADD_SURFACE
}
