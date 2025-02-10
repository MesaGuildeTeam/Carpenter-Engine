/** */

#ifndef ENGINE_TESTRUNNER
#define ENGINE_TESTRUNNER

#define EXPAND(A) #A
#define STRINGIFY(A) EXPAND(A)

#include <vector>
#include <string>
#include <functional>
#include <chrono>
#include <iostream>

namespace Testing {
  class TestRunner {
      private:
      struct Test {
          std::string name;
          std::function<bool()> test;
      };

      std::vector<Test> m_tests;
      unsigned int m_passedTests = 0; 
  
      public:

      /**
       * Adds a test to the test runner
       * 
       * @param name The name of the test
       * @param test The test function
       */ 
      void addTest(std::string name, std::function<bool()> test) {
          m_tests.push_back(Test{name, test});
      }

      /**
       *  Runs all the tests, processes, and outputs the results
       */ 
      void runTests() {
          std::cout << STRINGIFY(TESTNAME) << "\n";
          
          for (Test& test : m_tests) {
            std::cout << test.name;

            auto start = std::chrono::high_resolution_clock::now();

            bool result = test.test();

            auto end = std::chrono::high_resolution_clock::now();

            if (test.test()) {
              std::cout << " PASSED ";
              m_passedTests++;
            } else {
              std::cout << " FAILED ";
            }

            std::cout << "\x1B[2m" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\x1B[0m" << std::endl;
          }
      }

      unsigned int getTestCount() {
        return m_tests.size();
      }

      unsigned int getPassedTestCount() {
        return m_passedTests;
      }
  };
};

#define PREPARETESTEXTERNALS(TEST) \
extern "C" { \
  unsigned getTestCount() { \
    return TEST.getTestCount(); \
  } \
  unsigned getPassedTestCount() { \
    return TEST.getPassedTestCount(); \
  } \
}

#endif