#ifndef ENGINE_UIELEMENT
#define ENGINE_UIELEMENT

#include "../Node.hpp"

namespace Engine::UI {
  class UIElement : protected Engine::Node {
    protected:

    const char* m_uiTag;
    const char* m_uiClass;
    
    public:

    UIElement(std::string name);

    void Init() override;
  };
}

#endif
