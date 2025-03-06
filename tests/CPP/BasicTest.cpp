#include <Testing.hpp>

using namespace Testing;

TestRunner& runner{TestRunner::getInstance("Basic Tests")};

int main() {
  runner.addTest("Return Successful Test", []() {
    runner.DebugLog("Hello World! This is a Debug Message!");
  
    return true;
  });

  runner.addTest("Add to 24-bit limit to test timing", []() {
    for (unsigned i = 0; i < 0xFFFFFF; i++);
    return true;
  });

  return 0;
}
