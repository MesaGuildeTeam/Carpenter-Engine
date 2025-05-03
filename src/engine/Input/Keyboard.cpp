/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "Keyboard.hpp"

#include <iostream>

Engine::Input::Keyboard::Keyboard() {
  emscripten_set_keydown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, false, &Engine::Input::Keyboard::keyDown_emscripten);
  emscripten_set_keyup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, false, &Engine::Input::Keyboard::keyUp_emscripten);
}

bool Engine::Input::Keyboard::keyDown_emscripten(int eventType, const EmscriptenKeyboardEvent *keyEvent, void *userData) {
  Engine::Input::Keyboard& keyboard = Engine::Input::Keyboard::GetInstance();

  for (auto input : keyboard.m_listeners) {
    // Turns out I also needed to check if GetInput returns -1.
    // I don't fully understand yet... I'll leave it for now and refine this
    // later
    if (input == nullptr || input->GetInput(InputDevice::KEYBOARD) == -1) 
      continue;

    if (input->GetInput(InputDevice::KEYBOARD) == keyEvent->key[0]) {
      input->currentStrength = 1.0f;
    }
  }

  return true;
}

bool Engine::Input::Keyboard::keyUp_emscripten(int eventType, const EmscriptenKeyboardEvent *keyEvent, void *userData) {
  Engine::Input::Keyboard& keyboard = Engine::Input::Keyboard::GetInstance(); 

  for (auto input : keyboard.m_listeners) {
    if (input == nullptr || input->GetInput(InputDevice::KEYBOARD) == -1) 
      continue;

    if (input->GetInput(InputDevice::KEYBOARD) == keyEvent->key[0]) {
      input->currentStrength = 0.0f;
    }
  }

  return true;
}

Engine::Input::Keyboard& Engine::Input::Keyboard::GetInstance() {
  static Keyboard instance;
  return instance;
}

void Engine::Input::Keyboard::AddListener(Input* input) {
  m_listeners.push_back(input);
}

void Engine::Input::Keyboard::RemoveListener(Input* input) {
  m_listeners.erase(std::remove(m_listeners.begin(), m_listeners.end(), input), m_listeners.end());
}