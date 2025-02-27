#include "InputManager.hpp"
#include <iostream>

Engine::Input::InputManager::InputManager() {
}

void Engine::Input::InputManager::Update() {
  for(auto& [key, axis] : m_axes) {
    if (axis.positive != nullptr) axis.positive->Update();
    if (axis.negative != nullptr) axis.negative->Update();
  }
}

void Engine::Input::InputManager::AddAxis(const char* axis, InputParams positive, InputParams negative) {
  m_axes.emplace(axis, (Axis){new Input(positive), new Input(negative)});
}

float Engine::Input::InputManager::GetAxis(const char* axis) { 
  Engine::Input::Input* positive = m_axes.at(axis).positive;
  Engine::Input::Input* negative = m_axes.at(axis).negative;

  return positive->Strength() - negative->Strength();
}

void Engine::Input::InputManager::AddInput(const char* name, InputParams input) {
  m_axes.emplace(name, (Axis){new Input(input), nullptr});
}

Engine::Input::Input* Engine::Input::InputManager::GetInput(const char* name) {
  return m_axes.at(name).positive;
}