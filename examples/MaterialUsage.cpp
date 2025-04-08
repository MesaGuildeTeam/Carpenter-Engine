#include <Game.hpp>
#include <iostream>
#include <Graphics/Shapes.hpp>

using namespace Engine;

class ExampleScene : public Scene {
  private:
  Graphics::Plane mesh;
  Graphics::Shader shader;
  Graphics::Material material;
  
  public:
  float time = 0;

  ExampleScene() : Scene("ExampleScene"), shader("Assets/red_green.frag"),
  material(&shader) {
    material.CreateParameter("time", Graphics::MaterialParameterType::FLOAT);
    material.SetParameter("time", &time);
  }

  void Update(float dt) override {
    time += dt;
    Game::getInstance().GetRenderer().SetBackgroundColor({1, 1, 1});
  }

  void Draw() override {
    Game::getInstance().GetRenderer().UseMaterial(&material);
    Game::getInstance().GetRenderer().DrawMesh(&mesh, {0, 0, 0}, {0.5, 0.5, 0.5});
  }
  
};

Game game{Game::getInstance(new ExampleScene())};