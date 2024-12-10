#ifndef ENGINE_NODE
#define ENGINE_NODE

#include "Utils.hpp"
#include <vector>

namespace Engine {
  
  /**
   * A node in a game scene. Each node is linked with a parent and its children
   */
  class Node{
    private:
    
    Node* m_parent;
    std::vector<Node*> m_children;
    bool m_enabled;

    public:

    /** 
     * Default constructor
     */  
    Node();
  
    /** 
     * Default destructor
     */
    ~Node();

    /**
     * Adds a child to the node and assigns itself as the parent of the new node
     * 
     * @param child The child to add
     * @return The index of the child
     */
    size_t AddChild(Node* child);
  
    /**
     * Returns a reference to the child at the specified index
     * 
     * @param index The index of the child to return
     * @return A reference to the child
     */
    Node* GetChild(size_t index);

    /**
     * Removes the child at the specified index
     * 
     * @param index The index of the child to remove
     * @return SUCCESS if the child was removed, FAILURE otherwise
     */
    Success RemoveChild(size_t index);

    /**
     * Toggles the state of the node. Triggers callbacks onEnable and onDisable if the state changes successfully
     * 
     * @param enabled The new state of the node
     */
    Success SetEnabled(bool enabled = true);

    /**
     * Overridable enable method for the node. Calls this whenever the node is enabled
     */
    virtual void OnEnable() {};

    /**
     * Overridable disable method for the node. Calls this whenever the node is disabled
     */
    virtual void OnDisable() {};
    
    // Behaviour Methods //

    /**
     * Overridable draw method for the node
     * 
     * @warning To maintain recursiveness, this method must be called in each method override
     */
    void Draw();

    /**
     * Overridable update method for the node
     * 
     * @warning To maintain recursiveness, this method must be called in each method override
     */
    void Update(float dt);
  };

  /**
   * Typedef for a scene
   */
  typedef Node Scene;
}

#endif