/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "Mouse.hpp"
#include "Input.hpp"
#include <cstdlib>
#include <iostream>

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
  Engine::Input::Mouse& mouse = Engine::Input::Mouse::GetInstance();

  for (auto& input : mouse.m_listeners) {
    if (input == nullptr) continue;

    if (input->GetInput(InputDevice::MOUSE) == mouseEvent->button) {
      input->currentStrength = 0.0f;
    }
  }

  return true;
}

bool Engine::Input::Mouse::mouseScroll_emscripten(int eventType, const EmscriptenWheelEvent *wheelEvent, void *userData) {
  Engine::Input::Mouse& mouse = Engine::Input::Mouse::GetInstance();

  for (auto& input : mouse.m_listeners) {
    if (input == nullptr) continue;

    // margin of scroll acknowledgement is ~1 line/frame
    // but in firefox it's ~2.4 lines/frame...
    //
    // This has been my only complaint with JavaScript so far
    // Pardon my lack of professionalism but wtf????
    // - Roberto Selles
    float strength = (std::abs((int)wheelEvent->deltaY) <= 2) ? 0.0f : (int)wheelEvent->deltaY;
    
    if (input->GetInput(InputDevice::MOUSE) == 3 && wheelEvent->deltaY <= 0) {
      input->currentStrength = -strength;
    } else if (input->GetInput(InputDevice::MOUSE) == 4 && wheelEvent->deltaY >= 0) {
      input->currentStrength = strength;
    }
  }

  return true;
}

Engine::Input::Mouse::Mouse() {
  emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, false, &Engine::Input::Mouse::mouseDown_emscripten);
  emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, false, &Engine::Input::Mouse::mouseUp_emscripten);

  emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, false, &Engine::Input::Mouse::mouseMove_emscripten);
  emscripten_set_wheel_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, false, &Engine::Input::Mouse::mouseScroll_emscripten);
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

void Engine::Input::Mouse::RemoveListener(Input* input) {
  m_listeners.erase(std::remove(m_listeners.begin(), m_listeners.end(), input), m_listeners.end());
}

Engine::Input::Mouse& Engine::Input::Mouse::GetInstance() {
  static Mouse instance;
  return instance;
}

Engine::Vec2f Engine::Input::Mouse::GetPosition() {
  return m_position;
}
