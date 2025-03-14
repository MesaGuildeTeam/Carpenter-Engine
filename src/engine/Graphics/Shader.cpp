#include "Shader.hpp"
#include <GLES3/gl3.h>
#include <iostream>

const char* defaultVertexShader {
  "attribute vec3 aPos;\n"
  "attribute vec2 aUV;\n"
  "attribute vec3 aNormal;\n"
  "uniform vec2 window;\n"
  "varying vec2 vUV;\n"
  "void main()\n"
  "{\n"
  "   gl_Position = vec4(aPos.x * window.y / window.x, aPos.y, aPos.z, 1.0);\n"
  "   vUV = aUV;\n"
  "}\0"
};

const char* defaultFragmentShader {
  "precision mediump float;\n"
  "varying vec2 vUV;\n"
  "void main()\n"
  "{\n"
  "    gl_FragColor = vec4(vUV, 0.0, 1.0);\n"
  "}\0"
};

Engine::Graphics::Shader::Shader() : Shader(defaultFragmentShader, defaultVertexShader) {}

Engine::Graphics::Shader::Shader(const char* frag) : Shader(frag, defaultVertexShader) {}

Engine::Graphics::Shader::Shader(const char* frag, const char* vert) {
  // Generate and check vertex shader
  unsigned vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vert, 0);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, 0, infoLog);
    std::cerr << "ERROR: Shader Failed to compile successfully\n" << infoLog << std::endl; 
  }

  // Generate and check fragment shader
  unsigned fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &frag, 0);
  glCompileShader(fragmentShader);

  // Setup shader program
  m_shaderProgram = glCreateProgram();
  glAttachShader(m_shaderProgram, vertexShader);
  glAttachShader(m_shaderProgram, fragmentShader);

  glLinkProgram(m_shaderProgram);

  glBindAttribLocation(m_shaderProgram, 0, "aPos");
  glBindAttribLocation(m_shaderProgram, 1, "aUV");
  glBindAttribLocation(m_shaderProgram, 2, "aNormal");

  // Clean up unneeded data
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void Engine::Graphics::Shader::Use() {
  glUseProgram(m_shaderProgram);
}

unsigned int Engine::Graphics::Shader::GetShaderProgram() {
  return m_shaderProgram;
}