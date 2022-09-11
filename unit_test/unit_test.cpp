#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unittest {

TEST_CLASS(TestVector3D) {
public:
    TEST_METHOD(DotProduct) {
        Assert::AreEqual(Vector3D(4, -6, 2) * Vector3D(2, 3, 3), -4.);
        Assert::AreEqual(Vector3D(2, 3, 3) * Vector3D(4, -6, 2), -4.);
        Assert::AreEqual(Vector3D::dot_product(Vector3D(4, -6, 2), Vector3D(0, 0, 0)), 0.);
        Assert::AreEqual(Vector3D::dot_product(Vector3D(4, -6, 2), Vector3D(0, 0, 0)), 0.);
    }

    TEST_METHOD(CrossProduct) {
        auto a = Vector3D(4, -6, 2);
        auto b = Vector3D(2, 3, 3);
        Vector3D cross = Vector3D::cross_product(a, b);
        Assert::AreEqual(Vector3D(-24, -8, 24).to_string(), cross.to_string());
        
        b = Vector3D(0, 0, 0);
        cross = Vector3D::cross_product(a, b);
        for (int i = 0; i < 3; i++)
            Assert::AreEqual(0., cross[i]);
    }
};
}
