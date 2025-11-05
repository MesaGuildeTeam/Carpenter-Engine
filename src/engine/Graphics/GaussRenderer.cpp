#include "GaussRenderer.hpp"

#include <functional>
#include <emscripten/html5.h>
#include <GLES3/gl3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Engine::Graphics::GaussRenderer::GaussRenderer(const char* id): Engine::Graphics::Renderer::Renderer(id) {
    glDepthMask(GL_FALSE);
}

void Engine::Graphics::GaussRenderer::DrawMesh(Engine::Graphics::Mesh* mesh, Engine::Vec3f position, Engine::Vec3f scale, Engine::Vec3f rotation) {
  // Generate Data
  float* vertexBuffer = mesh->GetVertices();
  unsigned long vertexCount = mesh->GetVertexCount();

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


  // Bind and draw
  glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Engine::Graphics::Vertex),
    vertexBuffer, GL_DYNAMIC_DRAW);

  glDrawArrays(GL_POINTS, 0, vertexCount);
}