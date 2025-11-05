/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef ENGINE_TEXTURE
#define ENGINE_TEXTURE

#include "../Utils.hpp"

namespace Engine::Graphics {

  /**
   * @brief A wrapper class for a texture for the game engine.
   *
   * The class takes a path to the texture (preferrably along `Assets/`),
   * and prepares the texture to be loaded into the GPU.
   * When the game is ready to use the texture via `GetTexture()`, the texture
   * is loaded into the GPU to be used by the game engine.
   *
   * ## Example
   *
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
   */
  class Texture {
    private:
    unsigned int m_texture = -1;
    int m_dimensions[2];
    const char* m_filename;

    AssetRequest m_request;


    /**
     * @brief Loads the texture into place if the texture is not already loaded.
     *
     * This method is private and is called by GetTexture if the texture is not
     * loaded yet.
     */
    unsigned LoadTexture();

    public:

    /**
     * @brief The default constructor of the Texture class
     *
     * Takes a path to the texture (preferrably along `Assets/`),
     * and prepares the texture to be loaded into the GPU.
     *
     * The texture is not loaded into the GPU until GetTexture is called.
     *
     * @param path The path to the texture
     */
    Texture(const char* path);

    /**
     * @brief Returns the id of the texture
     *
     * This is the id of the texture that is loaded into the GPU according to
     * the renderer. When constructed, the texture is not loaded in immediately,
     * but rather when GetTexture is called.
     *
     * @return The id of the texture
     */
    unsigned GetTexture();


  };
};

#endif
