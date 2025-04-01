#ifndef ENGINE_RENDERER
#define ENGINE_RENDERER

#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Material.hpp"
#include "../GameObject.hpp"
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
   * 
   * @authors 
   * - Roberto Selles/Henderythmix
   */
  class Renderer {
    private:
    unsigned long m_context;
    const char* m_id;
    
    unsigned int m_vbo;
    unsigned int m_vao;
    unsigned int m_ebo;

    unsigned int m_currentShaderProgram;

    GameObject* m_camera;

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
     * Draws a mesh to the canvas with the currently loaded data.
     * The data loaded (but not required) includes:
     *
     * - Shaders
     *
     * - Uniforms
     * 
     * - Textures
     * 
     * @param mesh the mesh to draw
     * @param position the position of the mesh
     * @param scale the scaling of the mesh
     * @param rotation the rotation of the mesh in degrees
     */
    void DrawMesh(Mesh* mesh, Vec3f position = {0, 0, 0}, Vec3f scale = {1, 1, 1}, Vec3f rotation = {0, 0, 0});
    
    /**
     * @brief Sets the currently loaded shader.
     * 
     * Call this before drawing a mesh, but you are also suggested to use `UseMaterial` instead.
     */
    void UseShader(Shader& shader);

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

    /**
     * @brief Sets the currently loaded material.
     * 
     * Allows a pointer to a material to be used.
     * 
     * @param material the material to use
     */
    void UseMaterial(Material* material);

    /**
     * @brief Sets the camera reference.
     * 
     * The goal of this object is to provide a reference to the camera for the renderer.
     * Any game object can be a camera, and all it does is set a reference point to
     * the camera's position and rotation.
     * 
     * @param camera the object to use as a camera
     */
    void SetCameraReference(GameObject& camera);

    /**
     * @brief Sets the background color of the canvas.
     * 
     * @param color the color to set (RGB)
     */
    void SetBackgroundColor(Vec3f color);
  };
}

#endif