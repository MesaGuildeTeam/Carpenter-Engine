#ifndef ENGINE_RENDERER
#define ENGINE_RENDERER

namespace Engine {
  
  /**
   * The window used to interact with the DOM Canvas 
   */
  class Renderer {
    private:
    unsigned long m_context;

    public:

    Renderer(const char* id = "#canvas");

    void ClearBuffer();
  };
}

#endif