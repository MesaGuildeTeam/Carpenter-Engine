#include "Renderer.hpp"
#include <emscripten.h>
#include <iostream>

Engine::Renderer::Renderer(const char* id) {
  m_canvasId = id;

  EM_ASM({
    game.canvases[UTF8ToString($0)] = document.getElementById(UTF8ToString($0));
    game.gl[UTF8ToString($0)] = game.canvases[UTF8ToString($0)].getContext('webgl');
  }, m_canvasId);

  std::cout << "DEBUG: Canvas Initialized" << std::endl;
}

