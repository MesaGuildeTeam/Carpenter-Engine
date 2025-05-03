/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "UIButton.hpp"
#include <iostream>

Engine::UI::UIButton::UIButton(std::string name, std::string text, void (&callback)()) : UILabel(name, text), OnClick(callback) {
  m_uiTag = "button";
  m_uiClass = "ui-button";
}

bool Engine::UI::UIButton::m_mouseClickEmscripten(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData) {
  Engine::UI::UIButton* button = (Engine::UI::UIButton*)userData;
  button->OnClick();
  return true;
}

void Engine::UI::UIButton::Init() {
  UILabel::Init();

  // Element is formatted with the format "#{class}-{name}"
  // To be used in the future: `std::format("#{}-{}", m_uiClass, m_name)`
  char element[256];
  sprintf(element, "#%s-%s", m_uiClass, m_name.c_str());

  std::cout << "DEBUG: Linking callback to button " << element << std::endl;
  
  emscripten_set_click_callback(element, (void *)this, false, &Engine::UI::UIButton::m_mouseClickEmscripten);
}