#include "Window.hpp"
#include <emscripten.h>
#include <iostream>

Engine::Window::Window() {
  std::cout << "Table Engine" << std::endl 
    << "C++ Game Engine that takes advantage of the web browser" << std::endl;
  std::cout << "DEBUG: Initializing window" << std::endl;

  EM_ASM(
    game.canvas = document.getElementById('canvas');
    game.uiContainer = document.getElementById('ui-layer');
    game.gl = game.canvas.getContext('webgl');
    game.ready = true;

    game.canvas.width = window.innerWidth;
    game.canvas.height = window.innerHeight;
  );

  std::cout << "DEBUG: Window initialized successfully" << std::endl;
}

Engine::Window& Engine::Window::getWindow() {
  static Window instance;
  return instance;
}