#include <Game.hpp>
#include <Input/InputManager.hpp>
#include <Input/Mouse.hpp>

#include <iostream>

using namespace Engine;

Input::Mouse& mouse{Input::Mouse::GetInstance()};

class ExampleScene : public Scene {
    private:

    Input::InputManager inputManager;
    
    public:
    ExampleScene() : Scene("ExampleScene") {
        inputManager.AddAxis("Horizontal", {'d'}, {'a'});
        inputManager.AddInput("Jump", {Input::KeyCodes::SPACE});
        inputManager.AddInput("MouseClick", {-1, 0});
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

        if (inputManager.GetInput("Jump")->IsPressed()) {
            std::cout << "Jump" << std::endl;
        }

        if (inputManager.GetInput("Jump")->IsReleased()) {
            std::cout << "Jump released" << std::endl;
        }

        if (inputManager.GetInput("MouseClick")->IsPressed()) {
            std::cout << "Mouse clicked at <" << mouse.GetPosition().x << ", " << mouse.GetPosition().y << ">" << std::endl;
        }

        if (inputManager.GetInput("MouseClick")->IsReleased()) {
            std::cout << "Mouse click released" << std::endl;
        }
    }
};

Game& game{Game::getInstance(new ExampleScene())};