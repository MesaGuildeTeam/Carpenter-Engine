#include "Testing.hpp"

Testing::TestRunner instance;

Testing::TestRunner& Testing::TestRunner::getInstance(std::string name) {
    if (instance.m_tests.size() == 0)
        instance.m_testName = name;
    
    return instance;
}

void Testing::TestRunner::addTest(std::string name, std::function<bool()> test) {
    m_tests.push_back({name, test});
}

void Testing::TestRunner::runTests() {
    std::cout << "\n" << m_testName << "\n";
    for (Test& test : m_tests) {
        std::cout << test.name;

        auto start = std::chrono::high_resolution_clock::now();

        bool result = test.test();

        auto end = std::chrono::high_resolution_clock::now();

        if (result) {
            std::cout << " \x1B[32mPASSED\x1B[0m ";
            m_passedTests++;
        } else {
            std::cout << " \x1B[31mFAILED\x1B[0m ";
        }

        std::cout << "\x1B[2m" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\x1B[0m" << std::endl;
    }
}

unsigned int Testing::TestRunner::getTestCount() {
    return m_tests.size();
}

unsigned int Testing::TestRunner::getPassedTestCount() {
    return m_passedTests;
}

extern "C" {
    void Testing_runTests() {
        instance.runTests();
    }

    unsigned Testing_getTestCount() {
        return instance.getTestCount();
    }

    unsigned Testing_getPassedTestCount() {
        return instance.getPassedTestCount();
    }
}
