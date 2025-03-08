#ifndef ENGINE_WINDOW
#define ENGINE_WINDOW

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