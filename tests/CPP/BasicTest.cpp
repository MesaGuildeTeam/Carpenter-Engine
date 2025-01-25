#include <Testing.hpp>

Testing::TestRunner runner;

int main() {
  runner.addTest("Basic Unit Test", []() {return true;});

  runner.addTest("Add to 24-bit limit", []() {
    for (unsigned i = 0; i < 0xFFFFFF; i++);
    return true;
  });

  runner.runTests();
  return 0;
}

PREPARETESTEXTERNALS(runner)