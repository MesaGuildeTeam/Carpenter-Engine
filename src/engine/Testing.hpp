/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

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

  /**
   * @brief A Unit tester used to run C++ unit tests
   * 
   * The goal of this class is to run C++ unit tests for WebAssembly.
   * This class is a singleton that is accessed with `Testing::TestRunner::getInstance()` and you
   * add tests with `Testing::TestRunner::addTest()`. 
   * These tests get processed and compiled to WASM before being run via JavaScript and running `table test`.
   * There are extern functions defined in the `Testing.cpp` file that you can access to run tests.
   * 
   * @warning This class is a singleton and should not be created manually.
   * It is a singleton that is accessed with `Testing::TestRunner::getInstance()`
   * and should be assigned to references of the class.
   * 
   * ## Example
   * ```cpp
   * #include <Testing.hpp>
   * 
   * using namespace Testing;
   * TestRunner& runner{TestRunner::getInstance("Basic Tests")};
   * 
   * int main() {
   *   runner.addTest("Add Two Numbers", []() {
   *       runner.Assert(2 + 2 == 4, "2 + 2 should equal 4!");
   *   });
   * 
   *   return 0;
   * }
   * ```
   * 
   * @author Roberto Selles
   * @author Armand Baril
   */
  class TestRunner {
      private:
      struct Test {
          std::string name;
          std::function<void()> test;
      };

      bool m_currentSuccess = true;

      std::vector<Test> m_tests;
      unsigned int m_passedTests = 0;
      std::string m_testName;

      std::vector<std::string> m_logs;

      public:

      /**
       * Returns an instance of the test runner
       * 
       * @warning When using its return value, make sure you are assigning it to a reference.
       * 
       * - What *not* to do: `Testing::TestRunner runner = Testing::TestRunner::getInstance();`
       * 
       * - What to do: `Testing::TestRunner& runner = Testing::TestRunner::getInstance();`
       */
      static TestRunner& getInstance(std::string name = "Test");

      /**
       * Adds a test to the test runner
       *
       * @param name The name of the test
       * @param test The test function
       */
      void addTest(std::string name, std::function<void()> test);

      /**
       * Runs all the tests, processes, and outputs the results.
       * This is called by the `table test` command so it is not meant to be called manually.
       */
      void runTests();

      /**
       * Logs a message to the test being run inside
       * Use this instead of `std::cout` to log messages inside tests
       * 
       * @param message The message to print
       */
      void DebugLog(std::string message);

      /**
       * Logs an error message to the test being run
       * 
       * @param message The message to print
       */
      void DebugError(std::string message);

      /**
       * Asserts that the condition is true. 
       * If the condition is false, an error message will be printed in the logs via `TestRunner::DebugError()`
       * 
       * ## Example
       * ```cpp
       * runner.Assert(2 + 2 == 4, "2 + 2 should equal 4!");
       * ```
       * 
       * @param condition The condition to assert
       * @param message The message to print
       */
      void Assert(bool condition, std::string message);

      /**
       * Prints and dequeues all the logs in the logs vector. This is called by `runTests()` after each test
       */
      void PrintLogs();

      /**
       * Returns the number of tests that have been run
       * 
       * @return unsigned int number of tests in the test runner
       */
      unsigned int getTestCount();

      /**
       * Returns the number of tests that have passed
       * 
       * @return unsigned int number of tests that have passed
       */
      unsigned int getPassedTestCount();
  };
};

#endif
