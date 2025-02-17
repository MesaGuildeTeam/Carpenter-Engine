#include <Game.hpp>

#include <UI/UIElement.hpp>
#include <UI/UILabel.hpp>
#include <UI/UIButton.hpp>
#include <UI/UIInput.hpp>

#include <iostream>

Engine::UI::UIInput* inputField;

void functionCallback() {
  std::cout << "Button clicked. Input is:\nint: " << inputField->getInputInt()
  << "\ndouble: " << inputField->getInputDouble()
  << "\nstring: " << inputField->getInputString()
  << std::endl;
}

class TestScene : public Engine::Scene {
  public:

    TestScene() : Engine::Scene("TestScene") {
      std::cout << "TEST: Creating test scene" << std::endl;

      AddChild((Engine::Node*)(new Engine::UI::UIElement("BaseUI")));
      ((Engine::UI::UIElement*)GetChild(0))->SetDimensions({500, 200});
      ((Engine::UI::UIElement*)GetChild(0))->SetOffset({0, 0});
      ((Engine::UI::UIElement*)GetChild(0))->SetAnchor("center");

      GetChild(0)->AddChild((Engine::Node*)(new Engine::UI::UILabel("Label", "Hello World")));
      GetChild(0)->AddChild((Engine::Node*)(new Engine::UI::UIButton("Button", "Click me", functionCallback)));
      ((Engine::UI::UIButton*)GetChild(0)->GetChild(1))->SetAnchor("topright");

      GetChild(0)->AddChild((Engine::Node*)(new Engine::UI::UIInput("Input", "This is a Test Input")));
      inputField = (Engine::UI::UIInput*)GetChild(0)->GetChild(2);
      inputField->SetAnchor("bottomleft");
    };

    void Draw() override {
      //std::cout << "Drawing scene" << std::endl;
      Engine::Node::Draw();
    };

    void Update(float dt) override {
      Engine::Node::Update(dt);
      //std::cout << "Updating scene" << std::endl;
    };
};

Engine::Game game = Engine::Game::getInstance(new TestScene());
