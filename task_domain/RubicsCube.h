#pragma once
#include "VisibleObject.h"
#include "Model3D.h"
#include <array>

class RubicsCube : public VisibleObject {
public:
    RubicsCube();
    RubicsCube(const RubicsCube&) = delete;
    RubicsCube(RubicsCube&&) = delete;

    ~RubicsCube();

    std::string history() const noexcept;
    void undo();
    void rotate(char direction, bool rev);
    void reset();
    const Model3D& cube(int index) const noexcept;

private:
    void rotate_f(bool rev);
    void rotate_b(bool rev);
    void rotate_l(bool rev);
    void rotate_r(bool rev);
    void rotate_u(bool rev);
    void rotate_d(bool rev);

    void add_cube(int ix, int iy, int iz);

    void apply_seq(std::initializer_list<int> indexes, const EulerAngles& rot, bool rev);

    std::array<Model3D*, 27> _cube;
    std::string _history;
};
