/**
 * @file SoundTest.cpp
 * @brief Your basic spinning cube test
 * @author: Roberto Selles
 */

#include <Game.hpp>
#include <UI/UILabel.hpp>
#include <Graphics/Shapes.hpp>
#include <Graphics/Line.hpp>
#include <cmath>
#include <iostream>

using namespace Engine;

Engine::Vec3f circleFunction(float t) {
  std::cout << "computing sin/cos of " << t << std::endl;
  return {cosf(t), sinf(t), t};
};

class ExampleScene : public Scene {
  private:
  Graphics::Line mesh;
  Graphics::Texture texture;
  float time = 0;
  UI::UILabel label;

  public:
  ExampleScene() : Scene("ExampleScene"), texture("Assets/placeholder.png"),
  label("Label", "Hello World"), mesh(circleFunction, -1.0f, 1.0f, 0.1f, 0.1f) {
    AddChild(&label);
  }

  void Draw() override {
    Scene::Draw();

    //Game::getInstance().GetRenderer().UseTexture(texture, GL_TEXTURE0);
    Game::getInstance().GetRenderer().DrawMesh(&mesh, {0, 0, 10}, {0.5, 0.5, 0.5},
      {-35, time, 0});
  }

  void Update(float dt) override {
    time += 2 * dt;
  }
};

Game& game{Game::getInstance(new ExampleScene())};
