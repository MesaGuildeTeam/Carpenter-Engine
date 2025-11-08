/**
 * @file SoundTest.cpp
 * @brief Your basic spinning cube test
 * @author: Roberto Selles
 */

#include <Game.hpp>
#include <UI/UILabel.hpp>
#include <Graphics/Shapes.hpp>
#include <cmath>
#include <iostream>

using namespace Engine;

class ExampleScene : public Scene {
  private:
  Graphics::Cube mesh;
  
  Graphics::Texture color;
  Graphics::Texture normal;
  Graphics::Texture AO;
  //Graphics::Texture Specular;

  float time = 0;
  UI::UILabel label;

  public:
  ExampleScene() : Scene("ExampleScene"), color("Assets/Scifi_Hex_Wall_Albedo.jpg"),
  normal("Assets/Scifi_Hex_Wall_normal.jpg"), AO("Assets/Scifi_Hex_Wall_AO.jpg"),
  label("Label", "Hello World") {
    AddChild(&label);
  }

  void Draw() override {
    Scene::Draw();

    Game::getInstance().GetRenderer().UseTexture(color, GL_TEXTURE0);
    Game::getInstance().GetRenderer().UseTexture(AO, GL_TEXTURE1);
    Game::getInstance().GetRenderer().UseTexture(normal, GL_TEXTURE2);
    Game::getInstance().GetRenderer().DrawMesh(&mesh, {0, 0, 10}, {1, 1, 1},
      {-35, time, 0});
  }

  void Update(float dt) override {
    time += 2 * dt;
  }
};

Game& game{Game::getInstance(new ExampleScene())};
