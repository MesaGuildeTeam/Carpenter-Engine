#include "Shader.hpp"
#include <GLES3/gl3.h>
#include <iostream>

const char* defaultVertexShader {
  "attribute vec3 a_Position;\n"
  "attribute vec2 a_UV;\n"
  "attribute vec3 a_Normal;\n"
  "uniform vec2 window;\n"
  "varying vec2 v_UV;\n"
  "varying vec3 v_Normal;\n"
  "void main()\n"
  "{\n"
  "   gl_Position = vec4(a_Position.x * window.y / window.x, a_Position.y, a_Position.z, 1.0);\n"
  "   v_UV = a_UV;\n"
  "   v_Normal = a_Normal;\n"
  "}\0"
};

const char* defaultFragmentShader {
  "precision mediump float;\n"
  "varying vec2 v_UV;\n"
  "varying vec3 v_Normal;\n"
  "uniform sampler2D u_Color;\n"
  "void main()\n"
  "{\n"
  "    gl_FragColor = texture2D(u_Color, v_UV);\n"
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
    std::cerr << "ERROR: Vertex Shader Failed to compile successfully\n" << infoLog << std::endl; 
  }

  // Generate and check fragment shader
  unsigned fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &frag, 0);
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

  glBindAttribLocation(m_shaderProgram, 0, "a_Position");
  glBindAttribLocation(m_shaderProgram, 1, "a_UV");
  glBindAttribLocation(m_shaderProgram, 2, "a_Normal");

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