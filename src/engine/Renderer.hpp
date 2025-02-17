#ifndef ENGINE_RENDERER
#define ENGINE_RENDERER

namespace Engine {
  
  /**
   * The window used to interact with the DOM Canvas 
   */
  class Renderer {
    private:
    const char* m_canvasId;

    public:

    Renderer(const char* id = "canvas");
  };
}

#endif