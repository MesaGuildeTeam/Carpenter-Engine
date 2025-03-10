#include "Shader.hpp"
#include <GLES2/gl2.h>

const char* defaultVertexShader {
  "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "void main()\n"
  "{\n"
  "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
  "}\0"
};

const char* defaultFragmentShader {
  "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
  "}\0"
};

Engine::Graphics::Shader Engine::Graphics::DefaultShader;

Engine::Graphics::Shader::Shader() : Shader(defaultFragmentShader, defaultVertexShader) {}

Engine::Graphics::Shader::Shader(const char* frag) : Shader(frag, defaultVertexShader) {}

Engine::Graphics::Shader::Shader(const char* frag, const char* vert) {
  // Generate and check vertex shader
  unsigned vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vert, 0);
  glCompileShader(vertexShader);

  // Generate and check fragment shader
  unsigned fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &frag, 0);
  glCompileShader(fragmentShader);

  // Setup shader program
  m_shaderProgram = glCreateProgram();
  glAttachShader(m_shaderProgram, vertexShader);
  glAttachShader(m_shaderProgram, fragmentShader);
  glLinkProgram(m_shaderProgram);

  // Clean up unneeded data
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void Engine::Graphics::Shader::Use() {
  glUseProgram(m_shaderProgram);
}