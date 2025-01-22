#include <Testing.hpp>

int main() {
  Testing::TestRunner runner;
  runner.addTest("Basic Unit Test", []() {return true;});

  runner.runTests();
  return 0;
}