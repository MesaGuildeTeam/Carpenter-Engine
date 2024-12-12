#include <Game.hpp>
#include <Window.hpp>

#include <UI/UIElement.hpp>
#include <UI/UILabel.hpp>
#include <UI/UIButton.hpp>

#include <iostream>

void functionCallback() {
  std::cout << "Button clicked" << std::endl;
}

void functionCallback2() {
  std::cout << "Another Button clicked" << std::endl;
}

class TestScene : public Engine::Scene {
  public:

    TestScene() : Engine::Scene("TestScene") {
      std::cout << "TEST: Creating test scene" << std::endl;
      
      AddChild((Engine::Node*)(new Engine::UI::UIElement("BaseUI")));
      ((Engine::UI::UIElement*)GetChild(0))->SetDimensions({500, 200});

      GetChild(0)->AddChild((Engine::Node*)(new Engine::UI::UILabel("Label", "Hello World")));
      GetChild(0)->AddChild((Engine::Node*)(new Engine::UI::UIButton("Button", "Click me", functionCallback)));
      ((Engine::UI::UIButton*)GetChild(0)->GetChild(1))->SetAnchor("topright");
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

Engine::Window& window{Engine::Window::getWindow()};
Engine::Game game(new TestScene());

extern "C" {
  void CallDraw() { game.DrawScene(); }
  void CallUpdate() { game.UpdateScene(0.1f); }
}