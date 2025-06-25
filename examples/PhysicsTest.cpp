#include <Game.hpp>
#include <GameObject.hpp>
#include <Physics/World.hpp>
#include <Graphics/Shapes.hpp>
#include <iostream>

using namespace Engine;

class Ground : public GameObject {
  Graphics::Plane cube;

  public:
  Physics::Object phys;

  Ground() : GameObject("Ground"), phys(*this, 1, Physics::BoxMesh(10, 1, 10), true) {}

  void Init() override {
    Position = {0, -1, 10};
    Scale = {20, 1.5, 20};
  }

  void Draw() override {
    Game::getInstance().GetRenderer().DrawMesh(&cube, Position, Scale);
  }
};

class Ball : public GameObject {
  Graphics::Plane sphere;

  public:
  Physics::Object phys;

  Ball() : GameObject("Ball"), phys(*this, 1, Physics::SphereMesh(0.5)) {}

  void Init() override {
    Position = {0, 1, 10};
    Scale = {0.5, 0.5, 0.5};
  }

  void Draw() override {
    Game::getInstance().GetRenderer().DrawMesh(&sphere, Position, Scale);
  }
};

class TestScene : public Scene {
  private:
  Physics::World physWorld;
  Ground ground;
  Ball ball;

  public:
  TestScene() : Scene("TestScene"), physWorld({0, -0.981, 0}), ground() {
  }

  void Init() override {
    Scene::Init();
    AddChild(&ground);
    AddChild(&ball);

    physWorld.AddObject(&ball.phys);
    physWorld.AddObject(&ground.phys);
  }

  void Update(float dt) override {
    Scene::Update(dt);

    physWorld.Update(dt);
  }

  void Draw() override {
    Game::getInstance().GetRenderer().SetBackgroundColor({1.0f, 1.0f, 1.0f});
    Node::Draw();
  }
};

Game& game{Game::getInstance(new TestScene())};
