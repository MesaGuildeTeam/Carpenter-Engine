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
      std::string m_testName;

      public:

      static TestRunner& getInstance(std::string name = "Test");

      /**
       * Adds a test to the test runner
       *
       * @param name The name of the test
       * @param test The test function
       */
      void addTest(std::string name, std::function<bool()> test);

      /**
       *  Runs all the tests, processes, and outputs the results
       */
      void runTests();

      unsigned int getTestCount();

      unsigned int getPassedTestCount();
  };
};

#endif
