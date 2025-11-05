#include "UIImage.hpp"

#include <emscripten.h>

Engine::UI::UIImage::UIImage(std::string name, std::string path) : Engine::UI::UIElement(name) {
  m_uiTag = "img";
  m_uiClass = "ui-image";
  m_path = path;
}

void Engine::UI::UIImage::Init() {
  UIElement::Init();
  SetImage(m_path);
}

void Engine::UI::UIImage::SetImage(std::string path) {
  m_path = path.c_str();
  EM_ASM({
    document.getElementById(`${UTF8ToString($1)}-${UTF8ToString($0)}`).src = UTF8ToString($2);
  }, m_name.c_str(), m_uiClass, m_path.c_str());
}
