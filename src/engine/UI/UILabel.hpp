#ifndef ENGINE_UILABEL
#define ENGINE_UILABEL

#include "UIElement.hpp"

namespace Engine::UI {
  class UILabel : public UIElement {
    private:
    std::string m_text;

    public:
      UILabel(std::string name, std::string text);

      void Init() override;

      void SetText(std::string text);
  };
}

#endif