#ifndef ENGINE_RENDERER
#define ENGINE_RENDERER

#include "Mesh.hpp"
#include "Shader.hpp"
#include <memory>

namespace Engine::Graphics {
  
  /**
   * @brief a class used to interact with html canvases
   * 
   * Each canvas has its own unique renderer using OpenGL ES 3.0.
   * This allows us to render unique meshes, textures, and shaders
   * to canvases on the web. If you are trying to render to the main
   * canvas, you can access it using `Engine::Game::GetInstance().GetRenderer()`, 
   * and that will return the main renderer.
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

    /**
     * The default constructor
     * 
     * @param id the element id of the html canvas
     */
    Renderer(const char* id = "canvas");

    /**
     * Clears the canvas to black
     */
    void ClearBuffer();

    /**
     * Draws a mesh to the canvas with the currently loaded shader.
     * To draw with a specified shader, call `UseShader(shader)` first.
     * 
     * @param mesh the mesh to draw
     */
    void DrawMesh(Mesh* mesh);
    
    /**
     * Sets the currently loaded shader.
     * Call this before drawing a mesh, but you are also suggested to use `UseMaterial` instead.
     */
    void UseShader(Shader* shader);

    /**
     * @brief Sets the material preset for the shader.
     * 
     */
    //void UseMaterial(Material* material);
  };

  /**
   * @brief The default shader used by the renderer.
   * This is a static variable used to avoid needing to create a new shader every time.
   * 
   */
  extern std::unique_ptr<Shader> DefaultShader;
}

#endif