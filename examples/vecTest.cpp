#include <Game.hpp>
#include <functional>
#include <vector>

using namespace Engine;

class TestRunner {
    private:
    std::vector<std::pair<std::function<bool()>, std::string>> tests;

    public:

    void addTest(std::string name, std::function<bool()> test) {
        tests.push_back(std::pair(test, name));
    }

    bool runTests() {
        std::cout << "Running tests..." << std::endl;
        unsigned int testsPassed = 0;
        for (unsigned int i = 0; i < tests.size(); i++) {
            std::cout << "Running test \"" << tests[i].second << "\" (" << i << "/" << tests.size() << ") ..." << std::endl;
            if (tests[i].first()) {
                std::cout << "Test " << i << "/" << tests.size() << " passed." << std::endl;
                testsPassed++;
            } else {
                std::cout << "Test " << i << "/" << tests.size() << " failed." << std::endl;
            }
        }
        std::cout << testsPassed << "/" << tests.size() << "Tests passed." << std::endl;
        return testsPassed;
    }
};

int main() {
    TestRunner runner;

    runner.addTest("test pass", []() {
        return true;
    });

    runner.addTest("test fail", []() {
        return false;
    });

    runner.addTest("vec2 add", []() {
        return bool(vec2(1, 2) + vec2(3, 4) == vec2(4, 6));
    });

    runner.addTest("vec2 tangent", []() {
        return bool(vec2::cross(vec2(1, 2), vec2(1, 2).tangent()) == 0);
    });

    runner.runTests();

    return 0;
}