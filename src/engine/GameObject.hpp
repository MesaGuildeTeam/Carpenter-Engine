#ifndef ENGINE_GAMEOBJECT
#define ENGINE_GAMEOBJECT

#include "Node.hpp"

namespace Engine {

  /**
   * @brief A Game Object loaded in the scene
   * 
   * Each game object has its own position, rotation, and scale
   */
  class GameObject : public Node {
    private:
    
    protected:

    Vec3f Position{0.0f, 0.0f, 0.0f};
    Vec3f Scale{1.0f, 1.0f, 1.0f};
    Vec3f Rotation{25.0f, 0.0f, 0.0f};
    
    public:

    /**
     * @brief Default constructor
     * 
     * takes in an object name to make searching easier 
     */
    GameObject(std::string name);

    /**
     * @brief Returns the position of the game object relative to the global 0,0
     * 
     * @return The global position of the game object
     */
    Vec3f GetGlobalPosition();

    /**
     * @brief Returns the overall rotation in respect to any parent game objects
     * 
     * @return The global rotation
     */
    Vec3f GetGlobalRotation();
  };
}

#endif