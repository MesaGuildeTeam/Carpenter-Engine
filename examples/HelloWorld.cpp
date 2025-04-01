#include <Game.hpp>
#include <UI/UILabel.hpp>
#include <Graphics/Shapes.hpp>

using namespace Engine;

class CubeMesh : public Graphics::Mesh {
  public:

  CubeMesh() : Graphics::Mesh() {
    
  }
};

class ExampleScene : public Scene {
  private:
  Graphics::Cube mesh;
  Graphics::Texture texture;

  float time = 0;

  public:
  ExampleScene() : Scene("ExampleScene"), texture("Assets/placeholder.png") {
    UI::UILabel* label = new UI::UILabel("Label", "Hello World from Table Engine");
    AddChild(label);
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
