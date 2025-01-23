#include <Game.hpp>
#include <functional>
#include <vector>
#include <chrono>
#include <cmath>
#include "TestRunner.hpp"

using namespace Engine;

bool approxequals(float a, float b, float epsilon) {
    return abs(a - b) < epsilon;
}

int main() {
    TestRunner runner = TestRunner("vec2 class tester", "tests all methods of vec2", "vec2");

    runner.addTest("vec2 default constructor", "tests if vec2() is a zero vector", []() {
        vec2 v = vec2();
        return v.x == 0 && v.y == 0;
    });

    runner.addTest("vec2 fill constructor float", "tests if vec2(float) propagates the value to all components", []() {
        vec2 v = vec2(3.14f);
        return v.x == 3.14f && v.y == 3.14f;
    });

    runner.addTest("vec2 fill constructor cast int", "tests if vec2(int) casts and propagates the value to all components", []() {
        vec2 v = vec2(3);
        return v.x == 3 && v.y == 3;
    });

    runner.addTest("vec2 concat constructor copy fill", "tests if vec2(vec2) fills with the components from the source", []() {
        vec2 v = vec2(vec2(3));
        return v.x == 3 && v.y == 3;
    });

    runner.addTest("vec2 concat constructor copy copy", "tests if vec2(vec2) copies the components from the source", []() {
        vec2 v1 = vec2(3);
        vec2 v = vec2(v1);
        v1 = vec2(4);
        return v.x == 4 && v.y == 4;
    });

    runner.addTest("vec2 concat constructor copy cast", "tests if vec2(vec2b) copies and casts the components from the source", []() {
        vec2 v = vec2(vec2b(true));
        return v.x == 1 && v.y == 1;
    });

    runner.addTest("vec2 concat constructor scalar", "tests if vec2(float, float) fills with the components", []() {
        vec2 v = vec2(3.15f, 2.3f);
        return v.x == 3.15f && v.y == 2.3f;
    });

    runner.addTest("vec2 concat constructor scalar cast", "tests if vec2(float, float) casts and fills with the components", []() {
        vec2 v = vec2(3, true);
        return v.x == 3 && v.y == 1.0f;
    });

    runner.addTest("vec2 assign test", "tests that vec2 = vec2 works", []() {
        vec2 a = vec2(1, 2);
        a = vec2(4, 6);
        return bool(a == vec2(4, 6));
    });

    runner.addTest("vec2 add vec2", "tests that vec2 + vec2 works", []() {
        return bool(vec2(1, 2) + vec2(3, 4) == vec2(4, 6));
    });

    runner.addTest("vec2 add float", "tests that vec2 + float works", []() {
        return bool(vec2(1, 2) + 1.0f == vec2(2, 3));
    });

    runner.addTest("vec2 subtract vec2", "tests that vec2 - vec2 works", []() {
        return bool(vec2(1, 2) - vec2(3, 4) == vec2(-2, -2));
    });

    runner.addTest("vec2 subtract float", "tests that vec2 - float works", []() {
        return bool(vec2(1, 2) - 1.0f == vec2(0, 1));
    });

    runner.addTest("vec2 mul vec2", "tests that vec2 * vec2 works", []() {
        return bool(vec2(1, 2)*vec2(3, 4) == vec2(3, 8));
    });

    runner.addTest("vec2 mul float", "tests that vec2 * float works", []() {
        return bool(vec2(1, 2)*2.0f == vec2(2, 4));
    });

    runner.addTest("vec2 div vec2", "tests that vec2 / vec2 works", []() {
        return bool(vec2(1, 2)/vec2(3, 4) == vec2(1/3.0f, 2/4.0f));
    });

    runner.addTest("vec2 div float", "tests that vec2 / float works", []() {
        return bool(vec2(1, 2)/2.0f == vec2(1/2.0f, 2/2.0f));
    });

    runner.addTest("vec2 add equals vec2", "tests that vec2 += vec2 works", []() {
        vec2 a = vec2(1, 2);
        bool t = (a += vec2(3, 4)) == vec2(4, 6);
        return bool(a == vec2(4, 6)) && t;
    });

    runner.addTest("vec2 add equals float", "tests that vec2 += float works", []() {
        vec2 a = vec2(1, 2);
        bool t = (a += 1.0f) == vec2(2, 3);
        return bool(a == vec2(2, 3)) && t;
    });

    runner.addTest("vec2 subtract equals vec2", "tests that vec2 -= vec2 works", []() {
        vec2 a = vec2(1, 2);
        bool t = (a -= vec2(3, 4)) == vec2(-2, -2);
        return bool(a == vec2(-2, -2)) && t;
    });

    runner.addTest("vec2 subtract equals float", "tests that vec2 -= float works", []() {
        vec2 a = vec2(1, 2);
        bool t = (a -= 1.0f) == vec2(0, 1);
        return bool(a == vec2(0, 1)) && t;
    });

    runner.addTest("vec2 mul equals vec2", "tests that vec2 *= vec2 works", []() {
        vec2 a = vec2(1, 2);
        bool t = (a *= vec2(3, 4)) == vec2(3, 8);
        return bool(a == vec2(3, 8)) && t;
    });

    runner.addTest("vec2 mul equals float", "tests that vec2 *= float works", []() {
        vec2 a = vec2(1, 2);
        bool t = (a *= 2.0f) == vec2(2, 4);
        return bool(a == vec2(2, 4)) && t;
    });

    runner.addTest("vec2 div equals vec2", "tests that vec2 /= vec2 works", []() {
        vec2 a = vec2(1, 2);
        bool t = (a /= vec2(3, 4)) == vec2(1/3.0f, 2/4.0f);
        return bool(a == vec2(1/3.0f, 2/4.0f)) && t;
    });

    runner.addTest("vec2 div equals float", "tests that vec2 /= float works", []() {
        vec2 a = vec2(1, 2);
        bool t = (a /= 2.0f) == vec2(1/2.0f, 2/2.0f);
        return bool(a == vec2(1/2.0f, 2/2.0f)) && t;
    });

    runner.addTest("vec2 dot", "tests that dot(vec2, vec2) works", []() {
        return bool(vec2::dot(vec2(1, 2), vec2(2, 3)) == 8);
    });
    
    runner.addTest("vec2 anglebetween", "tests that anglebetween(vec2, vec2) works", []() {
        return approxequals(vec2::dot(vec2(1, 2), vec2(2, 3))/sqrt(vec2(1, 2).lengthSquared()*vec2(2, 3).lengthSquared()), cos(vec2::angleBetween(vec2(1, 2), vec2(2, 3))), 0.0001f);
    });

    runner.addTest("vec2 reflect", "tests that reflect(vec2, vec2) works", []() {
        vec2 n = vec2(2, 3).normalized();
        vec2 i = vec2(1, 2).normalized();
        vec2 r = vec2::reflect(i, n);
        return approxequals(vec2::dot(r, n), -vec2::dot(i, n), 0.01f);
    });

    runner.addTest("vec2 length", "tests that vec2.length() works", []() {
        vec2 a = vec2(2, 3);
        vec2 b = vec2(4, 6);
        vec2 c = vec2(6, 9);
        return approxequals(a.length() + b.length(), c.length(), 0.0001f);
    });

    runner.addTest("vec2 lengthSquared", "tests that vec2.lengthSquared() works", []() {
        vec2 a = vec2(2, 3);
        vec2 b = vec2(4, 6);
        vec2 c = vec2(6, 9);
        return approxequals(sqrtf(a.lengthSquared()) + sqrtf(b.lengthSquared()), sqrtf(c.lengthSquared()), 0.0001f);
    });

    runner.addTest("vec2 distanceSquared", "tests that distanceSquared(vec2, vec2) works", []() {
        vec2 a = vec2(2, 3);
        vec2 b = vec2(4, 6);
        vec2 c = vec2(6, 9);
        return bool(vec2::distanceSquared(a, b) == a.lengthSquared());
    });

    runner.addTest("vec2 cross", "tests that cross(vec2, vec2) works", []() {
        float a = vec2::cross(vec2(1, 2), vec2(2, 3));
        float b = vec3::cross(vec3(1, 2, 0), vec3(2, 3, 0)).z;
        //float b = mat2(vec2(1, 2), vec2(2, 3)).determinant();
        return bool(a == b);
    });

    runner.addTest("vec2 tangent", "tests that vec2::tangent is tangent to the source vector", []() {
        return bool(vec2::dot(vec2(1, 2), vec2(1, 2).tangent()) == 0);
    });

    runner.runTests();

    return 0;
}