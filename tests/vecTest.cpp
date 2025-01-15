#include <Game.hpp>
#include <functional>
#include <vector>
#include <chrono>
#include "TestRunner.hpp"

using namespace Engine;

int main() {
    TestRunner runner;

    runner.addTest("test pass", "tests that the tester passes when the return is true", []() {
        return true;
    });

    runner.addTest("test fail", "tests that the tester fails when the return is false", []() {
        return false;
    });

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
        return v.x == 3 && v.y == 3;
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

    runner.addTest("vec2 add", "tests that vec2 + vec2 works", []() {
        return bool(vec2(1, 2) + vec2(3, 4) == vec2(4, 6));
    });

    vec4 v1 = vec4(vec2(1, 2), 3, 4);

    runner.addTest("vec2 tangent", "tests that vec2::tangent is tangent to the source vector", []() {
        return bool(vec2::cross(vec2(1, 2), vec2(1, 2).tangent()) == 0);
    });

    runner.runTests();

    return 0;
}