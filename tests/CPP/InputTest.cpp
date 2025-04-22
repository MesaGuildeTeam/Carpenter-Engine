#include <Testing.hpp>
#include <Input/Input.hpp>

using namespace Engine;

Testing::TestRunner& runner{Testing::TestRunner::getInstance("Input Class Tests")};
Input::Input TestInput;

int main() {
    
    runner.addTest("Initial Check", []() {
        runner.DebugLog("Input class size: " + std::to_string(sizeof(Input::Input)) + " bytes");
        TestInput.currentStrength = 0;
        TestInput.Update();
        runner.Assert(TestInput.IsDown() == false, "Input does not start off released! IsDown() != false");
    });

    runner.addTest("Press", []() {
        TestInput.currentStrength = 1;
        TestInput.Update();
        runner.Assert(TestInput.IsDown() && TestInput.IsPressed() && !TestInput.IsReleased(), "Press is not updated correctly!");
    });

    runner.addTest("Hold Down", []() {
        TestInput.currentStrength = 1;
        TestInput.Update();
        runner.Assert(TestInput.IsDown() && !TestInput.IsPressed() && !TestInput.IsReleased(), "Hold is not updated correctly!");
    });
    
    runner.addTest("Release", []() {
        TestInput.currentStrength = 0;
        TestInput.Update();
        runner.Assert(!TestInput.IsDown() && !TestInput.IsPressed() && TestInput.IsReleased(), "Release is not updated correctly!");
    });

    runner.addTest("Wait", []() {
        TestInput.currentStrength = 0;
        TestInput.Update();
        runner.Assert(!TestInput.IsDown() && !TestInput.IsPressed() && !TestInput.IsReleased(), "Wait is not updated correctly!");
    });
    
    return 0;
}