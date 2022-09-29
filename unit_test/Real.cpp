#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace math_structs {

TEST_CLASS(TestReal) {
public:
    TEST_METHOD(Equal) {
        Assert::IsTrue(real_eq(12., 13., 1.5));
        Assert::IsTrue(real_eq(12., 12.001, 0.002));
        Assert::IsFalse(real_eq(12., 12.001, 0.0009));
        Assert::IsFalse(real_eq(-12., 12.0, 1.));
    }

    TEST_METHOD(MinMax) {
        Assert::AreEqual(12., real_min(12., 18.), eps);
        Assert::AreEqual(12., real_min(18., 12.), eps);
        Assert::AreEqual(12., real_min(12., 12.), eps);

        Assert::AreEqual(18., real_max(12., 18.), eps);
        Assert::AreEqual(18., real_max(18., 12.), eps);
        Assert::AreEqual(12., real_max(12., 12.), eps);
    }

    TEST_METHOD(Clamp) {
        Assert::AreEqual(7., real_clamp(7., 6., 8.));
        Assert::AreEqual(7., real_clamp(5., 7., 9.));
        Assert::AreEqual(7., real_clamp(8., 5., 7.));
        Assert::AreEqual(7., real_clamp(7., 7., 7.));
    }
};

}