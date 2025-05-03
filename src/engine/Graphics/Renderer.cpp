/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "Renderer.hpp"
#include <emscripten/html5.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Engine::Camera DefaultCamera("DefaultCamera", 1.0f);

// This is moved here to be initialized at renderer construction

Engine::Graphics::Renderer::Renderer(const char* id) : m_camera(&DefaultCamera) {
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
    game.canvases[UTF8ToString($0)] = document.getElementById(UTF8ToString($0));
    game.gl[UTF8ToString($0)] = game.canvases[UTF8ToString($0)]
      .getContext("webgl2");
  }, id);

  // Setup Clear Color and default render settings
  // Color is apprximately #181818ff
  glClearColor(0.094f, 0.094f, 0.094f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glEnable(GL_CULL_FACE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glFrontFace(GL_CCW);

  // Generate and configure buffers
  glGenBuffers(1, &m_vbo);
  glGenVertexArrays(1, &m_vao);
  glGenBuffers(1, &m_ebo);

  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBindVertexArray(m_vao);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  std::cout << "DEBUG: Canvas Initialized with tag " << id << std::endl;
  UseShader(DefaultShader());
}

void Engine::Graphics::Renderer::ClearBuffer() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::Graphics::Renderer::DrawMesh(Engine::Graphics::Mesh* mesh,
  Engine::Vec3f position, Engine::Vec3f scale, Engine::Vec3f rotation) {
  // Generate Data
  float* vertexBuffer = mesh->GetVertices();
  unsigned long vertexCount = mesh->GetVertexCount();
  unsigned short* indexBuffer = mesh->GetIndices();
  unsigned long indexCount = mesh->GetIndexCount();

  // Prepare Transformation uniforms

  // Window Dimensions
  int WindowDimensions[2] {0, 0}; // Width, Height
  emscripten_get_canvas_element_size(m_id, &WindowDimensions[0], &WindowDimensions[1]);
  int windowDimensionsSize = glGetUniformLocation(m_currentShaderProgram, "u_Window");
  glUniform2f(windowDimensionsSize, WindowDimensions[0], WindowDimensions[1]);

  float FOV = m_camera->getFOV();

  // Object Transformation Matrix
  glm::mat4 transformationMatrix = glm::mat4(1.0f);

  transformationMatrix = glm::translate(transformationMatrix,
    glm::vec3(position.x, position.y, position.z)); // position

  transformationMatrix = glm::rotate(transformationMatrix, glm::radians(rotation.x),
    glm::vec3(1.0f, 0.0f, 0.0f)); // rotation
  transformationMatrix = glm::rotate(transformationMatrix, glm::radians(rotation.y),
    glm::vec3(0.0f, 1.0f, 0.0f)); // rotation
  transformationMatrix = glm::rotate(transformationMatrix, glm::radians(rotation.z),
    glm::vec3(0.0f, 0.0f, 1.0f)); // rotation

  transformationMatrix = glm::scale(transformationMatrix,
    glm::vec3(scale.x, scale.y, scale.z)); // scale

  int transformUniform = glGetUniformLocation(m_currentShaderProgram, "u_Transform");
  glUniformMatrix4fv(transformUniform, 1, GL_FALSE, &transformationMatrix[0][0]);

  // Camera Position Matrix
  Vec3f camPos = m_camera->GetGlobalPosition();
  Vec3f camRot = m_camera->GetGlobalRotation();

  glm::mat4 cameraMatrix = glm::mat4(1.0f);
  cameraMatrix = glm::rotate(cameraMatrix, glm::radians(camRot.x),
    glm::vec3(1.0f, 0.0f, 0.0f)); // rotation
  cameraMatrix = glm::rotate(cameraMatrix, glm::radians(camRot.y),
    glm::vec3(0.0f, 1.0f, 0.0f)); // rotation
  cameraMatrix = glm::rotate(cameraMatrix, glm::radians(camRot.z),
    glm::vec3(0.0f, 0.0f, 1.0f)); // rotation
  cameraMatrix = glm::scale(cameraMatrix, glm::vec3(1.0f / FOV, 
    1.0f / FOV, 1.0f / FOV)); // scale


  cameraMatrix = glm::translate(cameraMatrix, glm::vec3(camPos.x / FOV, 
    camPos.y / FOV, camPos.z / FOV)); // position


  int cameraUniform = glGetUniformLocation(m_currentShaderProgram, "u_Camera");
  glUniformMatrix4fv(cameraUniform, 1, GL_FALSE, &cameraMatrix[0][0]);

  // Bind data
  glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Engine::Graphics::Vertex),
    vertexBuffer, GL_DYNAMIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned short),
    indexBuffer, GL_DYNAMIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Engine::Graphics::Vertex),
    (void*)0); // position
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Engine::Graphics::Vertex),
    (void*)(sizeof(float) * 3)); // texture coordinates
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Engine::Graphics::Vertex),
    (void*)(sizeof(float) * 5)); // normal

  glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_SHORT, 0);
}

void Engine::Graphics::Renderer::UseShader(Shader& shader) {
  m_currentShaderProgram = shader.GetShaderProgram();
  glUseProgram(m_currentShaderProgram);
}

void Engine::Graphics::Renderer::UseTexture(Engine::Graphics::Texture& texture,
  unsigned int textureSlot) {
  glActiveTexture(textureSlot);
  glBindTexture(GL_TEXTURE_2D, texture.GetTexture());
}

void Engine::Graphics::Renderer::UseMaterial(Engine::Graphics::Material* material) {
  UseShader(*material->GetShader());
  material->ApplyMaterialParams();
}

void Engine::Graphics::Renderer::SetCameraReference(Engine::Camera& camera) {
  m_camera = &camera;
}

void Engine::Graphics::Renderer::SetBackgroundColor(Vec3f color) {
  glClearColor(color.x, color.y, color.z, 1.0f);
}
