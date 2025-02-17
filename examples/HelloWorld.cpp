#include <Game.hpp>
#include <UI/UILabel.hpp>

using namespace Engine;

class ExampleScene : public Scene {
public:
  ExampleScene() : Scene("ExampleScene") {
    UI::UILabel* label = new UI::UILabel("Label", "Hello World from Table Engine");
    AddChild(label);
  }
};

Game game{Game::getInstance(new ExampleScene())};
