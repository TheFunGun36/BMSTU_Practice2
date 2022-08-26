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
    void rotateF(bool rev);
    void rotateB(bool rev);
    void rotateL(bool rev);
    void rotateR(bool rev);
    void rotateU(bool rev);
    void rotateD(bool rev);

    void addCube(int ix, int iy, int iz);

    void applySeq(std::initializer_list<int> indexes, const EulerAngles& rot, bool rev);

    std::array<Model3D*, 27> _cube;
    std::string _history;
};
