#if false
#include "UIRenderCanvas.hpp"

#include <emscripten/html5.h>
#include <iostream>

namespace Engine::UI {
    UIRenderCanvas::UIRenderCanvas(std::string id) : UIElement(id) {
    m_uiTag = "canvas";
    m_uiClass = "ui-renderer";

    // Create the canvas element
    EmscriptenWebGLContextAttributes attrs;
    emscripten_webgl_init_context_attributes(&attrs);

    attrs.majorVersion = 2; // WebGL 2.0
    attrs.minorVersion = 0; // none

    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx = emscripten_webgl_create_context(id.c_str(), attrs);
    if (cxt <= 0) {
        std::cerr << "Failed to get WebGL context" << std::endl;
    }
    // use emscripten_webgl_make_context_current(ctx) to use opengl functions
   UIRenderCanvas::onGLLoad.trigger((struct onGlLoadEventData){ctx, this});
}
}
#endif