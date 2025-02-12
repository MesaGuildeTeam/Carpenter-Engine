#include <Game.hpp>
#include <functional>
#include <vector>
#include <chrono>
#include <cmath>
#include "TestRunner.hpp"

using namespace Engine;
using namespace std;

bool approxequals(float a, float b, float epsilon) {
    return abs(a - b) < epsilon;
}

bool approxequals(vec2 a, vec2 b, float epsilon) {
    return abs(a - b) < epsilon;
}

int main() {
    TestRunner runner = TestRunner("bvec2 class tester", "tests all methods of bvec2", "bvec2");

    runner.addTest("mat2 default constructor", []() {
        mat2 m = mat2();
        return m[0].x == 0 && m[0].y == 0 && m[1].x == 0 && m[1].y == 0;
    });

    runner.addTest("mat2 fill constructor float", []() {
        mat2 m = mat2(1.0f);
        return m[0].x == 1 && m[0].y == 0 && m[1].x == 0 && m[1].y == 1;
    });

    runner.addTest("mat2 fill constructor cast int", []() {
        mat2 m = mat2(1);
        return m[0].x == 1 && m[0].y == 0 && m[1].x == 0 && m[1].y == 1;
    });

    runner.addTest("mat2 concat constructor copy fill", []() {
        mat2 m = mat2(1,2, vec2(3,4));
        return m[0].x == 1 && m[0].y == 2 && m[1].x == 3 && m[1].y == 4;
    });

    runner.addTest("mat2 concat constructor copy copy", []() {
        mat2 m1 = mat2(1,2,3,4);
        mat2 m = mat2(m1);
        m1 = mat2(4,5,6,7);
        return m[0].x == 1 && m[0].y == 2 && m[1].x == 3 && m[1].y == 4;
    });

    runner.addTest("mat2 concat constructor copy cast", []() {
        mat2 m = mat2(mat2(1,2,3,4));
        return m[0].x == 1 && m[0].y == 2 && m[1].x == 3 && m[1].y == 4;
    });

    runner.addTest("mat2 assign", []() {
        mat2 a = mat2(1,2,3,4);
        a = mat2(4,5,6,7);
        return bool(a == mat2(4,5,6,7));
    });

    runner.addTest("mat2 add", []() {
        mat2 a = mat2(1,2,3,4);
        mat2 b = mat2(4,5,6,7);
        return bool(a + b == mat2(5,7,9,11));
    });

    runner.addTest("mat2 sub", []() {
        mat2 a = mat2(1,2,3,4);
        mat2 b = mat2(4,5,6,7);
        return bool(a - b == mat2(-3,-3,-3,-3));
    });

    runner.addTest("mat2 mul mat2", []() {
        mat2 a = mat2(1,2,3,4);
        mat2 b = mat2(4,5,6,7);
        return bool(a*b == mat2(19,28,27,40));
    });

    runner.addTest("mat2 mul compare", []() {
        mat2 a = mat2(1,2,3,4);
        mat2 b = mat2(4,5,6,7);
        vec2 c = vec2(5,9);
        return bool(a*(b*c) == (a*b)*c);
    });

    runner.addTest("mat2 []", []() {
        mat2 a = mat2(1,2,3,4);
        return bool(a[0] == vec2(1,2));
    });

    runner.addTest("mat2 flatten", []() {
        mat2 a = mat2(1,2,3,4);
        return a.flatten() == std::array<float,4>({1,2,3,4});
    });

    runner.addTest("mat2 flatten_row", []() {
        mat2 a = mat2(1,2,3,4);
        return a.flatten_row() == std::array<float,4>({1,3,2,4});
    });

    runner.addTest("mat2 transpose", []() {
        mat2 a = mat2(1,2,3,4);
        return a.transpose() == mat2(1,3,2,4);
    });

    runner.addTest("mat2 determinant", []() {
        mat2 a = mat2(1,2,3,4);
        return a.determinant() == -2;
    });

    runner.addTest("mat2 inverse", []() {
        mat2 a = mat2(1,2,3,4);
        return a.inverse() == mat2(-2,1,1.5,-0.5);
    });

    runner.addTest("mat2 trace", []() {
        mat2 a = mat2(1,2,3,4);
        return (bool)(a.trace() == 5);
    });

    runner.addTest("mat2 rotation", []() {
        mat2 a = rotation(M_PI/2);
        vec2 b = vec2(1,0);
        vec2 c = vec2(0,1);
        return (bool)(approxequals(a*b, vec2(0,1), 0.001f) && approxequals(a*c, vec2(-1,0), 0.001f));
    });

    runner.addTest("mat3 rotation to", []() {
        vec2 a = vec2(1,2);
        vec2 b = vec2(3,4);
        mat2 r = rotation(a,b);
        return approxequals((r*a).normalized(), b.normalized(), 0.00001f);
    });

    runner.addTest("mat2 scale", []() {
        mat2 a = scale(vec2(3,4));
        vec2 b = vec2(1,2);
        return (bool)(a*b == vec2(3,8));
    });

    runner.addTest("mat2 basis", []() {
        mat2 a = basis(vec2(1,1).normalized());
        // check for orthonormality
        return (bool)(a*a.transpose() == mat2::identity);
    });

    runner.runTests();

    return 0;
}