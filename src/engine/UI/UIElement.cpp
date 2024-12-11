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
      var uielement = document.createElement(UTF8ToString($2));
      uielement.classList.add("ui-element");
      uielement.classList.add(UTF8ToString($4));
      console.log(UTF8ToString($0));
      uielement.id = `${UTF8ToString($4)}-${UTF8ToString($2)}`;
      document.getElementById(`${UTF8ToString($1) != "" ? UTF8ToString($1) + "-" : ""}${UTF8ToString($0)}`).appendChild(uielement);
    }, parentElement, parentClass, m_name.c_str(), m_uiTag, m_uiClass);
}