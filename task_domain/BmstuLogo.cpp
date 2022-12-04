#include "BmstuLogo.h"

BmstuLogo::BmstuLogo() {
    Color blue = Color(0x08, 0x5c, 0xa8);
    Color gray = Color(0xd6, 0xd4, 0xd4);
    Color yellow = Color(0xec, 0xbc, 0x35);

    vertex().reserve(60);
    vertex().push_back(Vector3D(-5, 0, 0));
    Surface surface;
    surface.owner = this;
    surface.diffuse = 1.0;
    surface.color = blue;
    surface.normal = Vector3D::up();
    make_shield(surface, 1.0, 0.01);
    make_plane_bg(surface, 0.04);

    surface.diffuse = 0.3;
    surface.color = gray;
    make_shield(surface, 0.90, 0.02);

    surface.diffuse = 0.6;
    surface.color = yellow;
    make_plane(surface, 0.04);

    transform().set_scale(Vector3D(10, 10, 10));
    transform().set_position(Vector3D(0, 0, -200));
}

void BmstuLogo::make_shield(Surface surf, real scale, real z) {

    // X: -23.40
    // Y: -36.74
    Vector3D path[] = {
        {0,         23.94, z},
        {-7.97,     28.92, z},
        {-10.66,    28.28, z},
        {-13.24,    30.91, z},
        {-11.3,     38.43, z},
        {-13.34,    46.40, z},
        {-8.17,     53.17, z},
        {0,         59.64, z},
        {8.17,      53.17, z},
        {13.34,     46.40, z},
        {11.3,      38.43, z},
        {13.24,     30.91, z},
        {10.66,     28.28, z},
        {7.97,      28.92, z},
    };

    for (auto& el : path) {
        el.set_y(el.y() - 36.74);
        el *= scale;
    }

    add_shape(surf, path, sizeof(path) / sizeof(Vector3D));
}

void BmstuLogo::make_plane(Surface surface, real z) {
    // X: -23.40
    // Y: -36.74

    Vector3D path[] = {
        { -0.15,    31.86, z },
        { -0.9,     38.28, z },
        { -2.84,    40.77, z },
        { -7.32,    42.76, z },
        { -1.74,    42.76, z },
        { 0,        45.40, z },
        { 1.74,     42.76, z },
        { 7.32,     42.76, z },
        { 2.84,     40.77, z },
        { 0.9,      38.28, z },
        { 0.15,     31.86, z }
    };

    for (auto &el : path)
        el.set_y(el.y() - 36.74);

    add_shape(surface, path, sizeof(path) / sizeof(Vector3D));
}

void BmstuLogo::make_plane_bg(Surface surface, real z) {
    Vector3D path[] = {
        { -7.8,     46, z },
        { 7.8,      46, z },
        { 7.8,      31, z },
        { -7.8,     31, z }
    };

    for (auto& el : path)
        el.set_y(el.y() - 36.74);

    add_shape(surface, path, sizeof(path) / sizeof(Vector3D));
}

void BmstuLogo::add_shape(Surface surf, Vector3D* path, int count) {
    int ibegin = vertex().size();

    for (int i = 0; i < count; i++) {
        Vector3D& el = path[i];

        real v = el.x();
        el.set_x(-el.y());
        el.set_y(v);

        vertex().push_back(el);
    }

    for (int i = 1; i < count; i++) {
        surf.points = {
            &vertex()[0],
            &vertex()[ibegin + i - 1],
            &vertex()[ibegin + i]
        };

        add_surface(surf);
    }

    surf.points = {
        &vertex()[0],
        &vertex()[ibegin],
        &vertex()[ibegin + count - 1]
    };

    add_surface(surf);
}
