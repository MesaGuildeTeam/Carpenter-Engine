#include "UIInput.hpp"

#include <emscripten.h>
#include <emscripten/val.h>

#include <iostream>

Engine::UI::UIInput::UIInput(std::string name, const char* placeholder) : UIElement(name) {
  m_uiTag = "input";
  m_uiClass = "ui-input";
  m_placeholder = placeholder;
}

void Engine::UI::UIInput::Init() {
  UIElement::Init();

  EM_ASM({
    document.getElementById(`${UTF8ToString($1) != "" ? UTF8ToString($1) + "-" : ""}${UTF8ToString($0)}`).placeholder = UTF8ToString($2);
  }, m_name.c_str(), m_uiClass, m_placeholder);
}

int Engine::UI::UIInput::getInputInt() {
  return EM_ASM_INT({
    return parseInt(document.getElementById(`${UTF8ToString($1) != "" ? UTF8ToString($1) + "-" : ""}${UTF8ToString($0)}`).value, 10);
  }, m_name.c_str(), m_uiClass);
}

double Engine::UI::UIInput::getInputDouble() {
  return EM_ASM_DOUBLE({
    return parseFloat(document.getElementById(`${UTF8ToString($1) != "" ? UTF8ToString($1) + "-" : ""}${UTF8ToString($0)}`).value, 10);
  }, m_name.c_str(), m_uiClass);
}

std::string Engine::UI::UIInput::getInputString() {
  using emscripten::val;

  // Element is formatted with the format "#{class}-{name}"
  // To be used in the future: `std::format("#{}-{}", m_uiClass, m_name)`
  char element[256];
  sprintf(element, "%s-%s", m_uiClass, m_name.c_str());

  val document = val::global("document");
  val inputField = document.call<val>("getElementById", std::string(element));

  m_value = inputField["value"].as<std::string>();

  return m_value.c_str();
}