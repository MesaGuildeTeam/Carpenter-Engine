#ifndef ENGINE_TESTRUNNER
#define ENGINE_TESTRUNNER

#include <vector>
#include <string>
#include <functional>
#include <chrono>
#include <iostream>

class TestRunner {
    private:
    struct Test {
        std::string name;
        std::string description;
        std::function<bool()> test;
    };

    std::vector<Test> tests;

    public:

    void addTest(std::string name, std::string description, std::function<bool()> test) {
        tests.push_back(Test{name, description, test});
    }

    bool runTests() {
        std::cout << "Running tests..." << std::endl;
        unsigned int testsPassed = 0;
        std::vector<Test> failed;
        for (unsigned int i = 0; i < tests.size(); i++) {
            std::cout << "Running test \"" << tests[i].name << "\" (" << i << "/" << tests.size() << ") ..." << std::endl;
            
            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
            
            bool res = tests[i].test();
            
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
            if (res) {
                std::cout << "Test " << i << "/" << tests.size() << " passed in " << elapsed << "ns." << std::endl;
                testsPassed++;
            } else {
                std::cout << "Test " << i << "/" << tests.size() << " failed in " << elapsed << "ns." << std::endl;
                failed.push_back(tests[i]);
            }
        }
        std::cout << testsPassed << "/" << tests.size() << "Tests passed." << std::endl;
        std::cout << "Failed tests:" << std::endl;
        for (unsigned int i = 0; i < failed.size(); i++) {
            std::cout << "  " << failed[i].name << ": " << failed[i].description << std::endl;
        }
        return testsPassed;
    }
};

#endif