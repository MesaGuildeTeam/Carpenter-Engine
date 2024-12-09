#ifndef ENGINE_GAME
#define ENGINE_GAME

namespace Engine {
  
  /**
   * The game class (singleton?) used to run the game loop
   */
  class Game {
    private:
    // Scene& m_currentScene;
    // std::map<const char*, Scene*> m_loadedScenes;
    
    public:
    Game();

    void DrawScene();

    void UpdateScene(float dt);

  };
}

#endif