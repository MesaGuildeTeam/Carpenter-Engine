#ifndef ENGINE_UIRenderCanvas
#define ENGINE_UIRenderCanvas

#include "esUtil.h"
#include "UIElement.hpp"
#include "../BasicEvent.hpp"
#include <emscripten/html5.h>

namespace Engine::UI {

  class UIRenderCanvas : public UIElement {
    private:

    public:
    
    BasicEvent<...> onGLLoad;

    /** 
     * Creates a render canvas with the given id
     */
    UIRenderCanvas(std::string id);

  };

}

#endif