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

Testing::TestRunner runner;

int main() {
    
    runner.addTest("vec4 default constructor", []() {
        vec4 v = vec4();
        return v.x == 0 && v.y == 0 && v.z == 0 && v.w == 0;
    });

    runner.addTest("vec4 fill constructor float", []() {
        vec4 v = vec4(3.14f);
        return v.x == 3.14f && v.y == 3.14f && v.z == 3.14f && v.w == 3.14f;
    });

    runner.addTest("vec4 fill constructor cast int", []() {
        vec4 v = vec4(3);
        return v.x == 3 && v.y == 3 && v.z == 3 && v.w == 3;
    });

    runner.addTest("vec4 concat constructor brackets", []() {
        vec4 m = {1,2,3,5};
        return m == vec4(1,2,3,5);
    });

    runner.addTest("vec4 iterator", []() {
        vec4 m = {1,2,3,5};
        for (auto it = m.begin(); it != m.end(); it++) {
            *it = *it * 2;
        }
        return m == vec4(2,4,6,10);
    });

    runner.addTest("vec4 for each", []() {
        vec4 m = {1,2,3,5};
        for (float& v : m) {
            v *= 2.0f;
        }
        return m == vec4(2,4,6,10);
    });

    runner.addTest("vec4 concat constructor copy fill", []() {
        vec4 v = vec4(vec4(3));
        return v.x == 3 && v.y == 3 && v.z == 3 && v.w == 3;
    });

    runner.addTest("vec4 concat constructor copy copy", []() {
        vec4 v1 = vec4(3);
        vec4 v = vec4(v1);
        v1 = vec4(4);
        return v.x == 3 && v.y == 3 && v.z == 3 && v.w == 3;
    });

    runner.addTest("vec4 concat constructor copy cast", []() {
        vec4 v = vec4(bvec4(true));
        return v.x == 1 && v.y == 1 && v.z == 1 && v.w == 1;
    });

    runner.addTest("vec4 concat constructor scalar", []() {
        vec4 v = vec4(3.15f, 2.3f, 1.0f, 5.0f);
        return v.x == 3.15f && v.y == 2.3f && v.z == 1.0f && v.w == 5.0f;
    });

    runner.addTest("vec4 concat constructor scalar cast", []() {
        vec4 v = vec4(3, true, 1.0f, 5);
        return v.x == 3 && v.y == 1.0f && v.z == 1.0f && v.w == 5;
    });

    runner.addTest("vec4 concat constructor mixed", []() {
        vec4 v = vec4(3, vec2(4, 5), 2);
        return v.x == 3 && v.y == 4 && v.z == 5 && v.w == 2;
    });

    runner.addTest("vec4 assign test", []() {
        vec4 a = vec4(1, 2, 3, 4);
        a = vec4(4, 6, 5, 8);
        return bool(a == vec4(4, 6, 5, 8));
    });

    runner.addTest("vec4 add vec4", []() {
        return bool(vec4(1, 2, 3, 4) + vec4(3, 4, 5, 6) == vec4(4, 6, 8, 10));
    });

    runner.addTest("vec4 add float", []() {
        return bool(vec4(1, 2, 3, 4) + 1.0f == vec4(2, 3, 4, 5));
    });

    runner.addTest("vec4 subtract vec4", []() {
        return bool(vec4(1, 2, 3, 4) - vec4(3, 4, 5, 6) == vec4(-2, -2, -2, -2));
    });

    runner.addTest("vec4 subtract float", []() {
        return bool(vec4(1, 2, 3, 4) - 1.0f == vec4(0, 1, 2, 3));
    });

    runner.addTest("vec4 mul vec4", []() {
        return bool(vec4(1, 2, 3, 4)*vec4(3, 4, 5, 6) == vec4(3, 8, 15, 24));
    });

    runner.addTest("vec4 mul float", []() {
        return bool(vec4(1, 2, 3, 4)*2.0f == vec4(2, 4, 6, 8));
    });

    runner.addTest("vec4 div vec4", []() {
        return bool(vec4(1, 2, 3, 4)/vec4(3, 4, 5, 6) == vec4(1/3.0f, 2/4.0f, 3/5.0f, 4/6.0f));
    });

    runner.addTest("vec4 div float", []() {
        return bool(vec4(1, 2, 3, 4)/2.0f == vec4(1/2.0f, 2/2.0f, 3/2.0f, 4/2.0f));
    });

    runner.addTest("vec4 add equals vec4", []() {
        vec4 a = vec4(1, 2, 3, 4);
        bool t = (a += vec4(3, 4, 5, 6)) == vec4(4, 6, 8, 10);
        return bool(a == vec4(4, 6, 8, 10)) && t;
    });

    runner.addTest("vec4 add equals float", []() {
        vec4 a = vec4(1, 2, 3, 4);
        bool t = (a += 1.0f) == vec4(2, 3, 4, 5);
        return bool(a == vec4(2, 3, 4, 5)) && t;
    });

    runner.addTest("vec4 subtract equals vec4", []() {
        vec4 a = vec4(1, 2, 3, 4);
        bool t = (a -= vec4(3, 4, 5, 6)) == vec4(-2, -2, -2, -2);
        return bool(a == vec4(-2, -2, -2, -2)) && t;
    });

    runner.addTest("vec4 subtract equals float", []() {
        vec4 a = vec4(1, 2, 3, 4);
        bool t = (a -= 1.0f) == vec4(0, 1, 2, 3);
        return bool(a == vec4(0, 1, 2, 3)) && t;
    });

    runner.addTest("vec4 mul equals vec4", []() {
        vec4 a = vec4(1, 2, 3, 4);
        bool t = (a *= vec4(3, 4, 5, 6)) == vec4(3, 8, 15, 24);
        return bool(a == vec4(3, 8, 15, 24)) && t;
    });

    runner.addTest("vec4 mul equals float", []() {
        vec4 a = vec4(1, 2, 3, 4);
        bool t = (a *= 2.0f) == vec4(2, 4, 6, 8);
        return bool(a == vec4(2, 4, 6, 8)) && t;
    });

    runner.addTest("vec4 div equals vec4", []() {
        vec4 a = vec4(1, 2, 3, 4);
        bool t = (a /= vec4(3, 4, 5, 6)) == vec4(1/3.0f, 2/4.0f, 3/5.0f, 4/6.0f);
        return bool(a == vec4(1/3.0f, 2/4.0f, 3/5.0f, 4/6.0f)) && t;
    });

    runner.addTest("vec4 div equals float", []() {
        vec4 a = vec4(1, 2, 3, 4);
        bool t = (a /= 2.0f) == vec4(1/2.0f, 2/2.0f, 3/2.0f, 4/2.0f);
        return bool(a == vec4(1/2.0f, 2/2.0f, 3/2.0f, 4/2.0f)) && t;
    });

    runner.addTest("vec4 dot", []() {
        return bool(dot(vec4(1, 2, 3, 4), vec4(2, 3, 4, 5)) == 2 + 6 + 12 + 20);
    });
    
    runner.addTest("vec4 anglebetween", []() {
        return approxequals(dot(vec4(1, 2, 3, 4), vec4(2, 3, 4, 5))/sqrt(vec4(1, 2, 3, 4).lengthSquared()*vec4(2, 3, 4, 5).lengthSquared()), cos(angleBetween(vec4(1, 2, 3, 4), vec4(2, 3, 4, 5))), 0.0001f);
    });

    runner.addTest("vec4 reflect", []() {
        vec4 n = vec4(2, 3, 4, 5).normalized();
        vec4 i = vec4(1, 2, 3, 4).normalized();
        vec4 r = reflect(i, n);
        return approxequals(dot(r, n), -dot(i, n), 0.01f);
    });

    runner.addTest("vec4 length", []() {
        vec4 a = vec4(2, 3, 4, 5);
        vec4 b = vec4(4, 6, 8, 10);
        vec4 c = vec4(6, 9, 12, 15);
        return approxequals(a.length() + b.length(), c.length(), 0.0001f);
    });

    runner.addTest("vec4 lengthSquared", []() {
        vec4 a = vec4(2, 3, 4, 5);
        vec4 b = vec4(4, 6, 8, 10);
        vec4 c = vec4(6, 9, 12, 15);
        return approxequals(sqrtf(a.lengthSquared()) + sqrtf(b.lengthSquared()), sqrtf(c.lengthSquared()), 0.0001f);
    });

    runner.addTest("vec4 distanceSquared", []() {
        vec4 a = vec4(2, 3, 4, 5);
        vec4 b = vec4(4, 6, 8, 10);
        vec4 c = vec4(6, 9, 12, 15);
        return bool(distanceSquared(a, b) == a.lengthSquared());
    });

    runner.runTests();

    return 0;
}

PREPARETESTEXTERNALS(runner);