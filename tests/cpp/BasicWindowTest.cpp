#include <Game.hpp>
#include <Window.hpp>

#include <iostream>

class TestScene : public Engine::Scene {
  public:

    TestScene() : Engine::Scene("TestScene") {
      std::cout << "Creating test scene" << std::endl;
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