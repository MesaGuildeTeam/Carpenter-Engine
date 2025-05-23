/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef ENGINE_GAME
#define ENGINE_GAME

#include "Node.hpp"
#include "Graphics/Renderer.hpp"
#include <map>

namespace Engine {
  
  /**
   * @brief The game class singleton used to run the game loop
   * 
   * This class communicates with the game DOM to run the game loop.
   * This allows the programmers to code without worrying about a 
   * main function. The game can hold multiple scenes and switch between
   * them using the `SwitchScene` method.
   * 
   * @warning This class is a singleton and should not be created manually.
   * Instead, you use the `GetInstance` method to get the singleton instance
   * and assign it only to references of the class.
   * 
   * ## Example 
   * ```cpp
   * Engine::Game& game = Engine::Game::GetInstance(new SampleScene());
   * ```
   * 
   * @author Roberto Selles
   */
  class Game {
    private:
    Scene* m_currentScene;
    std::map<const char*, Scene*> m_loadedScenes;

    Graphics::Renderer m_renderer;

    // SINGLETON STUFF //
    static Game* m_instance;

    /**
     * @brief Constructor with a default scene
     * 
     * @param startingScene The scene to start the game with
     */
    Game(Scene* startingScene);

    public:

    static Game& getInstance(Engine::Scene* startingScene = nullptr); 

    /**
     * Adds a scene to the game
     * 
     * @param id The loaded scene ID
     * @param scene The scene to add
     * 
     * @return Success if there is no scene with the same ID
     */
    Success AddScene(const char* id, Scene* scene);

    /**
     * Switches the scene requested
     * 
     * @param id The ID of the scene to switch to
     * @return Success if the scene exists
     */
    Success SwitchScene(const char* id);

    /**
     * Deletes a loaded scene from the game
     * 
     * @param id The ID of the scene to delete
     * @return Success if the scene exists
     */
    Success UnloadScene(const char* id);

    // For the game Loop //

    /**
     * Draws the current scene
     */
    void DrawScene();

    /**
     * Updates the current scene
     */
    void UpdateScene(float dt);

    /**
     * Returns the base renderer associated with the game engine
     */
    Graphics::Renderer& GetRenderer();

  };
}

#endif