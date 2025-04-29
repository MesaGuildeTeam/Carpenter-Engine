/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef ENGINE_NODE
#define ENGINE_NODE

#include "Utils.hpp"
#include <vector>
#include <string>

namespace Engine {

  /**
   * @brief A single node in a game scene.
   *
   * Each node is linked with a parent and its children. Nodes can be game
   * objects, scenes, UI elements, etc. There are predefined subclasses,
   * but you can also make your own to manage the behaviour of scenes.
   *
   * ## Example
   *
   * ```cpp
   * class ExampleNode : public Node {
   *   public:
   *   Cube mesh;
   *   CubeObject() : Node("Cube") {}
   * }
   *
   * class ExampleScene : public Scene {
   *   public:
   *   ExampleNode node;
   *   ExampleScene() : Scene("ExampleScene") {
   *     AddChild(&node);
   *   }
   * }
   * ```
   *
   * @author Roberto Selles
   */
  class Node{
    private:

    bool m_enabled;
    std::vector<Node*> m_children;

    protected:

    Node* m_parent;

    public:

    const char* m_nodeType;
    std::string m_name;

    /**
     * @brief Default constructor
     */
    Node(std::string name);

    /**
     * @brief Default destructor
     */
    ~Node();

    /**
     * @brief Adds a child to the node and assigns itself as the parent of the
     * new node
     *
     * @param child The child to add
     * @return The index of the child
     */
    size_t AddChild(Node* child);

    /**
     * @brief Returns a reference to the child at the specified index
     *
     * @param index The index of the child to return
     * @return A reference to the child
     */
    Node* GetChild(size_t index);

    /**
     * @brief Removes the child at the specified index
     *
     * @param index The index of the child to remove
     * @return SUCCESS if the child was removed, FAILURE otherwise
     */
    Success RemoveChild(size_t index);

    /**
     * @brief Toggles the state of the node.
     *
     * This method triggers callbacks onEnable and onDisable if the state changes
     * successfully.
     *
     * @param enabled The new state of the node
     * @return SUCCESS if the state changed successfully, FAILURE otherwise
     */
    Success SetEnabled(bool enabled = true);

    /**
     * @brief Overridable enable method for the node.
     *
     * Calls this whenever the node is enabled
     */
    virtual void OnEnable();

    /**
     * @brief Overridable disable method for the node.
     *
     * Calls this whenever the node is disabled
     */
    virtual void OnDisable();

    // Behaviour Methods //

    virtual void Init();

    /**
     * @brief Overridable draw method for the node
     *
     * @warning To maintain recursiveness, this method must be called in each method override
     */
    virtual void Draw();

    /**
     * @brief Overridable update method for the node
     *
     * @warning To maintain recursiveness, this method must be called in each method override
     */
    virtual void Update(float dt);
  };

  /**
   * @brief Typedef of node for scenes
   */
  typedef Node Scene;
}

#endif
