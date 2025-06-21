#ifndef ENGINE_PHYSICS_OBJECT
#define ENGINE_PHYSICS_OBJECT

#include "../Utils.hpp"
#include "../GameObject.hpp"
#include "./CollisionMesh.hpp"

namespace Engine::Physics {

  class Object {
    private:

    public:
    Vec3f& position;
    Mesh objectMesh;
    const float mass;
    Vec3f acceleration;
    Vec3f velocity;

    /**
     * @brief Constructor used to create objects in a physics space
     *
     * @param self the object this physics object is attached to
     * @param mass the mass in kilograms (kg) this object has
     * @param radius the collision detection radius
     */
    Object(Engine::GameObject& self, float mass);

    /**
     * @brief Computes movement of the object
     *
     * The update method focuses on the kinematics of the object.
     */
    void Update(float dt);
  };
};

#endif
