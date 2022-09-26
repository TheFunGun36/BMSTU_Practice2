#include "CubeBordered.h"

static constexpr int plate_verticies = 24;

CubeBordered::CubeBordered(Surface fill, Surface border, Vector3D s, Vector3D bs, Vector3D offset)
    : Cube(border, s, offset, plate_verticies) {
    constexpr int cube_verticies = 8;
    constexpr real tolerance = 0.1;
    vertex().resize(cube_verticies + plate_verticies);
    
    fill.owner = this;
    Vector3D normals[] = {
        Vector3D(1., 0., 0.),
        Vector3D(-1., 0., 0.),
        Vector3D(0., 1., 0.),
        Vector3D(0., -1., 0.),
        Vector3D(0., 0., 1.),
        Vector3D(0., 0., -1.)
    };

    int i = cube_verticies;

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
}
