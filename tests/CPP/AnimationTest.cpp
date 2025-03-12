#include <Testing.hpp>
#include <Animation/Animated.hpp>

Testing::TestRunner& runner = Testing::TestRunner::getInstance("Animation Tests");

int main() {
    runner.addTest("Animation Test", []() {

        Animated anvar;
        anvar.assignValues(1);
        anvar.assignValues(2);
        anvar.assignValues(3);
        anvar.assignValues(4);
        anvar.assignValues(5);

        std::cout << "\nCURRENT KEYFRAME: ";
        std::cout << anvar.getCurrentValue();
        std::cout << "\nKEYFRAMES:\n";
        anvar.printKeyframes();
        std::cout << "\nDELTA TIME: ";
        anvar.printDeltaTime();
        std::cout << "ARRAY SIZE: ";
        anvar.printArraySize();

        return true;
    });

    return 0;
}