#include "Renderer.hpp"
#include <emscripten/html5.h>
#include <iostream>
#include <GLES2/gl2.h>

Engine::Graphics::Renderer::Renderer(const char* id) {
  EmscriptenWebGLContextAttributes attrs;
  emscripten_webgl_init_context_attributes(&attrs);
  attrs.alpha = EM_TRUE;
  attrs.depth = EM_TRUE;
  attrs.stencil = EM_FALSE;
  attrs.antialias = EM_TRUE;
  attrs.majorVersion = 2;

  m_context = emscripten_webgl_create_context(id, &attrs);
  emscripten_webgl_make_context_current(m_context);

  EM_ASM({
    let name = UTF8ToString($0);
    game.canvases[UTF8ToString($0).split("#")[1]] = document.getElementById(UTF8ToString($0).split("#")[1]);
  }, id);

  glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
  glEnable(GL_DEPTH_TEST);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  std::cout << "DEBUG: Canvas Initialized with tag " << id << std::endl;
}

void Engine::Graphics::Renderer::ClearBuffer() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

