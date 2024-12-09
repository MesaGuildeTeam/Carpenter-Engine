#include "Window.hpp"
#include <emscripten.h>

Engine::Window::Window() {
  EM_ASM(
    game.canvas = document.getElementById('canvas');
    game.uiContainer = document.getElementById('ui-layer');
    game.gl = game.canvas.getContext('webgl');
    game.ready = true;

    game.canvas.width = window.innerWidth;
    game.canvas.height = window.innerHeight;
  );
}

Engine::Window& Engine::Window::getWindow() {
  static Window instance;
  return instance;
}