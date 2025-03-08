#include <Game.hpp>
#include <functional>
#include <vector>
#include <chrono>
#include <cmath>
#include <Testing.hpp>

using namespace Engine;
using namespace std;

bool approxequals(float a, float b, float epsilon) {
    return abs(a - b) < epsilon;
}

bool approxequals(vec2 a, vec2 b, float epsilon) {
    return abs(a - b) < epsilon;
}

bool approxequals(mat3 a, mat3 b, float epsilon) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (!approxequals(a[i][j], b[i][j], epsilon)) return false;
        }
    }
    return true;
}

static_assert(std::is_convertible_v<mat3, float>);

using namespace Testing;

TestRunner& runner{TestRunner::getInstance("mat3 Tests")};

int main() {
    
    runner.addTest("mat3 default constructor", []() {
        mat3 m = mat3();
        bool res = true;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                res &= m[i][j] == 0;
            }
        }
        return res;
    });

    runner.addTest("mat3 fill constructor float", []() {
        mat3 m = mat3(1.0f);
        bool res = true;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                res &= i == j ? m[i][j] == 1 : m[i][j] == 0;
            }
        }
        return res;
    });

    runner.addTest("mat3 fill constructor cast int", []() {
        mat3 m = mat3(1);
        bool res = true;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                res &= i == j ? m[i][j] == 1 : m[i][j] == 0;
            }
        }
        return res;
    });

    runner.addTest("mat3 concat constructor copy fill", []() {
        mat3 m = mat3(1,2, 3, vec3(3,4,6), vec3(4,5,7));
        array<float, 9> cmp = {1,2,3,3,4,6,4,5,7};
        for (int i = 0; i < 9; i++) {
            if (m.flatten()[i] != cmp[i]) return false;
        }
        return true;
    });

    runner.addTest("mat3 concat constructor copy copy", []() {
        mat3 m1 = mat3(1,2, 3, vec3(3,4,6), vec3(4,5,7));
        mat3 m = mat3(m1);
        m1 = mat3(5,6, 7, vec3(8,9,1), vec3(3,2,1));
        return m == mat3(1,2, 3, vec3(3,4,6), vec3(4,5,7));
    });

    runner.addTest("mat3 concat constructor copy cast", []() {
        mat3 m = mat3(mat3(1,2, 3, vec3(3,4,6), vec3(4,5,7)));
        return m == mat3(1,2, 3, vec3(3,4,6), vec3(4,5,7));
    });

    runner.addTest("mat3 assign", []() {
        mat3 a = mat3(1,2, 3, vec3(3,4,6), vec3(4,5,7));
        a = mat3(5,6, 7, vec3(8,9,1), vec3(3,2,1));
        return bool(a == mat3(5,6, 7, vec3(8,9,1), vec3(3,2,1)));
    });

    runner.addTest("mat3 add", []() {
        mat3 a = mat3(1,2, 3, vec3(3,4,6), vec3(4,5,7));
        mat3 b = mat3(5,6, 7, vec3(8,9,1), vec3(3,2,1));
        mat3 c = a + b;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (c[i][j] != a[i][j] + b[i][j]) return false;
            }
        }
        return true;
    });

    runner.addTest("mat3 sub", []() {
        mat3 a = mat3(1,2, 3, vec3(3,4,6), vec3(4,5,7));
        mat3 b = mat3(5,6, 7, vec3(8,9,1), vec3(3,2,1));
        mat3 c = a - b;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (c[i][j] != a[i][j] - b[i][j]) return false;
            }
        }
        return true;
    });

    runner.addTest("mat3 mul mat3", []() {
        mat3 a = mat3(1,2, 3, vec3(3,4,6), vec3(4,5,7));
        mat3 b = mat3(5,6, 7, vec3(8,9,1), vec3(3,2,1));
        return bool(a*b == mat3(51, 69, 100, 39, 57, 85, 13, 19, 28));
    });

    runner.addTest("mat3 mul compare", []() {
        mat3 a = mat3(1,2, 3, vec3(3,4,6), vec3(4,5,7));
        mat3 b = mat3(5,6, 7, vec3(8,9,1), vec3(3,2,1));
        vec3 c = vec3(5,9,1);
        return bool(a*(b*c) == (a*b)*c);
    });

    runner.addTest("mat3 []", []() {
        mat3 a = mat3(1,2, 3, vec3(3,4,6), vec3(4,5,7));
        return bool(a[0] == vec3(1,2,3));
    });

    runner.addTest("mat3 flatten", []() {
        mat3 a = mat3(1,2, 3, vec3(3,4,6), vec3(4,5,7));
        return a.flatten() == std::array<float,9>({1,2,3,3,4,6,4,5,7});
    });

    runner.addTest("mat3 flatten_row", []() {
        mat3 a = mat3(1,2, 3, vec3(3,4,6), vec3(4,5,7));
        return a.flatten_row() == std::array<float,9>({1,3,4,2,4,5,3,6,7});
    });

    runner.addTest("mat3 transpose", []() {
        mat3 a = mat3(1,2, 3, vec3(3,4,6), vec3(4,5,7));
        mat3 t = a.transpose();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (a[i][j] != t[j][i]) return false;
            }
        }
        return true;
    });

    runner.addTest("mat3 determinant", []() {
        mat3 a = mat3(1,2, 3, vec3(3,4,6), vec3(4,5,7));
        return a.determinant() == 1;
    });

    runner.addTest("mat3 inverse", []() {
        mat3 a = mat3(1,2, 3, vec3(3,4,6), vec3(4,5,7));
        return a.inverse()*a == mat3::identity;
    });

    runner.addTest("mat3 trace", []() {
        mat3 a = mat3(1,2, 3, vec3(3,4,6), vec3(4,5,7));
        return (bool)(a.trace() == 12);
    });

    runner.addTest("mat3 rotation X", []() {
        mat3 r = rotationX(2.677f);
        vec3 a = vec3(1,2,4);
        vec3 b = r*a;
        float t = angleBetween(a*vec3(0,1,1), b*vec3(0,1,1));
        return approxequals(t, 2.677f, 0.001f);
    });

    runner.addTest("mat3 rotation Y", []() {
        mat3 r = rotationY(2.677f);
        vec3 a = vec3(1,2,4);
        vec3 b = r*a;
        float t = angleBetween(a*vec3(1,0,1), b*vec3(1,0,1));
        return approxequals(t, 2.677f, 0.001f);
    });

    runner.addTest("mat3 rotation Z", []() {
        mat3 r = rotationZ(2.677f);
        vec3 a = vec3(1,2,4);
        vec3 b = r*a;
        float t = angleBetween(a*vec3(1,1,0), b*vec3(1,1,0));
        return approxequals(t, 2.677f, 0.001f);
    });

    runner.addTest("mat3 rotation axis", []() {
        vec3 k = vec3(1,2,3).normalized();
        mat3 a = rotation(k, M_PI/5);
        vec3 b = vec3(3,4,5).normalized();
        mat3 toAxis = basis(k).inverse();
        vec3 c = (toAxis*a*b*vec3(1,1,0)).normalized();
        vec3 d = (toAxis*b*vec3(1,1,0)).normalized();
        return approxequals(dot(c, d), cos(M_PI/5), 0.00001f) && b.length() == (a*b).length();
    });

    runner.addTest("mat3 rotation to", []() {
        vec3 a = vec3(1,2,3);
        vec3 b = vec3(3,4,5);
        mat3 r = rotation(a,b);
        return approxequals((r*a).normalized(), b.normalized(), 0.00001f);
    });

    runner.addTest("mat3 scale", []() {
        mat3 a = scale(vec3(3,4,5));
        vec3 b = vec3(1,2,3);
        return (bool)(a*b == vec3(3,8,15));
    });

    runner.addTest("mat3 basis 2", []() {
        mat3 a = basis(vec3(1,1,1).normalized(), vec3(-1,0,1).normalized());
        // check for orthonormality
        return (bool)(a*a.transpose() == mat3::identity);
    });

    runner.addTest("mat3 basis 1", []() {
        mat3 a = basis(vec3(1,1,1).normalized());
        // check for orthonormality
        return a*a.transpose() == mat3::identity;
    });

    return 0;
}
