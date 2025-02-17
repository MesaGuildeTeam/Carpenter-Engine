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
    
    runner.addTest("bvec4 default constructor", []() {
        bvec4 v = bvec4();
        return !v.x && !v.y && !v.z && !v.w;
    });

    runner.addTest("bvec4 fill constructor float", []() {
        bvec4 v = bvec4(true);
        return v.x && v.y && v.z && v.w;
    });

    runner.addTest("bvec4 fill constructor cast int", []() {
        bvec4 v = bvec4(1);
        return v.x && v.y && v.z && v.w;
    });

    runner.addTest("bvec4 concat constructor copy fill", []() {
        bvec4 v = bvec4(bvec3(1),0);
        return v.x && v.y && v.z && !v.w;
    });

    runner.addTest("bvec4 concat constructor copy copy", []() {
        bvec4 v1 = bvec4(0,1,0,0);
        bvec4 v = bvec4(v1);
        v1 = bvec4(0,1,1,0);
        cout << to_string(v);
        return !v.x && v.y && !v.z && !v.w;
    });

    runner.addTest("bvec4 concat constructor copy cast", []() {
        bvec4 v = bvec4(bvec2(1), 1, 0);
        return v.x && v.y && v.z && !v.w;
    });

    runner.addTest("bvec4 concat constructor scalar", []() {
        bvec4 v = bvec4(1.0f, 0.0f, 1.0f, 1.0f);
        return v.x && !v.y && v.z && v.w;
    });

    runner.addTest("bvec4 concat constructor scalar cast", []() {
        bvec4 v = bvec4(1, true, 1.0f, 0);
        return v.x && v.y && v.z && !v.w;
    });

    runner.addTest("bvec4 concat constructor mixed", []() {
        bvec4 v = bvec4(0, vec2(1, 1), 0);
        return !v.x && v.y && v.z && !v.w;
    });

    runner.addTest("bvec4 assign test", []() {
        bvec4 a = bvec4(1, 0, 0, 1);
        a = bvec4(1, 1, 1, 0);
        return bool(a == bvec4(1, 1, 1, 0));
    });

    runner.addTest("bvec4 and bvec4", []() {
        return bool((bvec4(1, 0, 0, 1) && bvec4(1, 1, 0, 0)) == bvec4(1, 0, 0, 0));
    });

    runner.addTest("bvec4 and bool", []() {
        return bool((bvec4(1, 0, 0, 1) && true) == bvec4(1, 0, 0, 1));
    });

    runner.addTest("bvec4 or bvec4", []() {
        return bool(bvec4(1, 0, 0, 1) || bvec4(1, 1, 0, 0) == bvec4(1, 1, 0, 1));
    });

    runner.addTest("bvec4 or bvec4", []() {
        return bool((bvec4(1, 0, 0, 1) || true) == bvec4(1, 1, 1, 1));
    });

    runner.addTest("not bvec4", []() {
        return bool((!bvec4(1, 0, 0, 1)) == bvec4(0, 1, 1, 0));
    });

    runner.addTest("bvec4 all", []() {
        return bool(!bvec4(1, 0, 0, 1).all() && bvec4(1, 1, 1, 1).all());
    });

    runner.addTest("bvec4 any", []() {
        return bool(bvec4(1, 0, 0, 1).any() && !bvec4(0, 0, 0, 0).any());
    });

    runner.addTest("bvec4 count", []() {
        return bool(bvec4(1, 0, 0, 1).count() == 2);
    });

    runner.runTests();

    return 0;
}

PREPARETESTEXTERNALS(runner);