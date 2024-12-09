#include "Game.hpp"
#include "Window.hpp"

Engine::Window& window{Engine::Window::getWindow()};
Engine::Game game;

extern "C" {
  void CallDraw() { game.DrawScene(); }
  void CallUpdate() { game.UpdateScene(0.1f); }
}