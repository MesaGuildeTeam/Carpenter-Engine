#ifndef ENGINE_TESTRUNNER
#define ENGINE_TESTRUNNER

#define STRINGIFY(A) #A
#define EXPAND(A) STRINGIFY(A)

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

      unsigned int m_passedTests = 0;
  
      std::vector<Test> m_tests;
  
      public:
  
      void addTest(std::string name, std::function<bool()> test) {
          m_tests.push_back(Test{name, test});
      }
  
      void runTests() {
          std::cout << EXPAND(TESTNAME) << "\n";
          
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

            std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
          }
      }
  };
};

#endif