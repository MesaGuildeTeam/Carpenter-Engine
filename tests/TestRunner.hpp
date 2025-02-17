#ifndef ENGINE_TESTRUNNER
#define ENGINE_TESTRUNNER

#include <vector>
#include <string>
#include <functional>
#include <chrono>
#include <iostream>

/**
 * A unit tester
 */
class TestRunner {
    private:

    std::string name;
    std::string description;
    std::string path;

    struct Test {
        std::string name;
        std::function<bool()> test;
    };

    std::vector<Test> tests;

    public:

    /**
     * creates a test runner
     * @param name the name of the test runner
     * @param description a description of the test runner
     * @param outputpath the file to write the output to
     */
    TestRunner(std::string name, std::string description, std::string outputpath){
        this -> name = name;
        this -> description = description;
        this -> path = outputpath;
    }

    /**
     * adds a test to the runner
     * @param name name of the test
     * @param description desription of the test
     * @param test function to run as the test, returns bool
     */
    void addTest(std::string name, std::function<bool()> test) {
        tests.push_back(Test{name, test});
    }

    /**
     * runs all tests
     */
    bool runTests() {
        std::cout << "Running tests..." << std::endl;
        unsigned int testsPassed = 0;
        std::vector<Test> failed;
        for (unsigned int i = 0; i < tests.size(); i++) {
            std::cout << "Running test \"" << tests[i].name << "\" (" << i << "/" << tests.size() << ") ..." << std::endl;
            
            auto begin = std::chrono::high_resolution_clock::now();
            
            bool res = tests[i].test();
            
            auto end = std::chrono::high_resolution_clock::now();

            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
            if (res) {
                std::cout << "Test " << i << "/" << tests.size() << " passed in " << elapsed << "ns." << std::endl;
                testsPassed++;
            } else {
                std::cout << "Test " << i << "/" << tests.size() << " failed in " << elapsed << "ns." << std::endl;
                failed.push_back(tests[i]);
            }
        }
        std::cout << testsPassed << "/" << tests.size() << " Tests passed." << std::endl;
        if (failed.size() != 0){
            std::cout << "Failed tests:" << std::endl;
            for (unsigned int i = 0; i < failed.size(); i++) {
                std::cout << "  " << failed[i].name << ": " << std::endl;
            }
        }
        return testsPassed;
    }
};

#endif