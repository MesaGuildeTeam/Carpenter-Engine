/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "Input.hpp"
#include "Mouse.hpp"
#include "Keyboard.hpp"

#include <iostream>

Engine::Input::Input::Input(InputParams params) {
    m_keyCode = params.keyCode;
    m_mouseButton = params.mouseButton;
    m_gamepadInput = params.gamepadInput;

    if (m_keyCode != -1)
        Engine::Input::Keyboard::GetInstance().AddListener(this);

    if (m_mouseButton != -1)
        Engine::Input::Mouse::GetInstance().AddListener(this);
}

Engine::Input::Input::~Input() {
    if (m_keyCode != -1)
        Engine::Input::Keyboard::GetInstance().RemoveListener(this);
        
    if (m_mouseButton != -1)
        Engine::Input::Mouse::GetInstance().RemoveListener(this);
}

const float MINIMUM_STRENGTH{0.5f};

void Engine::Input::Input::Update() {
    bool isDown = currentStrength >= MINIMUM_STRENGTH;
    bool wasDown = m_isDown >= MINIMUM_STRENGTH;

    m_isPressed = isDown && !m_isPressed && !wasDown;
    m_isReleased = !isDown && wasDown && !m_isReleased;
    m_isDown = currentStrength;
}

bool Engine::Input::Input::IsPressed() const {
    return m_isPressed;
}

bool Engine::Input::Input::IsReleased() const {
    return m_isReleased;
}

bool Engine::Input::Input::IsDown() const {
    return m_isDown >= MINIMUM_STRENGTH;
}

float Engine::Input::Input::Strength() const {
    return m_isDown;
}

char Engine::Input::Input::GetInput(InputDevice mode) const {
    switch (mode) {
        case KEYBOARD:
            return m_keyCode;
        case GAMEPAD:
            return m_gamepadInput;
        case MOUSE:
            return m_mouseButton;
    }
}