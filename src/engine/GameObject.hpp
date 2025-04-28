/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef ENGINE_GAMEOBJECT
#define ENGINE_GAMEOBJECT

#include "Node.hpp"

namespace Engine {

  /**
   * @brief A Game Object loaded in the scene
   * 
   * Each game object is a node. However it also has its own position, rotation,
   * and scale allowing it to be moved around in space.
   * 
   * ## Example
   * 
   * ```cpp
   * // Object of Focus
   * class CubeObject : public GameObject {
   *   public:
   *   Cube mesh;
   *   CubeObject() : GameObject("Cube") {
   *     Position = {0, 3, 4};
   *   }
   *  
   *   void Draw() override {
   *     Engine::Game::getInstance().GetRenderer().DrawMesh(&mesh, Position, Scale, Rotation);
   *   }
   * };
   * 
   * // Implementation
   * class CubeScene : public Scene {
   *   public:
   *   CubeObject cube;
   *   CubeScene() : Scene("CubeScene") {
   *     AddChild(&cube);
   *   }
   * };  
   * ```
   * 
   * @see Node
   * 
   * @author Roberto Selles
   */
  class GameObject : public Node {
    private:
    
    protected:

    Vec3f Position{0.0f, 0.0f, 0.0f};
    Vec3f Scale{1.0f, 1.0f, 1.0f};
    Vec3f Rotation{0.0f, 0.0f, 0.0f};
    
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