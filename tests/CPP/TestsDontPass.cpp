#include <Testing.hpp>

using namespace Testing;

TestRunner& runner{TestRunner::getInstance("Tests Don't Pass")};

int main() {
  runner.addTest("Unit test that intentionally fails", []() {return false;});

  return 0;
}
