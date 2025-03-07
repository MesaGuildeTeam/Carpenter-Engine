#include "Testing.hpp"

Testing::TestRunner instance;

Testing::TestRunner& Testing::TestRunner::getInstance(std::string name) {
    if (instance.m_tests.size() == 0)
        instance.m_testName = name;
    
    return instance;
}

void Testing::TestRunner::addTest(std::string name, std::function<void()> test) {
    m_tests.push_back({name, test});
}

void Testing::TestRunner::runTests() {
    std::cout << "\n\x1b[1m" << m_testName << "\n\x1b[0m";
    for (Test& test : m_tests) {
        std::cout << test.name;

        auto start = std::chrono::high_resolution_clock::now();

        m_currentSuccess = true;
        test.test();

        auto end = std::chrono::high_resolution_clock::now();

        if (m_currentSuccess == true) {
            std::cout << " \x1B[32m[✓]\x1B[0m ";
            m_passedTests++;
        } else {
            std::cout << " \x1B[31m[X]\x1B[0m ";
        }

        std::cout << "\x1B[2m" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\x1B[0m" << std::endl;

        if (m_logs.size() != 0)
            PrintLogs();
    }
}

void Testing::TestRunner::DebugLog(std::string message) {
    m_logs.push_back("\x1b[2m" + message + "\x1b[0m");
}

void Testing::TestRunner::DebugError(std::string message) {
    m_currentSuccess = false;
    m_logs.push_back("\x1b[2;31m" + message + "\x1b[0m");
}

void Testing::TestRunner::Assert(bool condition, std::string message) {
    if (!condition) {
        DebugError(message);
    } 
}

void Testing::TestRunner::PrintLogs() {
    std::cout << "\x1B[2mLogs:\n";
    for (std::string log : m_logs)
        std::cout << log << std::endl;

    std::cout << "\x1B[0m";

    m_logs.clear();
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
