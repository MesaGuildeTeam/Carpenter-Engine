#include "Mouse.hpp"

Engine::Input::Mouse::Mouse() {
  emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, false, &Engine::Input::Mouse::mouseMove_emscripten);
}

bool Engine::Input::Mouse::mouseMove_emscripten(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData) {
  Engine::Input::Mouse* mouse = (Engine::Input::Mouse*)userData;

  mouse->m_position.x = mouseEvent->canvasX;
  mouse->m_position.y = mouseEvent->canvasY;

  return true;
}

Engine::Input::Mouse& Engine::Input::Mouse::GetInstance() {
  static Mouse instance;
  return instance;
}

Engine::Vec2f Engine::Input::Mouse::GetPosition() {
  return m_position;
}