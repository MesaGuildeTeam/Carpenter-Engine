#include <Game.hpp>
#include <UI/UILabel.hpp>

using namespace Engine;

class CubeMesh : public Graphics::Mesh {
  public:

  CubeMesh() : Graphics::Mesh() {
    AddQuad({-0.5, -0.5, 0, 0, 1}, {0.5, -0.5, 0, 1, 1}, {0.5, 0.5, 0, 1, 0}, {-0.5, 0.5, 0, 0, 0});
  }
};

class ExampleScene : public Scene {
  private:
  CubeMesh mesh;
  Graphics::Texture texture;
  
  public:
  ExampleScene() : Scene("ExampleScene"), texture("Assets/placeholder.png") {
    UI::UILabel* label = new UI::UILabel("Label", "Hello World from Table Engine");
    AddChild(label);
  }

  void Draw() override {
    Scene::Draw();

    Game::getInstance().GetRenderer().UseTexture(texture, GL_TEXTURE0);
    Game::getInstance().GetRenderer().DrawMesh(&mesh, {0, 0, 0}, {1, 1, 1}, {45, 45, 0});
  }
};

Game game{Game::getInstance(new ExampleScene())};
