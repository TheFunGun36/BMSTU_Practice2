#include "Cube.h"

Cube::Cube(Surface fill, Surface border, Vector3D s, Vector3D bs, Vector3D offset) {
    constexpr int cube_verticies = 8;
    constexpr int plate_verticies = 24;
    constexpr int tolerance = 1;
    vertex().resize(cube_verticies + plate_verticies);

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

    fill.owner = this;
    Vector3D normals[] = {
        Vector3D(1., 0., 0.),
        Vector3D(-1., 0., 0.),
        Vector3D(0., 1., 0.),
        Vector3D(0., -1., 0.),
        Vector3D(0., 0., 1.),
        Vector3D(0., 0., -1.)
    };

    // +X
    vertex()[i++] = offset + Vector3D(s.x() + tolerance, bs.y(), bs.z());
    vertex()[i++] = offset + Vector3D(s.x() + tolerance, s.y() - bs.y(), bs.z());
    vertex()[i++] = offset + Vector3D(s.x() + tolerance, bs.y(), s.z() - bs.z());
    vertex()[i++] = offset + Vector3D(s.x() + tolerance, s.y() - bs.y(), s.z() - bs.z());

    // -X
    vertex()[i++] = offset + Vector3D(-tolerance, bs.y(), bs.z());
    vertex()[i++] = offset + Vector3D(-tolerance, s.y() - bs.y(), bs.z());
    vertex()[i++] = offset + Vector3D(-tolerance, bs.y(), s.z() - bs.z());
    vertex()[i++] = offset + Vector3D(-tolerance, s.y() - bs.y(), s.z() - bs.z());

    // +Y
    vertex()[i++] = offset + Vector3D(bs.x(), s.y() + tolerance, bs.z());
    vertex()[i++] = offset + Vector3D(s.x() - bs.x(), s.y() + tolerance, bs.z());
    vertex()[i++] = offset + Vector3D(bs.x(), s.y() + tolerance, s.z() - bs.z());
    vertex()[i++] = offset + Vector3D(s.x() - bs.x(), s.y() + tolerance, s.z() - bs.z());

    // -Y
    vertex()[i++] = offset + Vector3D(bs.x(), -tolerance, bs.z());
    vertex()[i++] = offset + Vector3D(s.x() - bs.x(), -tolerance, bs.z());
    vertex()[i++] = offset + Vector3D(bs.x(), -tolerance, s.z() - bs.z());
    vertex()[i++] = offset + Vector3D(s.x() - bs.x(), -tolerance, s.z() - bs.z());

    // +Z
    vertex()[i++] = offset + Vector3D(bs.x(), bs.y(), s.z() + tolerance);
    vertex()[i++] = offset + Vector3D(s.x() - bs.x(), bs.y(), s.z() + tolerance);
    vertex()[i++] = offset + Vector3D(bs.x(), s.y() - bs.y(), s.z() + tolerance);
    vertex()[i++] = offset + Vector3D(s.x() - bs.x(), s.y() - bs.y(), s.z() + tolerance);

    // -Z
    vertex()[i++] = offset + Vector3D(bs.x(), bs.y(), -tolerance);
    vertex()[i++] = offset + Vector3D(s.x() - bs.x(), bs.y(), -tolerance);
    vertex()[i++] = offset + Vector3D(bs.x(), s.y() - bs.y(), -tolerance);
    vertex()[i++] = offset + Vector3D(s.x() - bs.x(), s.y() - bs.y(), -tolerance);

    int j = 0;
    for (i = cube_verticies; i < cube_verticies + plate_verticies; i += 4) {
        fill.normal = normals[j++];
        fill.points[0] = &vertex()[i];
        fill.points[1] = &vertex()[i + 1];
        fill.points[2] = &vertex()[i + 2];
        add_surface(fill);
        fill.points[0] = &vertex()[i + 3];
        add_surface(fill);
    }

    border.owner = this;
    i = 0;

#define ADD_SURFACE(x1, x2, x3, x4) \
    border.normal = normals[i++]; \
    border.points[0] = &vertex()[x1]; \
    border.points[1] = &vertex()[x2]; \
    border.points[2] = &vertex()[x3]; \
    add_surface(border); \
    border.points[0] = &vertex()[x4]; \
    add_surface(border);

    ADD_SURFACE(1, 3, 5, 7);
    ADD_SURFACE(0, 2, 4, 6);
    ADD_SURFACE(2, 3, 6, 7);
    ADD_SURFACE(0, 1, 4, 5);
    ADD_SURFACE(4, 5, 6, 7);
    ADD_SURFACE(0, 1, 2, 3);

#undef ADD_SURFACE
}
