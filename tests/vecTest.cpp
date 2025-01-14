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