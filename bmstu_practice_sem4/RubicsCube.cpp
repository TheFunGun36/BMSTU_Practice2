#include "RubicsCube.h"
#include <cmath>
#include <cassert>

RubicsCube::RubicsCube() {
    for (int iz = 0; iz < 3; iz++)
        for (int iy = 0; iy < 3; iy++)
            for (int ix = 0; ix < 3; ix++)
                addCube(ix, iy, iz);
}

static inline int arithmeticProg(int value) {
    int result = 0;
    for (int i = 1; i <= value; i++)
        result += i;
    return result;
}

void RubicsCube::addCube(int ix, int iy, int iz) {
    constexpr real sqrt3over3 = 0.5773502691896257;
    const real cubeSize = 10;
    int index = ix + iy * 3 + iz * 9;

    _cube[index] = new Model3D();
    _cube[index]->vertex().reserve(8);
    _cube[index]->surface().reserve(12);

    for (int bz = 0; bz <= 1; bz++) {
        for (int by = 0; by <= 1; by++) {
            for (int bx = 0; bx <= 1; bx++) {
                Vertex vertex;
                vertex.pos = {
                    (arithmeticProg(ix) + 2) * cubeSize,
                    (arithmeticProg(iy) + 2) * cubeSize,
                    (arithmeticProg(iz) + 2) * cubeSize
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
    surface.diffuse = 0.01;
    surface.color = Color(0, 40, 0);

#define ADD_SURFACE(x1, x2, x3, x4, n) \
    surface.normal = n; \
    surface.points[0] = &_cube[index]->vertex()[x1]; \
    surface.points[1] = &_cube[index]->vertex()[x2]; \
    surface.points[2] = &_cube[index]->vertex()[x3]; \
    _cube[index]->surface().push_back(surface); \
    surface.points[0] = &_cube[index]->vertex()[x4]; \
    _cube[index]->surface().push_back(surface); \

    ADD_SURFACE(0, 2, 4, 6, Vector3D(-1, 0, 0));
    ADD_SURFACE(1, 3, 5, 7, Vector3D(1, 0, 0));
    ADD_SURFACE(0, 1, 4, 5, Vector3D(0, -1, 0));
    ADD_SURFACE(2, 3, 6, 7, Vector3D(0, 1, 0));
    ADD_SURFACE(0, 1, 2, 3, Vector3D(0, 0, -1));
    ADD_SURFACE(4, 5, 6, 7, Vector3D(0, 0, 1));

#undef ADD_SURFACE
}

void RubicsCube::applySeq(std::initializer_list<int> indexes, const EulerAngles& rot, bool rev) {
    assert(indexes.size() == 8);

    int inc = rev * 2 - 1;
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
        _cube[i]->transform().rotate(rot);
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
    case 'F': rotateF(!rev); break;
    case 'B': rotateB(!rev); break;
    case 'U': rotateU(!rev); break;
    case 'D': rotateD(!rev); break;
    case 'L': rotateL(!rev); break;
    case 'R': rotateR(!rev); break;
    default: return;
    }
}

void RubicsCube::rotate(char direction, bool rev) {
    switch (direction) {
    case 'F': rotateF(rev); break;
    case 'B': rotateB(rev); break;
    case 'U': rotateU(rev); break;
    case 'D': rotateD(rev); break;
    case 'L': rotateL(rev); break;
    case 'R': rotateR(rev); break;
    default: return;
    }

    _history.push_back(direction);
}

void RubicsCube::rotateF(bool rev) {
    EulerAngles rot = { Angle::from_degrees(rev ? 90 : -90), Angle(), Angle() };
    applySeq({18, 21, 24, 25, 26, 23, 20, 19}, rot, rev);
    _cube[22]->transform().rotate(rot);
}

void RubicsCube::rotateB(bool rev) {
    EulerAngles rot = { Angle::from_degrees(rev ? -90 : 90), Angle(), Angle() };
    applySeq({ 0, 1, 2, 5, 8, 7, 6, 3 }, rot, rev);
    _cube[4]->transform().rotate(rot);
}

void RubicsCube::rotateL(bool rev) {
    EulerAngles rot = { Angle(), Angle::from_degrees(rev ? -90 : 90), Angle() };
    applySeq({ 0, 3, 6, 15, 24, 21, 18, 9 }, rot, rev);
    _cube[12]->transform().rotate(rot);
}

void RubicsCube::rotateR(bool rev) {
    EulerAngles rot = { Angle(), Angle::from_degrees(rev ? 90 : -90), Angle() };
    applySeq({ 8, 5, 2, 11, 20, 23, 26, 17 }, rot, rev);
    _cube[14]->transform().rotate(rot);
}

void RubicsCube::rotateU(bool rev) {
    EulerAngles rot = { Angle(), Angle(), Angle::from_degrees(rev ? 90 : -90) };
    applySeq({ 6, 7, 8, 17, 26, 25, 24, 15 }, rot, rev);
    _cube[16]->transform().rotate(rot);
}

void RubicsCube::rotateD(bool rev) {
    EulerAngles rot = { Angle(), Angle(), Angle::from_degrees(rev ? -90 : 90) };
    applySeq({ 2, 1, 0, 9, 18, 19, 20, 11 }, rot, rev);
    _cube[10]->transform().rotate(rot);
}

void RubicsCube::reset() {
    // TODO: make RubicsCube::reset faster
    while (!_history.empty())
        undo();
}

const Model3D& RubicsCube::cube(int index) const noexcept {
    return *_cube[index];
}
