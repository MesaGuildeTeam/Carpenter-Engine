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

int main() {
    TestRunner runner = TestRunner("vec4 class tester", "tests all methods of vec4", "vec4");

    runner.addTest("vec4 default constructor", "tests if vec4() is a zero vector", []() {
        vec4 v = vec4();
        return v.x == 0 && v.y == 0 && v.z == 0 && v.w == 0;
    });

    runner.addTest("vec4 fill constructor float", "tests if vec4(float) propagates the value to all components", []() {
        vec4 v = vec4(3.14f);
        return v.x == 3.14f && v.y == 3.14f && v.z == 3.14f && v.w == 3.14f;
    });

    runner.addTest("vec4 fill constructor cast int", "tests if vec4(int) casts and propagates the value to all components", []() {
        vec4 v = vec4(3);
        return v.x == 3 && v.y == 3 && v.z == 3 && v.w == 3;
    });

    runner.addTest("vec4 concat constructor copy fill", "tests if vec4(vec4) fills with the components from the source", []() {
        vec4 v = vec4(vec4(3));
        return v.x == 3 && v.y == 3 && v.z == 3 && v.w == 3;
    });

    runner.addTest("vec4 concat constructor copy copy", "tests if vec4(vec4) copies the components from the source", []() {
        vec4 v1 = vec4(3);
        vec4 v = vec4(v1);
        v1 = vec4(4);
        return v.x == 4 && v.y == 4 && v.z == 4 && v.w == 4;
    });

    runner.addTest("vec4 concat constructor copy cast", "tests if vec4(vec4b) copies and casts the components from the source", []() {
        vec4 v = vec4(vec4b(true));
        return v.x == 1 && v.y == 1 && v.z == 1 && v.w == 1;
    });

    runner.addTest("vec4 concat constructor scalar", "tests if vec4(float, float, float) fills with the components", []() {
        vec4 v = vec4(3.15f, 2.3f, 1.0f, 5.0f);
        return v.x == 3.15f && v.y == 2.3f && v.z == 1.0f && v.w == 5.0f;
    });

    runner.addTest("vec4 concat constructor scalar cast", "tests if vec4(float, bool, float) casts and fills with the components", []() {
        vec4 v = vec4(3, true, 1.0f, 5);
        return v.x == 3 && v.y == 1.0f && v.z == 1.0f && v.w == 5;
    });

    runner.addTest("vec4 concat constructor mixed", "tests if vec4(float, vec2) casts and fills with the components", []() {
        vec4 v = vec4(3, vec2(4, 5), 2);
        return v.x == 3 && v.y == 4 && v.z == 5 && v.w == 2;
    });

    runner.addTest("vec4 assign test", "tests that vec4 = vec4 works", []() {
        vec4 a = vec4(1, 2, 3, 4);
        a = vec4(4, 6, 5, 8);
        return bool(a == vec4(4, 6, 5, 8));
    });

    runner.addTest("vec4 add vec4", "tests that vec4 + vec4 works", []() {
        return bool(vec4(1, 2, 3, 4) + vec4(3, 4, 5, 6) == vec4(4, 6, 8, 10));
    });

    runner.addTest("vec4 add float", "tests that vec4 + float works", []() {
        return bool(vec4(1, 2, 3, 4) + 1.0f == vec4(2, 3, 4, 5));
    });

    runner.addTest("vec4 subtract vec4", "tests that vec4 - vec4 works", []() {
        return bool(vec4(1, 2, 3, 4) - vec4(3, 4, 5, 6) == vec4(-2, -2, -2, -2));
    });

    runner.addTest("vec4 subtract float", "tests that vec4 - float works", []() {
        return bool(vec4(1, 2, 3, 4) - 1.0f == vec4(0, 1, 2, 3));
    });

    runner.addTest("vec4 mul vec4", "tests that vec4 * vec4 works", []() {
        return bool(vec4(1, 2, 3, 4)*vec4(3, 4, 5, 6) == vec4(3, 8, 15, 24));
    });

    runner.addTest("vec4 mul float", "tests that vec4 * float works", []() {
        return bool(vec4(1, 2, 3, 4)*2.0f == vec4(2, 4, 6, 8));
    });

    runner.addTest("vec4 div vec4", "tests that vec4 / vec4 works", []() {
        return bool(vec4(1, 2, 3, 4)/vec4(3, 4, 5, 6) == vec4(1/3.0f, 2/4.0f, 3/5.0f, 4/6.0f));
    });

    runner.addTest("vec4 div float", "tests that vec4 / float works", []() {
        return bool(vec4(1, 2, 3, 4)/2.0f == vec4(1/2.0f, 2/2.0f, 3/2.0f, 4/2.0f));
    });

    runner.addTest("vec4 add equals vec4", "tests that vec4 += vec4 works", []() {
        vec4 a = vec4(1, 2, 3, 4);
        bool t = (a += vec4(3, 4, 5, 6)) == vec4(4, 6, 8, 10);
        return bool(a == vec4(4, 6, 8, 10)) && t;
    });

    runner.addTest("vec4 add equals float", "tests that vec4 += float works", []() {
        vec4 a = vec4(1, 2, 3, 4);
        bool t = (a += 1.0f) == vec4(2, 3, 4, 5);
        return bool(a == vec4(2, 3, 4, 5)) && t;
    });

    runner.addTest("vec4 subtract equals vec4", "tests that vec4 -= vec4 works", []() {
        vec4 a = vec4(1, 2, 3, 4);
        bool t = (a -= vec4(3, 4, 5, 6)) == vec4(-2, -2, -2, -2);
        return bool(a == vec4(-2, -2, -2, -2)) && t;
    });

    runner.addTest("vec4 subtract equals float", "tests that vec4 -= float works", []() {
        vec4 a = vec4(1, 2, 3, 4);
        bool t = (a -= 1.0f) == vec4(0, 1, 2, 3);
        return bool(a == vec4(0, 1, 2, 3)) && t;
    });

    runner.addTest("vec4 mul equals vec4", "tests that vec4 *= vec4 works", []() {
        vec4 a = vec4(1, 2, 3, 4);
        bool t = (a *= vec4(3, 4, 5, 6)) == vec4(3, 8, 15, 24);
        return bool(a == vec4(3, 8, 15, 24)) && t;
    });

    runner.addTest("vec4 mul equals float", "tests that vec4 *= float works", []() {
        vec4 a = vec4(1, 2, 3, 4);
        bool t = (a *= 2.0f) == vec4(2, 4, 6, 8);
        return bool(a == vec4(2, 4, 6, 8)) && t;
    });

    runner.addTest("vec4 div equals vec4", "tests that vec4 /= vec4 works", []() {
        vec4 a = vec4(1, 2, 3, 4);
        bool t = (a /= vec4(3, 4, 5, 6)) == vec4(1/3.0f, 2/4.0f, 3/5.0f, 4/6.0f);
        return bool(a == vec4(1/3.0f, 2/4.0f, 3/5.0f, 4/6.0f)) && t;
    });

    runner.addTest("vec4 div equals float", "tests that vec4 /= float works", []() {
        vec4 a = vec4(1, 2, 3, 4);
        bool t = (a /= 2.0f) == vec4(1/2.0f, 2/2.0f, 3/2.0f, 4/2.0f);
        return bool(a == vec4(1/2.0f, 2/2.0f, 3/2.0f, 4/2.0f)) && t;
    });

    runner.addTest("vec4 dot", "tests that dot(vec4, vec4) works", []() {
        return bool(dot(vec4(1, 2, 3, 4), vec4(2, 3, 4, 5)) == 2 + 6 + 12 + 20);
    });
    
    runner.addTest("vec4 anglebetween", "tests that anglebetween(vec4, vec4) works", []() {
        return approxequals(dot(vec4(1, 2, 3, 4), vec4(2, 3, 4, 5))/sqrt(vec4(1, 2, 3, 4).lengthSquared()*vec4(2, 3, 4, 5).lengthSquared()), cos(angleBetween(vec4(1, 2, 3, 4), vec4(2, 3, 4, 5))), 0.0001f);
    });

    runner.addTest("vec4 reflect", "tests that reflect(vec4, vec4) works", []() {
        vec4 n = vec4(2, 3, 4, 5).normalized();
        vec4 i = vec4(1, 2, 3, 4).normalized();
        vec4 r = reflect(i, n);
        return approxequals(dot(r, n), -dot(i, n), 0.01f);
    });

    runner.addTest("vec4 length", "tests that vec4.length() works", []() {
        vec4 a = vec4(2, 3, 4, 5);
        vec4 b = vec4(4, 6, 8, 10);
        vec4 c = vec4(6, 9, 12, 15);
        return approxequals(a.length() + b.length(), c.length(), 0.0001f);
    });

    runner.addTest("vec4 lengthSquared", "tests that vec4.lengthSquared() works", []() {
        vec4 a = vec4(2, 3, 4, 5);
        vec4 b = vec4(4, 6, 8, 10);
        vec4 c = vec4(6, 9, 12, 15);
        return approxequals(sqrtf(a.lengthSquared()) + sqrtf(b.lengthSquared()), sqrtf(c.lengthSquared()), 0.0001f);
    });

    runner.addTest("vec4 distanceSquared", "tests that distanceSquared(vec4, vec4) works", []() {
        vec4 a = vec4(2, 3, 4, 5);
        vec4 b = vec4(4, 6, 8, 10);
        vec4 c = vec4(6, 9, 12, 15);
        return bool(distanceSquared(a, b) == a.lengthSquared());
    });

    runner.runTests();

    return 0;
}