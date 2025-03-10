#ifndef ENGINE_RENDERER
#define ENGINE_RENDERER

#include "Mesh.hpp"
#include "Shader.hpp"
#include <memory>

namespace Engine::Graphics {
  
  /**
   * The window used to interact with the DOM Canvas 
   */
  class Renderer {
    private:
    unsigned long m_context;
    
    unsigned int m_vbo;
    unsigned int m_vao;
    unsigned int m_ebo;

    public:

    Renderer(const char* id = "#canvas");

    void ClearBuffer();

    void DrawMesh(Mesh* mesh);
    
  };
 
  extern std::unique_ptr<Shader> DefaultShader;
}

#endif