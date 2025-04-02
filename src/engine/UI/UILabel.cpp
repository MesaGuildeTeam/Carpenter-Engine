/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "UILabel.hpp"
#include <emscripten.h>

Engine::UI::UILabel::UILabel(std::string name, std::string text) : UIElement(name) {
  m_uiTag = "div";
  m_uiClass = "ui-label";
  m_text = text;
}

void Engine::UI::UILabel::Init() {
  UIElement::Init();
  SetText(m_text);
}

void Engine::UI::UILabel::SetText(std::string text) {
  m_text = text;
  EM_ASM({
    document.getElementById(`${UTF8ToString($1)}-${UTF8ToString($0)}`).innerHTML = UTF8ToString($2);
  }, m_name.c_str(), m_uiClass, m_text.c_str());
}