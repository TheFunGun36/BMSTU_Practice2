#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace math_structs {

TEST_CLASS(TestQuaternion) {
    static constexpr real sqrt2over2 = 0.70710678118654752440084436210485;
public:
    TEST_METHOD(FromEuler) {
        Quaternion a;
        a = Quaternion(EulerAngles(
            Angle(),
            Angle::from_degrees(90),
            Angle()));
        Assert::IsTrue(a == Quaternion(sqrt2over2, 0, sqrt2over2, 0));

        a = Quaternion(EulerAngles(
            Angle(),
            Angle::from_degrees(180),
            Angle()));
        Assert::IsTrue(a == Quaternion(0, 0, 1, 0));

        a = Quaternion(EulerAngles(
            Angle::from_degrees(90),
            Angle(),
            Angle()));
        Assert::IsTrue(a == Quaternion(sqrt2over2, sqrt2over2, 0, 0));

        a = Quaternion(EulerAngles(
            Angle::from_degrees(180),
            Angle(),
            Angle()));
        Assert::IsTrue(a == Quaternion(0, 1, 0, 0));
    }

    TEST_METHOD(Multiplication) {
        Quaternion q = { 1, 0, 0, 0 };
        Assert::IsTrue(q == q * q);

        q = { sqrt2over2, sqrt2over2, 0, 0 };
        Quaternion r = { 0, 1, 0, 0 };
        Assert::AreEqual(r.to_string(), (q * q).to_string());

        Quaternion p = r;
        r = { -sqrt2over2, sqrt2over2, 0, 0 };
        Assert::AreEqual(r.to_string(), (p * q).to_string());
    }
};

}