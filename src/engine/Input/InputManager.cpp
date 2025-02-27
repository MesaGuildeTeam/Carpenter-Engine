#include "InputManager.hpp"
#include <iostream>

bool Engine::Input::InputManager::keyDown_emscripten(int eventType, const EmscriptenKeyboardEvent *keyEvent, void *userData) {
  Engine::Input::InputManager* inputManager = (Engine::Input::InputManager*)userData;

  for (auto& [key, axis] : inputManager->m_axes) {
    if (axis.positive->GetInput(Engine::Input::InputDevice::KEYBOARD) == keyEvent->key[0]) {
      axis.positive->currentStrength = 1.0f;
    }

    if (axis.negative->GetInput(Engine::Input::InputDevice::KEYBOARD) == keyEvent->key[0]) {
      axis.negative->currentStrength = 1.0f;
    }
  }

  return true;
}

bool Engine::Input::InputManager::keyUp_emscripten(int eventType, const EmscriptenKeyboardEvent *keyEvent, void *userData) {
  Engine::Input::InputManager* inputManager = (Engine::Input::InputManager*)userData;

  for (auto& [key, axis] : inputManager->m_axes) {
    if (axis.positive->GetInput(Engine::Input::InputDevice::KEYBOARD) == keyEvent->key[0]) {
      axis.positive->currentStrength = 0.0f;
    }

    if (axis.negative->GetInput(Engine::Input::InputDevice::KEYBOARD) == keyEvent->key[0]) {
      axis.negative->currentStrength = 0.0f;
    }
  }

  return true;
}

Engine::Input::InputManager::InputManager() {
  emscripten_set_keydown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, false, &Engine::Input::InputManager::keyDown_emscripten);
  emscripten_set_keyup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, false, &Engine::Input::InputManager::keyUp_emscripten);
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