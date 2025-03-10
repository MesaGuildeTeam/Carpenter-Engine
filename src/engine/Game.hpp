#ifndef ENGINE_GAME
#define ENGINE_GAME

#include "Node.hpp"
#include "Graphics/Renderer.hpp"
#include <map>

namespace Engine {
  
  /**
   * The game class singleton used to run the game loop
   */
  class Game {
    private:
    Scene* m_currentScene;
    std::map<const char*, Scene*> m_loadedScenes;

    Graphics::Renderer m_renderer;

    // SINGLETON STUFF //
    static Game* m_instance;

    /**
     * Constructor with default scene
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