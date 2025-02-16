#include <Testing.hpp>

Testing::TestRunner runner;

int main() { 
  runner.addTest("Unit test that intentionally fails", []() {return false;});

  runner.runTests();
}

PREPARETESTEXTERNALS(runner);