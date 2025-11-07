/**
 * @file SoundTest.cpp
 * @brief Your basic spinning cube test
 * @author: Roberto Selles
 */

#include <Game.hpp>
#include <UI/UILabel.hpp>
#include <UI/UIButton.hpp>
#include <UI/UIInput.hpp>
#include <Asset.hpp>
#include <cmath>
#include <iostream>

#include <emscripten.h>

using namespace Engine;

std::string data{""};

void SaveCallback() {
    oAsset asset("WriteTest.txt");
    asset.Write(data);
}

class ExampleScene : public Scene {
  private:
  UI::UIInput input;
  UI::UILabel output;
  UI::UIButton saveButton;

  public:
  ExampleScene() : Scene("ExampleScene"), input{"input", "Insert Text"}, output{"label", "Undefined Text"}, saveButton{"save", "Save", SaveCallback} {
  }

  void Init() override {
    AddChild(&input);
    AddChild(&output);
    AddChild(&saveButton);

    output.SetOffset(Vec2f{0, 40});
    saveButton.SetOffset(Vec2f{0, 80});

    iAsset readData("WriteTest.txt");

    while (!readData.IsOpen()) emscripten_sleep(0);
    std::cout << (int)readData.GetData()[0] << std::endl;
    if (readData.GetData()[0] != 0)
        output.SetText((const char*)readData.GetData());
  }

  void Draw() override {
    Scene::Draw();

  }

  void Update(float dt) override {
    Scene::Update(dt);

    data = input.getInputString();
  }
};

Game& game{Game::getInstance(new ExampleScene())};