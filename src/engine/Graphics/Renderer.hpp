#ifndef ENGINE_RENDERER
#define ENGINE_RENDERER

#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include <memory>
#include <GLES3/gl3.h>

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
     * @brief The default constructor
     * 
     * @param id the element id of the html canvas
     */
    Renderer(const char* id = "canvas");

    /**
     * @brief Clears the canvas to the default clear color
     */
    void ClearBuffer();

    /**
     * @brief Draws a mesh to the canvas
     * 
     * Draws a mesh to the canvas with the currently loaded shader.
     * To draw with a specified shader, call `UseShader(shader)` first.
     * 
     * @param mesh the mesh to draw
     */
    void DrawMesh(Mesh* mesh);
    
    /**
     * @brief Sets the currently loaded shader.
     * 
     * Call this before drawing a mesh, but you are also suggested to use `UseMaterial` instead.
     */
    void UseShader(Shader* shader);

    /**
     * @brief Takes the texture and binds it to the specified slot.
     * 
     * To bind a texture to the renderer slot, you use the texture you wish to bind,
     * and the slot you wish to bind it to.
     * 
     * 
     * By default, the method binds the texture to slot 0 or `GL_TEXTURE0`. 
     * If you wish to select another slot, please refer to the OpenGL documentation,
     * or here are a few standards the team follows:
     * 
     * - `GL_TEXTURE0`: Albedo/Color
     * 
     * - `GL_TEXTURE1`: Normal
     * 
     * ## Example
     * ```cpp
     * Engine::Graphics::Texture texture("Assets/placeholder.png");
     * 
     * class TestObject : public Engine::Node {
     *   void Draw() override {
     *     Engine::Game::getInstance().GetRenderer().UseTexture(texture, GL_TEXTURE0);
     *     Engine::Game::getInstance().GetRenderer().DrawMesh(&mesh);
     *   }
     * };
     * ```
     * 
     * @param texture the texture to bind
     * @param slot the slot to bind the texture to. 
     */
    void UseTexture(Texture& texture, unsigned int slot = GL_TEXTURE0);
  };

  /**
   * @brief The default shader used by the renderer.
   * This is a static variable used to avoid needing to create a new shader every time.
   * 
   */
  extern std::unique_ptr<Shader> DefaultShader;
}

#endif