#include "UIElement.hpp"
#include <emscripten.h>

Engine::UI::UIElement::UIElement(std::string name) : Engine::Node(name) {
  m_nodeType = "UI";
  m_uiTag = "div";
  m_uiClass = "ui-generic";
}

void Engine::UI::UIElement::Init() {
  const char* parentElement = m_parent->m_nodeType == "UI" ? m_parent->m_name.c_str() : "ui-layer";
  const char* parentClass = m_parent->m_nodeType == "UI" ? ((UI::UIElement*)m_parent)->m_uiClass : "";

  EM_ASM({
      var uielement = document.createElement(UTF8ToString($3));
      uielement.classList.add("ui-element");
      uielement.classList.add(UTF8ToString($4));
      uielement.id = `${UTF8ToString($4)}-${UTF8ToString($2)}`;

      document.getElementById(`${UTF8ToString($1) != "" ? UTF8ToString($1) + "-" : ""}${UTF8ToString($0)}`)
        .appendChild(uielement);
    }, parentElement, parentClass, m_name.c_str(), m_uiTag, m_uiClass);
}

void Engine::UI::UIElement::AddTheme(const char* theme) {
  EM_ASM({
    document.getElementById(`${UTF8ToString($1) != "" ? UTF8ToString($1) + "-" : ""}${UTF8ToString($0)}`).classList.add(UTF8ToString($2));
  }, m_name.c_str(), m_uiClass, theme);
}

void Engine::UI::UIElement::SetAnchor(const char* anchor) {
  EM_ASM({
    document.getElementById(`${UTF8ToString($1) != "" ? UTF8ToString($1) + "-" : ""}${UTF8ToString($0)}`).classList.add(`ui-anchor-${UTF8ToString($2)}`);
  }, m_name.c_str(), m_uiClass, anchor);
}

void Engine::UI::UIElement::SetDimensions(Vec2f dimensions) {
  EM_ASM({
    document.getElementById(`${UTF8ToString($1) != "" ? UTF8ToString($1) + "-" : ""}${UTF8ToString($0)}`).style.width = `${$2}px`;
    document.getElementById(`${UTF8ToString($1) != "" ? UTF8ToString($1) + "-" : ""}${UTF8ToString($0)}`).style.height = `${$3}px`;
  }, m_name.c_str(), m_uiClass, dimensions.x, dimensions.y);
}

void Engine::UI::UIElement::SetOffset(Vec2f offset) {
  EM_ASM({
    document.getElementById(`${UTF8ToString($1) != "" ? UTF8ToString($1) + "-" : ""}${UTF8ToString($0)}`).style.setProperty('--offset-x', `${$2}px`);
    document.getElementById(`${UTF8ToString($1) != "" ? UTF8ToString($1) + "-" : ""}${UTF8ToString($0)}`).style.setProperty('--offset-y', `${$3}px`);
  }, m_name.c_str(), m_uiClass, offset.x, offset.y);
}

void Engine::UI::UIElement::OnEnable() {
  EM_ASM({
    document.getElementById(`${UTF8ToString($1) != "" ? UTF8ToString($1) + "-" : ""}${UTF8ToString($0)}`).style.display = "block";
  }, m_name.c_str(), m_uiClass);
}

void Engine::UI::UIElement::OnDisable() {
  EM_ASM({
    document.getElementById(`${UTF8ToString($1) != "" ? UTF8ToString($1) + "-" : ""}${UTF8ToString($0)}`).style.display = "none";
  }, m_name.c_str(), m_uiClass);
}