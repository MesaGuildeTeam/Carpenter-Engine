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

bool approxequals(mat4 a, mat4 b, float epsilon) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (!approxequals(a[i][j], b[i][j], epsilon)) return false;
        }
    }
    return true;
}

static_assert(std::is_convertible_v<mat4, float>);

int main() {
    TestRunner runner = TestRunner("bvec2 class tester", "tests all methods of bvec2", "bvec2");

    runner.addTest("mat4 default constructor", []() {
        mat4 m = mat4();
        bool res = true;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                res &= m[i][j] == 0;
            }
        }
        return res;
    });

    runner.addTest("mat4 fill constructor float", []() {
        mat4 m = mat4(1.0f);
        bool res = true;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                res &= i == j ? m[i][j] == 1 : m[i][j] == 0;
            }
        }
        return res;
    });

    runner.addTest("mat4 fill constructor cast int", []() {
        mat4 m = mat4(1);
        bool res = true;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                res &= i == j ? m[i][j] == 1 : m[i][j] == 0;
            }
        }
        return res;
    });

    runner.addTest("mat4 concat constructor copy fill", []() {
        mat4 m = mat4(1,2, 3, 4, vec4(3,4,6,5), vec4(4,5,7,8), vec4(6,7,8,9));
        array<float, 16> cmp = {1,2,3,4,3,4,6,5,4,5,7,8,6,7,8,9};
        for (int i = 0; i < 16; i++) {
            if (m.flatten()[i] != cmp[i]) return false;
        }
        return true;
    });

    runner.addTest("mat4 concat constructor copy copy", []() {
        mat4 m1 = mat4(1,2, 3, 4, vec4(3,4,6,5), vec4(4,5,7,8), vec4(6,7,8,9));
        mat4 m = mat4(m1);
        m1 = mat4(5,6, 7,8, vec4(8,9,1,2), vec4(3,2,1,0), vec2(1,5), vec2(5,2));
        return m == mat4(1,2, 3, 4, vec4(3,4,6,5), vec4(4,5,7,8), vec4(6,7,8,9));
    });

    runner.addTest("mat4 concat constructor copy cast", []() {
        mat4 m = mat4(mat4(1,2, 3, 4, vec4(3,4,6,5), vec4(4,5,7,8), vec4(6,7,8,9)));
        return m == mat4(1,2, 3, 4, vec4(3,4,6,5), vec4(4,5,7,8), vec4(6,7,8,9));
    });

    runner.addTest("mat4 assign", []() {
        mat4 a = mat4(1,2, 3, 4, vec4(3,4,6,5), vec4(4,5,7,8), vec4(6,7,8,9));
        a = mat4(5,6, 7,8, vec4(8,9,1,2), vec4(3,2,1,0), vec2(1,5), vec2(5,2));
        return bool(a == mat4(5,6, 7,8, vec4(8,9,1,2), vec4(3,2,1,0), vec2(1,5), vec2(5,2)));
    });

    runner.addTest("mat4 add", []() {
        mat4 a = mat4(1,2, 3, 4, vec4(3,4,6,5), vec4(4,5,7,8), vec4(6,7,8,9));
        mat4 b = mat4(5,6, 7,8, vec4(8,9,1,2), vec4(3,2,1,0), vec2(1,5), vec2(5,2));
        mat4 c = a + b;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (c[i][j] != a[i][j] + b[i][j]) return false;
            }
        }
        return true;
    });

    runner.addTest("mat4 sub", []() {
        mat4 a = mat4(1,2, 3, 4, vec4(3,4,6,5), vec4(4,5,7,8), vec4(6,7,8,9));
        mat4 b = mat4(5,6, 7,8, vec4(8,9,1,2), vec4(3,2,1,0), vec2(1,5), vec2(5,2));
        mat4 c = a - b;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (c[i][j] != a[i][j] - b[i][j]) return false;
            }
        }
        return true;
    });

    runner.addTest("mat4 mul mat4", []() {
        mat4 a = mat4(1,2, 3, 4, vec4(3,4,6,5), vec4(4,5,7,8), vec4(6,7,8,9));
        mat4 b = mat4(5,6, 7,8, vec4(8,9,1,2), vec4(3,2,1,0), vec2(1,5), vec2(5,2));
        return bool(a*b == mat4(99,125,164,178,51,71,101,103,13,19,28,30,48,61,84,87));
    });

    runner.addTest("mat4 mul compare", []() {
        mat4 a = mat4(1,2, 3, 4, vec4(3,4,6,5), vec4(4,5,7,8), vec4(6,7,8,9));
        mat4 b = mat4(5,6, 7,8, vec4(8,9,1,2), vec4(3,2,1,0), vec2(1,5), vec2(5,2));
        vec4 c = vec4(5,9,1,2);
        return bool(a*(b*c) == (a*b)*c);
    });

    runner.addTest("mat4 []", []() {
        mat4 a = mat4(1,2, 3, 4, vec4(3,4,6,5), vec4(4,5,7,8), vec4(6,7,8,9));
        return bool(a[0] == vec4(1,2,3,4));
    });

    runner.addTest("mat4 flatten", []() {
        mat4 a = mat4(1,2, 3, 4, vec4(3,4,6,5), vec4(4,5,7,8), vec4(6,7,8,9));
        return a.flatten() == std::array<float,16>({1,2, 3, 4, 3,4,6,5, 4,5,7,8, 6,7,8,9});
    });

    runner.addTest("mat4 flatten_row", []() {
        mat4 a = mat4(1,2, 3, 4, vec4(3,4,6,5), vec4(4,5,7,8), vec4(6,7,8,9));
        return a.flatten_row() == std::array<float,16>({1,3,4,6,2,4,5,7,3,6,7,8,4,5,8,9});
    });

    runner.addTest("mat4 transpose", []() {
        mat4 a = mat4(1,2, 3, 4, vec4(3,4,6,5), vec4(4,5,7,8), vec4(6,7,8,9));
        mat4 t = a.transpose();
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (a[i][j] != t[j][i]) return false;
            }
        }
        return true;
    });

    runner.addTest("mat4 determinant", []() {
        //mat4 a = mat4(1,2, 3, 4, vec4(3,4,6,5), vec4(4,5,7,8), vec4(6,7,8,9));
        //return a.determinant() == 1;
        return false;
    });

    runner.addTest("mat4 inverse", []() {
        //mat4 a = mat4(1,2, 3, 4, vec4(3,4,6,5), vec4(4,5,7,8), vec4(6,7,8,9));
        //return a.inverse()*a == mat4::identity;
        return false;
    });

    runner.addTest("mat4 trace", []() {
        mat4 a = mat4(1,2, 3, 4, vec4(3,4,6,5), vec4(4,5,7,8), vec4(6,7,8,9));
        return (bool)(a.trace() == 1+4+7+9);
    });

    runner.addTest("mat4 scale", []() {
        mat4 a = scale(vec4(3,4,5,7));
        vec4 b = vec4(1,2,3,3);
        return (bool)(a*b == vec4(3,8,15,21));
    });

    runner.runTests();

    return 0;
}