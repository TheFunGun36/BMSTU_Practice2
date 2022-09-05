#include "RubicsCube.h"
#include <cmath>
#include <cassert>

RubicsCube::RubicsCube() {
    this->surface().reserve(324);
    for (int iz = 0; iz < 3; iz++)
        for (int iy = 0; iy < 3; iy++)
            for (int ix = 0; ix < 3; ix++)
                add_cube(ix, iy, iz);
}

static inline int arithmeticProg(int value) {
    int result = 0;
    for (int i = 1; i <= value; i++)
        result += i;
    return result;
}

void RubicsCube::add_cube(int ix, int iy, int iz) {
    constexpr real sqrt3over3 = 0.5773502691896257;
    const real cube_size = 10;
    const real border_size = 2;
    int index = ix + iy * 3 + iz * 9;

    _cube[index] = new Model3D();
    _cube[index]->vertex().reserve(8);
    _cube[index]->surface().reserve(12);

    for (int bz = 0; bz <= 1; bz++) {
        for (int by = 0; by <= 1; by++) {
            for (int bx = 0; bx <= 1; bx++) {
                Vertex vertex;
                vertex.pos = {
                    (arithmeticProg(ix + bx) - 2) * cube_size - (bx * 2 - 1) * border_size,
                    (arithmeticProg(iy + by) - 2) * cube_size - (by * 2 - 1) * border_size,
                    (arithmeticProg(iz + bz) - 2) * cube_size - (bz * 2 - 1) * border_size
                };
                vertex.normal = {
                    sqrt3over3 * bx * 2 - sqrt3over3,
                    sqrt3over3 * by * 2 - sqrt3over3,
                    sqrt3over3 * bz * 2 - sqrt3over3,
                };
                _cube[index]->vertex().push_back(vertex);
            }
        }
    }

    Surface surface;
    surface.diffuse = 0.5;
    surface.color = Color(0, 40, 0);
    surface.owner = _cube[index];

#define ADD_SURFACE(x1, x2, x3, x4, n) \
    surface.normal = n; \
    surface.points[0] = &_cube[index]->vertex()[x1]; \
    surface.points[1] = &_cube[index]->vertex()[x2]; \
    surface.points[2] = &_cube[index]->vertex()[x3]; \
    _cube[index]->add_surface(surface); \
    this->surface().push_back(_cube[index]->surface().back()); \
    surface.points[0] = &_cube[index]->vertex()[x4]; \
    _cube[index]->add_surface(surface); \
    this->surface().push_back(_cube[index]->surface().back());

    ADD_SURFACE(0, 2, 4, 6, Vector3D(-1, 0, 0));
    ADD_SURFACE(1, 3, 5, 7, Vector3D(1, 0, 0));
    ADD_SURFACE(0, 1, 4, 5, Vector3D(0, -1, 0));
    ADD_SURFACE(2, 3, 6, 7, Vector3D(0, 1, 0));
    ADD_SURFACE(0, 1, 2, 3, Vector3D(0, 0, -1));
    ADD_SURFACE(4, 5, 6, 7, Vector3D(0, 0, 1));

#undef ADD_SURFACE
}

void RubicsCube::apply_seq(std::initializer_list<int> indexes, const EulerAngles& rot, bool rev) {
    rev = !rev;
    int inc = 1 - rev * 2;
    const int* begin = rev ? indexes.end() - 1 : indexes.begin();
    const int* end = rev ? indexes.begin() - 1 : indexes.end();

    const int* it = begin;

    Model3D* tmp = _cube[*it];
    it += inc;
    while (it != end) {
        _cube[*(it - inc)] = _cube[*it];
        it += inc;
    }
    _cube[*(it - inc)] = tmp;

    for (int i : indexes)
        _cube[i]->transform().rotate_world(rot);
}

RubicsCube::~RubicsCube() {
    for (int i = 0; i < _cube.size(); i++)
        delete _cube[i];
}

std::string RubicsCube::history() const noexcept {
    std::string result;
    result.reserve(_history.size() * 2);

    for (auto ch : _history) {
        if (ch <= 'Z') {  // if uppercase
            result.push_back(ch);
        }
        else {
            ch -= 32;  // 'a' - 'A', to uppercase
            result.push_back(ch);
            result.push_back('\'');
        }
    }

    return result;
}

void RubicsCube::undo() {
    char ch = _history.back();
    bool rev = ch >= 'a';  //if lowercase
    switch (ch - rev * 32) {
    case 'F': rotate_f(!rev); break;
    case 'B': rotate_b(!rev); break;
    case 'U': rotate_u(!rev); break;
    case 'D': rotate_d(!rev); break;
    case 'L': rotate_l(!rev); break;
    case 'R': rotate_r(!rev); break;
    default: return;
    }
}

void RubicsCube::rotate(char direction, bool rev) {
    switch (direction) {
    case 'F': rotate_f(rev); break;
    case 'B': rotate_b(rev); break;
    case 'U': rotate_u(rev); break;
    case 'D': rotate_d(rev); break;
    case 'L': rotate_l(rev); break;
    case 'R': rotate_r(rev); break;
    default: return;
    }

    _history.push_back(direction + (rev ? 'a' - 'A' : 0));
}

void RubicsCube::rotate_f(bool rev) {
    EulerAngles rot = { Angle::from_degrees(rev ? -90 : 90), Angle(), Angle() };  //-X
    apply_seq({ 0, 6, 24, 18 }, rot, rev);  //Corners
    apply_seq({ 3, 15, 21, 9 }, rot, rev);  //Edges
    _cube[12]->transform().rotate_world(rot);
}

void RubicsCube::rotate_b(bool rev) {
    EulerAngles rot = { Angle::from_degrees(rev ? 90 : -90), Angle(), Angle() };  //+X
    apply_seq({ 8, 2, 20, 26 }, rot, rev);  //Corners
    apply_seq({ 5, 11, 23, 17 }, rot, rev);  //Edges
    _cube[14]->transform().rotate_world(rot);
}

void RubicsCube::rotate_l(bool rev) {
    EulerAngles rot = { Angle(), Angle::from_degrees(rev ? 90 : -90), Angle() };  //+Y
    apply_seq({ 6, 8, 26, 24 }, rot, rev);  //Corners
    apply_seq({ 7, 17, 25, 15 }, rot, rev);  //Edges
    _cube[16]->transform().rotate_world(rot);
}

void RubicsCube::rotate_r(bool rev) {
    EulerAngles rot = { Angle(), Angle::from_degrees(rev ? -90 : 90), Angle() };  //-Y
    apply_seq({ 2, 0, 18, 20 }, rot, rev);  //Corners
    apply_seq({ 1, 9, 19, 11 }, rot, rev);  //Edges
    _cube[10]->transform().rotate_world(rot);
}

void RubicsCube::rotate_u(bool rev) {
    EulerAngles rot = { Angle(), Angle(), Angle::from_degrees(rev ? 90 : -90) };  //+Z
    apply_seq({ 18, 24, 26, 20 }, rot, rev);  //Corners
    apply_seq({ 21, 25, 23, 19 }, rot, rev);  //Edges
    _cube[22]->transform().rotate_world(rot);
}

void RubicsCube::rotate_d(bool rev) {
    EulerAngles rot = { Angle(), Angle(), Angle::from_degrees(rev ? -90 : 90) };  //-Z
    apply_seq({ 0, 2, 8, 6 }, rot, rev);  //Corners
    apply_seq({ 1, 5, 7, 3 }, rot, rev);  //Edges
    _cube[4]->transform().rotate_world(rot);
}

void RubicsCube::reset() {
    while (!_history.empty())
        undo();
}

const Model3D& RubicsCube::cube(int index) const noexcept {
    return *_cube[index];
}
