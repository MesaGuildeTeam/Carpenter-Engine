#include <Game.hpp>
#include <Input/InputManager.hpp>
#include <iostream>

using namespace Engine;

class ExampleScene : public Scene {
    private:

    Input::InputManager inputManager;
    
    public:
    ExampleScene() : Scene("ExampleScene") {
        inputManager.AddAxis("Horizontal", Input::Input('d', -1, -1), Input::Input('a', -1, -1));
    }

    void Update(float dt) override {
        Engine::Node::Update(dt);

        inputManager.Update();

        if (inputManager.GetAxis("Horizontal") > 0) {
            std::cout << "Right" << std::endl;
        }

        if (inputManager.GetAxis("Horizontal") < 0) {
            std::cout << "Left" << std::endl;
        }
    }
};

Game& game{Game::getInstance((Scene*)new ExampleScene())};

extern "C" {
    void CallDraw() {game.DrawScene(); }
    void CallUpdate(float dt) { game.UpdateScene(dt); }
}