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
    const real cube_size = 20;

    Surface fill;
    fill.diffuse = 0.8;
    fill.color = Color(150, 170, 150);

    Surface border;
    border.diffuse = 1.0;
    border.color = Color(40, 40, 40);

    Vector3D size(
        (arithmeticProg(ix) + 1) * cube_size,
        (arithmeticProg(iy) + 1) * cube_size,
        (arithmeticProg(iz) + 1) * cube_size
    );

    Vector3D offset(
        (arithmeticProg(ix) - 2) * cube_size,
        (arithmeticProg(iy) - 2) * cube_size,
        (arithmeticProg(iz) - 2) * cube_size
    );

    Vector3D border_size(3., 3., 3.);

    int index = ix + iy * 3 + iz * 9;
    _cube[index] = new CubeBordered(fill, border, size, border_size, offset);
    surface().reserve(24);
    for (auto s : _cube[index]->surface())
        surface().push_back(s);
}

void RubicsCube::apply_seq(std::initializer_list<int> indexes, const EulerAngles& rot, bool rev) {
    rev = !rev;
    int inc = 1 - rev * 2;
    const int* begin = rev ? indexes.end() - 1 : indexes.begin();
    const int* end = rev ? indexes.begin() - 1 : indexes.end();

    const int* it = begin;

    CubeBordered* tmp = _cube[*it];
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

    _history.pop_back();
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

const CubeBordered& RubicsCube::cube(int index) const noexcept {
    return *_cube[index];
}
