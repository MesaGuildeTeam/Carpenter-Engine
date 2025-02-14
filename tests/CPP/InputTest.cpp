#include <Testing.hpp>
#include <Input/Input.hpp>

using namespace Engine;

Testing::TestRunner runner;
Input::Input TestInput;

int main() {
    
    runner.addTest("Initial Check", []() {
        TestInput.Update(0);
        return (TestInput.IsDown() == false);
    });

    runner.addTest("Press", []() {
        TestInput.Update(1);
        return (TestInput.IsDown() && TestInput.IsPressed() && !TestInput.IsReleased());
    });

    runner.addTest("Hold Down", []() {
        TestInput.Update(1);
        return (TestInput.IsDown() && !TestInput.IsPressed() && !TestInput.IsReleased());
    });
    
    runner.addTest("Release", []() {
        TestInput.Update(0);
        return (!TestInput.IsDown() && !TestInput.IsPressed() && TestInput.IsReleased());
    });

    runner.addTest("Wait", []() {
        TestInput.Update(0);
        return (!TestInput.IsDown() && !TestInput.IsPressed() && !TestInput.IsReleased());
    });
    
    runner.runTests();
    return 0;
}

PREPARETESTEXTERNALS(runner);