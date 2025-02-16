#include "Testing.hpp"

Testing::TestRunner& Testing::TestRunner::getInstance() {
    static TestRunner instance;
    return instance;
}

void Testing::TestRunner::addTest(std::string name, std::function<bool()> test) {
    m_tests.push_back({name, test});
}

void Testing::TestRunner::runTests() {
    std::cout << STRINGIFY(TESTNAME) << "\n";
    for (Test& test : m_tests) {
        std::cout << test.name;

        auto start = std::chrono::high_resolution_clock::now();

        bool result = test.test();

        auto end = std::chrono::high_resolution_clock::now();

        if (result) {
            std::cout << " PASSED ";
            m_passedTests++;
        } else {
            std::cout << " FAILED ";
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
        Testing::TestRunner::getInstance().runTests();
    }

    unsigned Testing_getTestCount() {
        return Testing::TestRunner::getInstance().getTestCount();
    }

    unsigned Testing_getPassedTestCount() {
        return Testing::TestRunner::getInstance().getPassedTestCount();
    }
}
