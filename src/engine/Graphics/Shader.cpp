/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "Shader.hpp"
#include <GLES3/gl3.h>
#include <emscripten/html5.h>
#include <iostream>
#include "../Game.hpp"

Engine::Graphics::Shader::Shader() : Engine::Graphics::Shader("shader/default.frag", "shader/default.vert") {}

Engine::Graphics::Shader::Shader(const char* frag) : Engine::Graphics::Shader(frag, "shader/default.vert") {}

Engine::Graphics::Shader::Shader(const char* frag, const char* vert): m_shaderProgram(0) {
  //std::cout << "Creating shader with fragment shader " << std::string(frag) << " and vertex shader " << std::string(vert) << std::endl;
  m_frag = frag;
  m_vert = vert;
}

unsigned int Engine::Graphics::Shader::CompileShader() {
  // Load shader scripts
  char *vScript = nullptr, *fScript = nullptr;
  int vertexShaderSize, fragmentShaderSize;

  int vScriptError, fScriptError;

  //std::cout << "fetching data from vertex shader " << std::string(m_vert) << " and fragment shader " << std::string(m_frag) << std::endl;
  //emscripten_wget_data(m_frag, (void**)&fScript, &fragmentShaderSize, &fScriptError);
  //emscripten_wget_data(m_vert, (void**)&vScript, &vertexShaderSize, &vScriptError);

  if (m_fragFile.IsClosed()) m_fragFile.Open(m_frag);
  if (m_vertFile.IsClosed()) m_vertFile.Open(m_vert);
 
  // Fallback if shader scripts are not ready
  
  // NOTE: I have alternated between using the following, and I have still not
  // figured out which one it is... Here are all the options we know exist
  // - `continue`: DO NOT USE. This will deadlock the game
  // - `return 0`: This usually means a shader is not used, but I need to
  //   return the correct number
  // - `emscripten_sleep(0)`: This works best, but this can not run forever.
  while (!m_fragFile.IsOpen()) emscripten_sleep(0);
  while (!m_vertFile.IsOpen()) emscripten_sleep(0);

  fragmentShaderSize = m_vertFile.GetSize();
  vertexShaderSize = m_vertFile.GetSize();

  vScript = (char*)m_vertFile.GetData();
  fScript = (char*)m_fragFile.GetData();

  // Compile and check vertex shader
  unsigned vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vScript, &vertexShaderSize);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, 0, infoLog);
    std::cerr << "ERROR: Vertex Shader Failed to compile\n"
      << infoLog << std::endl;
  }

  // Compile and check fragment shader
  unsigned fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fScript, &fragmentShaderSize);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, 0, infoLog);
    std::cerr << "ERROR: Fragment Shader Failed to compile\n"
      << infoLog << std::endl;
  }

  // Setup shader program
  m_shaderProgram = glCreateProgram();
  glAttachShader(m_shaderProgram, vertexShader);
  glAttachShader(m_shaderProgram, fragmentShader);

  glLinkProgram(m_shaderProgram);

  glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);

  // Clean up unneeded data
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  m_fragFile.Close();
  m_vertFile.Close();

  if (!success) {
    glGetProgramInfoLog(m_shaderProgram, 512, 0, infoLog);
    std::cerr << "ERROR: Shader Program Failed to link successfully\n"
      << infoLog << std::endl;

    // set the shader program to the default shader as a fallback
    m_shaderProgram = 0;
    return 0;
  } else {
    std::cout << "DEBUG: Shader Program linked successfully with ID "
      << m_shaderProgram << std::endl;
  }

  glBindAttribLocation(m_shaderProgram, 0, "a_Position");
  glBindAttribLocation(m_shaderProgram, 1, "a_UV");
  glBindAttribLocation(m_shaderProgram, 2, "a_Normal");

  return m_shaderProgram;
}

unsigned int Engine::Graphics::Shader::GetShaderProgram() {
  if (m_shaderProgram == 0) {
    return CompileShader();
  }

  return m_shaderProgram;
}

Engine::Graphics::Shader& Engine::Graphics::DefaultShader() {
  static Engine::Graphics::Shader defaultShader;
  return defaultShader;
}
