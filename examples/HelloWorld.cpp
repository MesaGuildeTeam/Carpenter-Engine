#include <Game.hpp>
#include <UI/UILabel.hpp>
#include <Graphics/Shapes.hpp>

using namespace Engine;

class ExampleScene : public Scene {
  private:
  Graphics::Cube mesh;
  Graphics::Texture texture;
  float time = 0;
  UI::UILabel label;

  public:
  ExampleScene() : Scene("ExampleScene"), texture("Assets/placeholder.png"), label("Label", "Hello World") {
    AddChild(&label);
  }

  void Draw() override {
    Scene::Draw();

    Game::getInstance().GetRenderer().UseTexture(texture, GL_TEXTURE0);
    Game::getInstance().GetRenderer().DrawMesh(&mesh, {0, 0, 10}, {1, 1, 1}, {-35, time, 0});
  }

  void Update(float dt) override {
    time += dt;
  }
};

Game game{Game::getInstance(new ExampleScene())};
