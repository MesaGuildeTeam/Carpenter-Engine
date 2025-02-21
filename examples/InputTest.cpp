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
        inputManager.AddInput("Jump", Input::Input(Input::KeyCodes::SPACE, -1, -1));
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

        if (inputManager.GetInput("Jump").IsPressed()) {
            std::cout << "Jump" << std::endl;
        }

        if (inputManager.GetInput("Jump").IsReleased()) {
            std::cout << "Jump released" << std::endl;
        }
    }
};

Game& game{Game::getInstance(new ExampleScene())};