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

void Engine::Graphics::Material::ApplyMaterialParams() {
  unsigned shaderProgram = m_referenceShader->GetShaderProgram();
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
    }
  }
}

Engine::Graphics::Shader* Engine::Graphics::Material::GetShader() {
  return m_referenceShader;
}