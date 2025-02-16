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
    TestRunner runner = TestRunner("bvec2 class tester", "tests all methods of bvec2", "bvec2");

    runner.addTest("bvec2 default constructor", []() {
        bvec2 v = bvec2();
        return !v.x && !v.y;
    });

    runner.addTest("bvec2 fill constructor float", []() {
        bvec2 v = bvec2(true);
        return v.x && v.y;
    });

    runner.addTest("bvec2 fill constructor cast int", []() {
        bvec2 v = bvec2(1);
        return v.x && v.y;
    });

    runner.addTest("bvec2 concat constructor copy fill", []() {
        bvec2 v = bvec2(1,0);
        return v.x && !v.y;
    });

    runner.addTest("bvec2 concat constructor copy copy", []() {
        bvec2 v1 = bvec2(0,1);
        bvec2 v = bvec2(v1);
        v1 = bvec2(0,1);
        cout << to_string(v);
        return !v.x && v.y;
    });

    runner.addTest("bvec2 concat constructor copy cast", []() {
        bvec2 v = bvec2(bvec2(1));
        return v.x && v.y;
    });

    runner.addTest("bvec2 concat constructor scalar", []() {
        bvec2 v = bvec2(1.0f, 0.0f);
        return v.x && !v.y;
    });

    runner.addTest("bvec2 concat constructor scalar cast", []() {
        bvec2 v = bvec2(1, true);
        return v.x && v.y;
    });

    runner.addTest("bvec2 assign test", []() {
        bvec2 a = bvec2(1, 0);
        a = bvec2(1, 1);
        return bool(a == bvec2(1, 1));
    });

    runner.addTest("bvec2 and bvec2", []() {
        return bool((bvec2(1, 0) && bvec2(1, 1)) == bvec2(1, 0));
    });

    runner.addTest("bvec2 and bool", []() {
        return bool((bvec2(1, 0) && true) == bvec2(1, 0));
    });

    runner.addTest("bvec2 or bvec2", []() {
        return bool(bvec2(1, 0) || bvec2(1, 1) == bvec2(1, 1));
    });

    runner.addTest("bvec2 or bvec2", []() {
        return bool((bvec2(1, 0) || true) == bvec2(1, 1));
    });

    runner.addTest("not bvec2", []() {
        return bool((!bvec2(1, 0)) == bvec2(0, 1));
    });

    runner.addTest("bvec2 all", []() {
        return bool(!bvec2(1, 0).all() && bvec2(1, 1).all());
    });

    runner.addTest("bvec2 any", []() {
        return bool(bvec2(1, 0).any() && !bvec2(0, 0).any());
    });

    runner.addTest("bvec2 count", []() {
        return bool(bvec2(1, 0).count() == 1);
    });

    runner.runTests();

    return 0;
}