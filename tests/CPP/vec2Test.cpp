#include <Game.hpp>
#include <functional>
#include <vector>
#include <chrono>
#include <cmath>
#include <Testing.hpp>

using namespace Engine;

bool approxequals(float a, float b, float epsilon) {
    return abs(a - b) < epsilon;
}

Testing::TestRunner runner;

int main() {

    runner.addTest("vec2 default constructor", []() {
        vec2 v = vec2();
        return v.x == 0 && v.y == 0;
    });

    runner.addTest("vec2 fill constructor float", []() {
        vec2 v = vec2(3.14f);
        return v.x == 3.14f && v.y == 3.14f;
    });

    runner.addTest("vec2 fill constructor cast int", []() {
        vec2 v = vec2(3);
        return v.x == 3 && v.y == 3;
    });

    runner.addTest("vec2 concat constructor copy fill", []() {
        vec2 v = vec2(vec2(3));
        return v.x == 3 && v.y == 3;
    });

    runner.addTest("vec2 concat constructor copy copy", []() {
        vec2 v1 = vec2(3);
        vec2 v = vec2(v1);
        v1 = vec2(4);
        return v.x == 3 && v.y == 3;
    });

    runner.addTest("vec2 concat constructor copy cast", []() {
        vec2 v = vec2(bvec2(true));
        return v.x == 1 && v.y == 1;
    });

    runner.addTest("vec2 concat constructor scalar", []() {
        vec2 v = vec2(3.15f, 2.3f);
        return v.x == 3.15f && v.y == 2.3f;
    });

    runner.addTest("vec2 concat constructor scalar cast", []() {
        vec2 v = vec2(3, true);
        return v.x == 3 && v.y == 1.0f;
    });

    runner.addTest("vec2 assign test", []() {
        vec2 a = vec2(1, 2);
        a = vec2(4, 6);
        return bool(a == vec2(4, 6));
    });

    runner.addTest("vec2 add vec2", []() {
        return bool(vec2(1, 2) + vec2(3, 4) == vec2(4, 6));
    });

    runner.addTest("vec2 add float", []() {
        return bool(vec2(1, 2) + 1.0f == vec2(2, 3));
    });

    runner.addTest("vec2 subtract vec2", []() {
        return bool(vec2(1, 2) - vec2(3, 4) == vec2(-2, -2));
    });

    runner.addTest("vec2 subtract float", []() {
        return bool(vec2(1, 2) - 1.0f == vec2(0, 1));
    });

    runner.addTest("vec2 mul vec2", []() {
        return bool(vec2(1, 2)*vec2(3, 4) == vec2(3, 8));
    });

    runner.addTest("vec2 mul float", []() {
        return bool(vec2(1, 2)*2.0f == vec2(2, 4));
    });

    runner.addTest("vec2 div vec2", []() {
        return bool(vec2(1, 2)/vec2(3, 4) == vec2(1/3.0f, 2/4.0f));
    });

    runner.addTest("vec2 div float", []() {
        return bool(vec2(1, 2)/2.0f == vec2(1/2.0f, 2/2.0f));
    });

    runner.addTest("vec2 add equals vec2", []() {
        vec2 a = vec2(1, 2);
        bool t = (a += vec2(3, 4)) == vec2(4, 6);
        return bool(a == vec2(4, 6)) && t;
    });

    runner.addTest("vec2 add equals float", []() {
        vec2 a = vec2(1, 2);
        bool t = (a += 1.0f) == vec2(2, 3);
        return bool(a == vec2(2, 3)) && t;
    });

    runner.addTest("vec2 subtract equals vec2", []() {
        vec2 a = vec2(1, 2);
        bool t = (a -= vec2(3, 4)) == vec2(-2, -2);
        return bool(a == vec2(-2, -2)) && t;
    });

    runner.addTest("vec2 subtract equals float", []() {
        vec2 a = vec2(1, 2);
        bool t = (a -= 1.0f) == vec2(0, 1);
        return bool(a == vec2(0, 1)) && t;
    });

    runner.addTest("vec2 mul equals vec2", []() {
        vec2 a = vec2(1, 2);
        bool t = (a *= vec2(3, 4)) == vec2(3, 8);
        return bool(a == vec2(3, 8)) && t;
    });

    runner.addTest("vec2 mul equals float", []() {
        vec2 a = vec2(1, 2);
        bool t = (a *= 2.0f) == vec2(2, 4);
        return bool(a == vec2(2, 4)) && t;
    });

    runner.addTest("vec2 div equals vec2", []() {
        vec2 a = vec2(1, 2);
        bool t = (a /= vec2(3, 4)) == vec2(1/3.0f, 2/4.0f);
        return bool(a == vec2(1/3.0f, 2/4.0f)) && t;
    });

    runner.addTest("vec2 div equals float", []() {
        vec2 a = vec2(1, 2);
        bool t = (a /= 2.0f) == vec2(1/2.0f, 2/2.0f);
        return bool(a == vec2(1/2.0f, 2/2.0f)) && t;
    });

    runner.addTest("vec2 dot", []() {
        return bool(dot(vec2(1, 2), vec2(2, 3)) == 8);
    });
    
    runner.addTest("vec2 anglebetween", []() {
        return approxequals(dot(vec2(1, 2), vec2(2, 3))/sqrt(vec2(1, 2).lengthSquared()*vec2(2, 3).lengthSquared()), cos(angleBetween(vec2(1, 2), vec2(2, 3))), 0.0001f);
    });

    runner.addTest("vec2 reflect", []() {
        vec2 n = vec2(2, 3).normalized();
        vec2 i = vec2(1, 2).normalized();
        vec2 r = reflect(i, n);
        return approxequals(dot(r, n), -dot(i, n), 0.01f);
    });

    runner.addTest("vec2 length", []() {
        vec2 a = vec2(2, 3);
        vec2 b = vec2(4, 6);
        vec2 c = vec2(6, 9);
        return approxequals(a.length() + b.length(), c.length(), 0.0001f);
    });

    runner.addTest("vec2 lengthSquared", []() {
        vec2 a = vec2(2, 3);
        vec2 b = vec2(4, 6);
        vec2 c = vec2(6, 9);
        return approxequals(sqrtf(a.lengthSquared()) + sqrtf(b.lengthSquared()), sqrtf(c.lengthSquared()), 0.0001f);
    });

    runner.addTest("vec2 distanceSquared", []() {
        vec2 a = vec2(2, 3);
        vec2 b = vec2(4, 6);
        vec2 c = vec2(6, 9);
        return bool(distanceSquared(a, b) == a.lengthSquared());
    });

    runner.addTest("vec2 tangent", []() {
        return bool(dot(vec2(1, 2), vec2(1, 2).tangent()) == 0);
    });

    runner.runTests();

    return 0;
}

PREPARETESTEXTERNALS(runner);