#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace math_structs {

TEST_CLASS(TestAngle) {
    static constexpr real pi = 3.14159265358979323846;
public:

#define F Angle::to_radians
    TEST_METHOD(ToRadians) {
        Assert::AreEqual(pi,        F(180), eps);
        Assert::AreEqual(pi / 2.,   F(90),  eps);
        Assert::AreEqual(pi / 4.,   F(45),  eps);
        Assert::AreEqual(-pi / 2.,  F(-90), eps);
        Assert::AreEqual(0,         F(0),   eps);
    }
#undef F

#define F Angle::to_degrees
    TEST_METHOD(ToDegrees) {
        Assert::AreEqual(180, F(pi),        eps);
        Assert::AreEqual(90,  F(pi / 2.),   eps);
        Assert::AreEqual(45,  F(pi / 4.),   eps);
        Assert::AreEqual(-90, F(-pi / 2.),  eps);
        Assert::AreEqual(0,   F(0),         eps);
    }
#undef F

#define F Angle::optimize_degrees
    TEST_METHOD(OptimizeDegrees) {
        Assert::AreEqual(180,   F(540), eps);
        Assert::AreEqual(270,   F(-90), eps);
        Assert::AreEqual(90,    F(90), eps);
        Assert::AreEqual(0,     F(0), eps);
        Assert::AreEqual(0,     F(360), eps);
    }
#undef F

#define F Angle::optimize_radians
    TEST_METHOD(OptimizeRadians) {
        Assert::AreEqual(pi/2.,     F(2 * pi + pi / 2.), eps);
        Assert::AreEqual(3*pi/2.,   F(-pi / 2.), eps);
        Assert::AreEqual(pi/2.,     F(pi/2.), eps);
        Assert::AreEqual(0,         F(0), eps);
        Assert::AreEqual(0,         F(2 * pi), eps);
    }
#undef F
};

}