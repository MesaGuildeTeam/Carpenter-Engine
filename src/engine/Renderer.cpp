/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

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

