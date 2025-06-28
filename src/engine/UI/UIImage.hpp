#ifndef ENGINE_UIIMAGE
#define ENGINE_UIIMAGE

#include "UIElement.hpp"

namespace Engine::UI {
  class UIImage : public UIElement {
    protected:
    std::string m_path;

    public:
    UIImage(std::string name, std::string path);

    void Init() override;

    void SetImage(std::string path);
  };
}

#endif
