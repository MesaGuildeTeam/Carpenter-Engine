/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef ENGINE_SHADER
#define ENGINE_SHADER

namespace Engine::Graphics {

  /**
   * @brief A class used to load and use shaders
   * 
   * This class is used to load and use shaders in the game engine.
   * The shader takes two files, one for the vertex shader and one for the 
   * fragment shader, and compiles them into a GPU program to be used by 
   * the game engine to render models. If no shader scripts are provided,
   * it will use the default shader. A fragment shader will be required first.
   * 
   * ## Example
   * 
   * ```cpp
   * Engine::Graphics::Shader shader;
   * 
   * class TestObject : public Engine::Node {
   *   void Draw() override {
   *     Engine::Game::getInstance().GetRenderer().UseShader(shader);
   *     Engine::Game::getInstance().GetRenderer().DrawMesh(&mesh);
   *   }
   * };
   * ```
   * 
   * @authors
   * - Roberto Selles/Henderythmix
   */
  class Shader {
    private:

    unsigned int m_shaderProgram = -1;

    const char* m_frag;
    const char* m_vert;

    void CompileShader();

    public:

    /**
     * @brief Default constructor
     * 
     * uses the default shader files
     */
    Shader();

    /**
     * @brief Constructor with default vertex shader
     * 
     * Shader program that uses the default vertex shader.
     * Takes in a shader file for the fragment shader
     * 
     * @param frag the path to the fragment shader
     */
    Shader(const char* frag);

    /**
     * @brief Main constructor for a shader
     * 
     * Take in a fragment and vertex shader file to construct a shader.
     * 
     * @param frag the path to the fragment shader
     * @param vert the path to the vertex shader
     */
    Shader(const char* frag, const char* vert);

    /**
     * @brief Gets the shader program
     * 
     * Returns the shader program that was loaded into the GPU. If the shader is
     * not compiled, it will compile the shaderand *and then* return the shader
     * program.
     * 
     * @return the shader program
     */
    unsigned int GetShaderProgram();
  };

  /**
   * @brief The default shader used by the renderer.
   * This is a default shader so it is not *required* to make your own shaders. 
   * 
   */
  extern Shader DefaultShader;
}

#endif