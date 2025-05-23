/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "Material.hpp"
#include <GLES3/gl3.h>
#include <iostream>

Engine::Graphics::Material::Material(Engine::Graphics::Shader* referenceShader) {
  m_referenceShader = referenceShader;
}

void Engine::Graphics::Material::CreateParameter(const char* name, Engine::Graphics::MaterialParameterType type) {
  m_parameters.emplace(name, type);
}

void* Engine::Graphics::Material::SetParameter(const char* name, void* value) {
  if (m_parameters.find(name) == m_parameters.end()) {
    throw std::runtime_error("Parameter does not exist");
  }
  
  m_parameterValues.emplace(name, value);
  return value;
}

Engine::Success Engine::Graphics::Material::ApplyMaterialParams() {
  unsigned shaderProgram = m_referenceShader->GetShaderProgram();
  Engine::Success success = Engine::Success::SUCCESS;
  for (auto& [key, type] : m_parameters) {
    if (m_parameters.find(key) == m_parameters.end()) continue;
    int uniformLocation = glGetUniformLocation(shaderProgram, key);
    void* value = m_parameterValues[key];

    switch (type) {
      case Engine::Graphics::MaterialParameterType::FLOAT:
        glUniform1f(uniformLocation, *(float*)value);
        break;
      case Engine::Graphics::MaterialParameterType::INT:
        glUniform1i(uniformLocation, *(int*)value);
        break;
      case Engine::Graphics::MaterialParameterType::VEC2:
        glUniform2fv(uniformLocation, 1, (float*)value);
        break;
      case Engine::Graphics::MaterialParameterType::VEC3:
        glUniform3fv(uniformLocation, 1, (float*)value);
        break;
      case Engine::Graphics::MaterialParameterType::VEC4:
        glUniform4fv(uniformLocation, 1, (float*)value);
        break;
      default:
        success = Engine::Success::FAILURE;
    }
  }

  return success;
}

Engine::Graphics::Shader* Engine::Graphics::Material::GetShader() {
  return m_referenceShader;
}