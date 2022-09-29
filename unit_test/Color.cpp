#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace math_structs {

TEST_CLASS(TestColor) {
public:
    TEST_METHOD(Blend) {
        auto a = Color(250, 120, 250);
        Assert::IsTrue(a == a);

        auto b = Color(100, 100, 100);
        Assert::IsTrue(Color(175, 110, 175) == Color::blend(a, b, 0.5));
        Assert::IsTrue(Color(137, 105, 137) == Color::blend(a, b, 0.25));
    }

    TEST_METHOD(Intensity) {
        auto c = Color(250, 120, 250);
        Color b = Color::intensity(c, 1.);

        Assert::IsTrue(c == b);
        Assert::IsTrue(Color(255, 240, 255) == Color::intensity(c, 2.));
        Assert::IsTrue(Color(50, 24, 50) == Color::intensity(c, 0.));
        Assert::IsTrue(Color(50, 24, 50) == Color::intensity(c, 0.1));
        Assert::IsTrue(Color(50, 24, 50) == Color::intensity(c, 0.2));
        Assert::IsTrue(Color(75, 36, 75) == Color::intensity(c, 0.3));
    }
};

}