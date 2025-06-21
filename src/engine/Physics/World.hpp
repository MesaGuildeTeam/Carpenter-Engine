#ifndef ENGINE_PHYSICS_WORLD
#define ENGINE_PHYSICS_WORLD

#include <vector>

#include "../Utils.hpp"
#include "Object.hpp"

namespace Engine::Physics {
  class World {
    private:
    Vec3f m_gravity;
    std::vector<Physics::Object*> m_objectsList;

    public:
    World(Vec3f gravity);

    void AddObject(Physics::Object* obj);

    /**
     * @brief Updates all the objects in the scene
     */
    void Update(float dt);
  };
};

#endif
