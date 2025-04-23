/**
 * @file SoundTest.cpp
 * @brief Basic UI test scene for the game engine
 * @author: Roberto Selles
 */

#include <Game.hpp>

#include <UI/UIElement.hpp>
#include <UI/UILabel.hpp>
#include <UI/UIButton.hpp>
#include <UI/UIInput.hpp>

#include <iostream>

using namespace Engine;

UI::UIInput* inputField;

void functionCallback() {
  std::cout << "Button Clicked. Input is:" << std::endl
    << "int: " << inputField->getInputInt() << std::endl
    << "double: " << inputField->getInputDouble() << std::endl
    << "string: " << inputField->getInputString() << std::endl;
}

class TestScene : public Scene {
  public:
  UI::UIElement Base{UI::UIElement("BaseUI")};
  UI::UILabel Label{UI::UILabel("Label", "Hello World")};
  UI::UIButton Button{UI::UIButton("Button", "Click me", functionCallback)};
  UI::UIInput Input{UI::UIInput("Input", "This is a Test Input")};

  TestScene() : Scene("TestScene") {
    std::cout << "TEST: Creating test scene" << std::endl;
    AddChild(&Base);
    Base.SetDimensions({500, 200});
    Base.SetOffset({0, 0});
    Base.SetAnchor("center");

    Base.AddChild(&Label);
    Base.AddChild(&Button);
    Base.AddChild(&Input);

    Button.SetAnchor("topright");
    Input.SetAnchor("bottomleft");

    inputField = &Input;
  };
};

Game& game{Game::getInstance(new TestScene())};