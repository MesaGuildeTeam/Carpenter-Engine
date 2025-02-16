#include <Testing.hpp>

using namespace Testing;

TestRunner runner{TestRunner::getInstance()};

int main() {
  runner.addTest("Unit test that intentionally fails", []() {return false;});
}
