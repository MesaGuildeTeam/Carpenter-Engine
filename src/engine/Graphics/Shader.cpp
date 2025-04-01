#include "Shader.hpp"
#include <GLES3/gl3.h>
#include <emscripten/html5.h>
#include <iostream>
#include "../Game.hpp"

Engine::Graphics::Shader Engine::Graphics::DefaultShader;

Engine::Graphics::Shader::Shader() : Shader("js/default.frag", "js/default.vert") {}

Engine::Graphics::Shader::Shader(const char* frag) : Shader(frag, "js/default.vert") {}

Engine::Graphics::Shader::Shader(const char* frag, const char* vert) {
  m_frag = frag;
  m_vert = vert;
}

void Engine::Graphics::Shader::CompileShader() {
  // Load shader scripts
  char* vScript, *fScript;
  int vertexShaderSize, fragmentShaderSize;

  emscripten_wget_data(m_frag, (void**)&fScript, &fragmentShaderSize, nullptr);
  emscripten_wget_data(m_vert, (void**)&vScript, &vertexShaderSize, nullptr);
  
  // Compile and check vertex shader
  unsigned vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vScript, &vertexShaderSize);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, 0, infoLog);
    std::cerr << "ERROR: Vertex Shader Failed to compile successfully\n" << infoLog << std::endl;
  }

  // Compile and check fragment shader
  unsigned fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fScript, &fragmentShaderSize);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, 0, infoLog);
    std::cerr << "ERROR: Fragment Shader Failed to compile successfully\n" << infoLog << std::endl;
  }

  // Setup shader program
  m_shaderProgram = glCreateProgram();
  glAttachShader(m_shaderProgram, vertexShader);
  glAttachShader(m_shaderProgram, fragmentShader);

  glLinkProgram(m_shaderProgram);

  glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);

  if (!success) {
    glGetProgramInfoLog(m_shaderProgram, 512, 0, infoLog);
    std::cerr << "ERROR: Shader Program Failed to link successfully\n" << infoLog << std::endl;
    
    // set the shader program to the default shader as a fallback
    m_shaderProgram = DefaultShader.GetShaderProgram();
  } else {
    std::cout << "DEBUG: Shader Program linked successfully with ID " << m_shaderProgram << std::endl;
  }

  glBindAttribLocation(m_shaderProgram, 0, "a_Position");
  glBindAttribLocation(m_shaderProgram, 1, "a_UV");
  glBindAttribLocation(m_shaderProgram, 2, "a_Normal");

  // Clean up unneeded data
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  delete[] vScript;
  delete[] fScript;
}



unsigned int Engine::Graphics::Shader::GetShaderProgram() {
  if (m_shaderProgram == -1) {
    CompileShader();
  }

  return m_shaderProgram;
}