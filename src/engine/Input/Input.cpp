#include "Input.hpp"
#include <iostream>

Engine::Input::Input::Input(char keyCode, char mouseButton, char gamepadInput) {
    m_keyCode = keyCode;
    m_mouseButton = mouseButton;
    m_gamepadInput = gamepadInput;    
}

const float MINIMUM_STRENGTH{0.5f};

void Engine::Input::Input::Update(float strength) {
    bool isDown = strength >= MINIMUM_STRENGTH;
    bool wasDown = m_isDown >= MINIMUM_STRENGTH;

    m_isPressed = isDown && !m_isPressed && !wasDown;
    m_isReleased = !isDown && wasDown && !m_isReleased;
    m_isDown = strength;
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