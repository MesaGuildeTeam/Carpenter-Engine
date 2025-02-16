#include <Testing.hpp>

using namespace Testing;

TestRunner runner{TestRunner::getInstance()};

int main() {
  runner.addTest("Basic Unit Test", []() {return true;});

  runner.addTest("Add to 24-bit limit", []() {
    for (unsigned i = 0; i < 0xFFFFFF; i++);
    return true;
  });

  return 0;
}
