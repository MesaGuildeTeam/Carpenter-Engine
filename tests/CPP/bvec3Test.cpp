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

    runner.addTest("bvec3 default constructor", []() {
        bvec3 v = bvec3();
        return !v.x && !v.y && !v.z;
    });

    runner.addTest("bvec3 fill constructor float", []() {
        bvec3 v = bvec3(true);
        return v.x && v.y && v.z;
    });

    runner.addTest("bvec3 fill constructor cast int", []() {
        bvec3 v = bvec3(1);
        return v.x && v.y && v.z;
    });

    runner.addTest("bvec3 concat constructor copy fill", []() {
        bvec3 v = bvec3(bvec2(1),0);
        return v.x && v.y && !v.z;
    });

    runner.addTest("bvec3 concat constructor copy copy", []() {
        bvec3 v1 = bvec3(0,1,0);
        bvec3 v = bvec3(v1);
        v1 = bvec3(0,1,1);
        cout << to_string(v);
        return !v.x && v.y && !v.z;
    });

    runner.addTest("bvec3 concat constructor copy cast", []() {
        bvec3 v = bvec3(bvec2(1), 1);
        return v.x && v.y && v.z;
    });

    runner.addTest("bvec3 concat constructor scalar", []() {
        bvec3 v = bvec3(1.0f, 0.0f, 1.0f);
        return v.x && !v.y && v.z;
    });

    runner.addTest("bvec3 concat constructor scalar cast", []() {
        bvec3 v = bvec3(1, true, 1.0f);
        return v.x && v.y && v.z;
    });

    runner.addTest("bvec3 concat constructor mixed", []() {
        bvec3 v = bvec3(0, vec2(1, 1));
        return !v.x && v.y && v.z;
    });

    runner.addTest("bvec3 assign test", []() {
        bvec3 a = bvec3(1, 0, 0);
        a = bvec3(1, 1, 1);
        return bool(a == bvec3(1, 1, 1));
    });

    runner.addTest("bvec3 and bvec3", []() {
        return bool((bvec3(1, 0, 0) && bvec3(1, 1, 0)) == bvec3(1, 0, 0));
    });

    runner.addTest("bvec3 and bool", []() {
        return bool((bvec3(1, 0, 0) && true) == bvec3(1, 0, 0));
    });

    runner.addTest("bvec3 or bvec3", []() {
        return bool(bvec3(1, 0, 0) || bvec3(1, 1, 0) == bvec3(1, 1, 0));
    });

    runner.addTest("bvec3 or bvec3", []() {
        return bool((bvec3(1, 0, 0) || true) == bvec3(1, 1, 1));
    });

    runner.addTest("not bvec3", []() {
        return bool((!bvec3(1, 0, 0)) == bvec3(0, 1, 1));
    });

    runner.addTest("bvec3 all", []() {
        return bool(!bvec3(1, 0, 0).all() && bvec3(1, 1, 1).all());
    });

    runner.addTest("bvec3 any", []() {
        return bool(bvec3(1, 0, 0).any() && !bvec3(0, 0, 0).any());
    });

    runner.addTest("bvec3 count", []() {
        return bool(bvec3(1, 0, 0).count() == 1);
    });

    runner.runTests();

    return 0;
}
