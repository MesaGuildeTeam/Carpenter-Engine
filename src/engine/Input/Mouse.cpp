#include "Mouse.hpp"
#include <iostream>
#include <memory>

bool Engine::Input::Mouse::mouseDown_emscripten(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData) {
  Engine::Input::Mouse& mouse = Engine::Input::Mouse::GetInstance();

  for (auto input : mouse.m_listeners) {
    if (input == nullptr) continue;
    if (input->GetInput(InputDevice::MOUSE) == (char)mouseEvent->button) {
      input->currentStrength = 1.0f;
    }
  }

  return true;
}

bool Engine::Input::Mouse::mouseUp_emscripten(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData) {
  Engine::Input::Mouse* mouse = (Engine::Input::Mouse*)userData;

  for (auto& input : mouse->m_listeners) {
    if (input == nullptr) continue;

    if (input->GetInput(InputDevice::MOUSE) == mouseEvent->button) {
      input->currentStrength = 0.0f;
    }
  }

  return true;
}

Engine::Input::Mouse::Mouse() {
  emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, false, &Engine::Input::Mouse::mouseDown_emscripten);
  emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, false, &Engine::Input::Mouse::mouseUp_emscripten);

  emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, false, &Engine::Input::Mouse::mouseMove_emscripten);
}

bool Engine::Input::Mouse::mouseMove_emscripten(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData) {
  Engine::Input::Mouse* mouse = (Engine::Input::Mouse*)userData;

  mouse->m_position.x = mouseEvent->clientX;
  mouse->m_position.y = mouseEvent->clientY;

  return true;
}

void Engine::Input::Mouse::AddListener(Input* input) {
  m_listeners.push_back(input);
}

Engine::Input::Mouse& Engine::Input::Mouse::GetInstance() {
  static Mouse instance;
  return instance;
}

Engine::Vec2f Engine::Input::Mouse::GetPosition() {
  return m_position;
}