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
    const char* m_id;
    
    unsigned int m_vbo;
    unsigned int m_vao;
    unsigned int m_ebo;

    unsigned int m_currentShaderProgram;

    public:

    Renderer(const char* id = "#canvas");

    void ClearBuffer();

    void DrawMesh(Mesh* mesh);
    
    void UseShader(Shader* shader);
  };
 
  extern std::unique_ptr<Shader> DefaultShader;
}

#endif