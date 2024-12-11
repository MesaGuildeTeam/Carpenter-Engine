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
      std::cout << "Creating test scene" << std::endl;
      AddChild((Engine::Node*)(new Engine::UI::UIElement("BaseUI")));

      GetChild(0)->AddChild((Engine::Node*)(new Engine::UI::UILabel("Label", "Hello World")));
      GetChild(0)->AddChild((Engine::Node*)(new Engine::UI::UIButton("Button", "Click me", functionCallback)));
      GetChild(0)->AddChild((Engine::Node*)(new Engine::UI::UIButton("Button2", "Click me 2", functionCallback2)));
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