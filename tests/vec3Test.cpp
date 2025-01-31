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
    TestRunner runner = TestRunner("vec3 class tester", "tests all methods of vec3", "vec3");

    runner.addTest("vec3 default constructor", "tests if vec3() is a zero vector", []() {
        vec3 v = vec3();
        return v.x == 0 && v.y == 0 && v.z == 0;
    });

    runner.addTest("vec3 fill constructor float", "tests if vec3(float) propagates the value to all components", []() {
        vec3 v = vec3(3.14f);
        return v.x == 3.14f && v.y == 3.14f && v.z == 3.14f;
    });

    runner.addTest("vec3 fill constructor cast int", "tests if vec3(int) casts and propagates the value to all components", []() {
        vec3 v = vec3(3);
        return v.x == 3 && v.y == 3 && v.z == 3;
    });

    runner.addTest("vec3 concat constructor copy fill", "tests if vec3(vec3) fills with the components from the source", []() {
        vec3 v = vec3(vec3(3));
        return v.x == 3 && v.y == 3 && v.z == 3;
    });

    runner.addTest("vec3 concat constructor copy copy", "tests if vec3(vec3) copies the components from the source", []() {
        vec3 v1 = vec3(3);
        vec3 v = vec3(v1);
        v1 = vec3(4);
        return v.x == 4 && v.y == 4 && v.z == 4;
    });

    runner.addTest("vec3 concat constructor copy cast", "tests if vec3(vec3b) copies and casts the components from the source", []() {
        vec3 v = vec3(vec3b(true));
        return v.x == 1 && v.y == 1 && v.z == 1;
    });

    runner.addTest("vec3 concat constructor scalar", "tests if vec3(float, float, float) fills with the components", []() {
        vec3 v = vec3(3.15f, 2.3f, 1.0f);
        return v.x == 3.15f && v.y == 2.3f && v.z == 1.0f;
    });

    runner.addTest("vec3 concat constructor scalar cast", "tests if vec3(float, bool, float) casts and fills with the components", []() {
        vec3 v = vec3(3, true, 1.0f);
        return v.x == 3 && v.y == 1.0f && v.z == 1.0f;
    });

    runner.addTest("vec3 concat constructor mixed", "tests if vec3(float, vec2) casts and fills with the components", []() {
        vec3 v = vec3(3, vec2(4, 5));
        return v.x == 3 && v.y == 4 && v.z == 5;
    });

    runner.addTest("vec3 assign test", "tests that vec3 = vec3 works", []() {
        vec3 a = vec3(1, 2, 3);
        a = vec3(4, 6, 5);
        return bool(a == vec3(4, 6, 5));
    });

    runner.addTest("vec3 add vec3", "tests that vec3 + vec3 works", []() {
        return bool(vec3(1, 2, 3) + vec3(3, 4, 5) == vec3(4, 6, 8));
    });

    runner.addTest("vec3 add float", "tests that vec3 + float works", []() {
        return bool(vec3(1, 2, 3) + 1.0f == vec3(2, 3, 4));
    });

    runner.addTest("vec3 subtract vec3", "tests that vec3 - vec3 works", []() {
        return bool(vec3(1, 2, 3) - vec3(3, 4, 5) == vec3(-2, -2, -2));
    });

    runner.addTest("vec3 subtract float", "tests that vec3 - float works", []() {
        return bool(vec3(1, 2, 3) - 1.0f == vec3(0, 1, 2));
    });

    runner.addTest("vec3 mul vec3", "tests that vec3 * vec3 works", []() {
        return bool(vec3(1, 2, 3)*vec3(3, 4, 5) == vec3(3, 8, 15));
    });

    runner.addTest("vec3 mul float", "tests that vec3 * float works", []() {
        return bool(vec3(1, 2, 3)*2.0f == vec3(2, 4, 6));
    });

    runner.addTest("vec3 div vec3", "tests that vec3 / vec3 works", []() {
        return bool(vec3(1, 2, 3)/vec3(3, 4, 5) == vec3(1/3.0f, 2/4.0f, 3/5.0f));
    });

    runner.addTest("vec3 div float", "tests that vec3 / float works", []() {
        return bool(vec3(1, 2, 3)/2.0f == vec3(1/2.0f, 2/2.0f, 3/2.0f));
    });

    runner.addTest("vec3 add equals vec3", "tests that vec3 += vec3 works", []() {
        vec3 a = vec3(1, 2, 3);
        bool t = (a += vec3(3, 4, 5)) == vec3(4, 6, 8);
        return bool(a == vec3(4, 6, 8)) && t;
    });

    runner.addTest("vec3 add equals float", "tests that vec3 += float works", []() {
        vec3 a = vec3(1, 2, 3);
        bool t = (a += 1.0f) == vec3(2, 3, 4);
        return bool(a == vec3(2, 3, 4)) && t;
    });

    runner.addTest("vec3 subtract equals vec3", "tests that vec3 -= vec3 works", []() {
        vec3 a = vec3(1, 2, 3);
        bool t = (a -= vec3(3, 4, 5)) == vec3(-2, -2, -2);
        return bool(a == vec3(-2, -2, -2)) && t;
    });

    runner.addTest("vec3 subtract equals float", "tests that vec3 -= float works", []() {
        vec3 a = vec3(1, 2, 3);
        bool t = (a -= 1.0f) == vec3(0, 1, 2);
        return bool(a == vec3(0, 1, 2)) && t;
    });

    runner.addTest("vec3 mul equals vec3", "tests that vec3 *= vec3 works", []() {
        vec3 a = vec3(1, 2, 3);
        bool t = (a *= vec3(3, 4, 5)) == vec3(3, 8, 15);
        return bool(a == vec3(3, 8, 15)) && t;
    });

    runner.addTest("vec3 mul equals float", "tests that vec3 *= float works", []() {
        vec3 a = vec3(1, 2, 3);
        bool t = (a *= 2.0f) == vec3(2, 4, 6);
        return bool(a == vec3(2, 4, 6)) && t;
    });

    runner.addTest("vec3 div equals vec3", "tests that vec3 /= vec3 works", []() {
        vec3 a = vec3(1, 2, 3);
        bool t = (a /= vec3(3, 4, 5)) == vec3(1/3.0f, 2/4.0f, 3/5.0f);
        return bool(a == vec3(1/3.0f, 2/4.0f, 3/5.0f)) && t;
    });

    runner.addTest("vec3 div equals float", "tests that vec3 /= float works", []() {
        vec3 a = vec3(1, 2, 3);
        bool t = (a /= 2.0f) == vec3(1/2.0f, 2/2.0f, 3/2.0f);
        return bool(a == vec3(1/2.0f, 2/2.0f, 3/2.0f)) && t;
    });

    runner.addTest("vec3 dot", "tests that dot(vec3, vec3) works", []() {
        return bool(dot(vec3(1, 2, 3), vec3(2, 3, 4)) == 20);
    });
    
    runner.addTest("vec3 anglebetween", "tests that anglebetween(vec3, vec3) works", []() {
        return approxequals(dot(vec3(1, 2, 3), vec3(2, 3, 4))/sqrt(vec3(1, 2, 3).lengthSquared()*vec3(2, 3, 4).lengthSquared()), cos(angleBetween(vec3(1, 2, 3), vec3(2, 3, 4))), 0.0001f);
    });

    runner.addTest("vec3 reflect", "tests that reflect(vec3, vec3) works", []() {
        vec3 n = vec3(2, 3, 4).normalized();
        vec3 i = vec3(1, 2, 3).normalized();
        vec3 r = reflect(i, n);
        return approxequals(dot(r, n), -dot(i, n), 0.01f);
    });

    runner.addTest("vec3 length", "tests that vec3.length() works", []() {
        vec3 a = vec3(2, 3, 4);
        vec3 b = vec3(4, 6, 8);
        vec3 c = vec3(6, 9, 12);
        return approxequals(a.length() + b.length(), c.length(), 0.0001f);
    });

    runner.addTest("vec3 lengthSquared", "tests that vec3.lengthSquared() works", []() {
        vec3 a = vec3(2, 3, 4);
        vec3 b = vec3(4, 6, 8);
        vec3 c = vec3(6, 9, 12);
        return approxequals(sqrtf(a.lengthSquared()) + sqrtf(b.lengthSquared()), sqrtf(c.lengthSquared()), 0.0001f);
    });

    runner.addTest("vec3 distanceSquared", "tests that distanceSquared(vec3, vec3) works", []() {
        vec3 a = vec3(2, 3, 4);
        vec3 b = vec3(4, 6, 8);
        vec3 c = vec3(6, 9, 12);
        return bool(distanceSquared(a, b) == a.lengthSquared());
    });

    runner.addTest("vec3 cross", "tests that cross(vec3, vec3) works", []() {
        return bool(cross(vec3(1, 0, 0), vec3(0, 0, 1)) == vec3(0,-1,0));
    });

    runner.addTest("vec3 tangent", "tests that vec3::tangent is tangent to the source vector", []() {
        return bool(dot(vec3(1, 2, 3), vec3(1, 2, 3).tangent()) == 0);
    });

    runner.runTests();

    return 0;
}