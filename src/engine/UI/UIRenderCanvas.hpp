#ifndef ENGINE_UIRenderCanvas
#define ENGINE_UIRenderCanvas

#include <GLES3/gl3.h>
#include "UIElement.hpp"
#include "../BasicEvent.hpp"

namespace Engine::UI {

  class UIRenderCanvas : public UIElement {
    private:

    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE gl;

    public:

    struct onGlLoadEventData {
      EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;
      UIRenderCanvas* element;
    };
    
    BasicEvent<onGlLoadEventData> onGLLoad;

    /** 
     * Creates a render canvas with the given id
     */
    UIRenderCanvas(std::string id);

  };

}

#endif