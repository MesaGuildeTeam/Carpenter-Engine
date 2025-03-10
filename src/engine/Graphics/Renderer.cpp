#include "Renderer.hpp"
#include <emscripten/html5.h>
#include <iostream>
#include <GLES3/gl3.h>

// This is moved here to be initialized at renderer construction
std::unique_ptr<Engine::Graphics::Shader> Engine::Graphics::DefaultShader;

Engine::Graphics::Renderer::Renderer(const char* id) {
  EmscriptenWebGLContextAttributes attrs;
  emscripten_webgl_init_context_attributes(&attrs);
  attrs.alpha = EM_TRUE;
  attrs.depth = EM_TRUE;
  attrs.stencil = EM_FALSE;
  attrs.antialias = EM_TRUE;
  attrs.majorVersion = 2;

  // Generate the WebGL Context
  m_context = emscripten_webgl_create_context(id, &attrs);
  emscripten_webgl_make_context_current(m_context);
  m_id = id;

  EM_ASM({
    let name = UTF8ToString($0);
    game.canvases[UTF8ToString($0).split("#")[1]] = document.getElementById(UTF8ToString($0).split("#")[1]);
    game.gl[UTF8ToString($0).split("#")[1]] = game.canvases[UTF8ToString($0).split("#")[1]].getContext("webgl2");
  }, id);

  // Setup Clear Color
  glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
  glEnable(GL_DEPTH_TEST);

  Engine::Graphics::DefaultShader = std::unique_ptr<Engine::Graphics::Shader>(new Engine::Graphics::Shader());

  UseShader(DefaultShader.get());

  // Generate and configure buffers
  glGenBuffers(1, &m_vbo);
  glGenVertexArrays(1, &m_vao);
  glGenBuffers(1, &m_ebo);

  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBindVertexArray(m_vao);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  glEnableVertexAttribArray(0);

  std::cout << "DEBUG: Canvas Initialized with tag " << id << std::endl;
}

void Engine::Graphics::Renderer::ClearBuffer() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::Graphics::Renderer::DrawMesh(Engine::Graphics::Mesh* mesh) {
  // Generate Data
  float* vertexBuffer = mesh->GetVertices();
  unsigned short* indexBuffer = mesh->GetIndices();
  unsigned long indexCount = mesh->GetIndexCount();

  // Prepare Transformation Matrix Uniform
  int WindowDimensions[2] {0, 0}; // Width, Height... Fullscreen?
  emscripten_get_canvas_element_size(m_id, &WindowDimensions[0], &WindowDimensions[1]);
  int windowDimensionsSize = glGetUniformLocation(m_currentShaderProgram, "window");

  glUniform2f(windowDimensionsSize, WindowDimensions[0], WindowDimensions[1]);

  // Bind data
  glBufferData(GL_ARRAY_BUFFER, indexCount * sizeof(Vec3f), vertexBuffer, GL_DYNAMIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned short), indexBuffer, GL_STATIC_DRAW);
  //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3f), (void*)0);
  glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_SHORT, 0);
}

void Engine::Graphics::Renderer::UseShader(Shader* shader) {
  shader->Use();
  m_currentShaderProgram = shader->GetShaderProgram();
}