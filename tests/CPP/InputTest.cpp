#include <Testing.hpp>
#include <Input/Input.hpp>

using namespace Engine;

Testing::TestRunner& runner{Testing::TestRunner::getInstance("Input Class Tests")};
Input::Input TestInput;

int main() {
    
    runner.addTest("Initial Check", []() {
        TestInput.currentStrength = 0;
        TestInput.Update();
        return (TestInput.IsDown() == false);
    });

    runner.addTest("Press", []() {
        TestInput.currentStrength = 1;
        TestInput.Update();
        return (TestInput.IsDown() && TestInput.IsPressed() && !TestInput.IsReleased());
    });

    runner.addTest("Hold Down", []() {
        TestInput.currentStrength = 1;
        TestInput.Update();
        return (TestInput.IsDown() && !TestInput.IsPressed() && !TestInput.IsReleased());
    });
    
    runner.addTest("Release", []() {
        TestInput.currentStrength = 0;
        TestInput.Update();
        return (!TestInput.IsDown() && !TestInput.IsPressed() && TestInput.IsReleased());
    });

    runner.addTest("Wait", []() {
        TestInput.currentStrength = 0;
        TestInput.Update();
        return (!TestInput.IsDown() && !TestInput.IsPressed() && !TestInput.IsReleased());
    });
    
    return 0;
}