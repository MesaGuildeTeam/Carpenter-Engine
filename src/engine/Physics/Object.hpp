#ifndef ENGINE_PHYSICS_OBJECT
#define ENGINE_PHYSICS_OBJECT

#include "../Utils.hpp"
#include "../GameObject.hpp"
#include "./CollisionMesh.hpp"

namespace Engine::Physics {

  class Object {
    private:
    bool m_isStatic;


    public:
    Vec3f& position;
    Vec3f acceleration;
    Vec3f velocity;


    const Mesh objectMesh;
    const float mass;

    /**
     * @brief Constructor used to create objects in a physics space
     *
     * @param self the object this physics object is attached to
     * @param mass the mass in kilograms (kg) this object has
     * @param radius the collision detection radius
     */
    Object(Engine::GameObject& self, float mass, Mesh mesh = PointMesh(), bool isStatic = false);

    /**
     * @brief Computes movement of the object
     *
     * The update method focuses on the kinematics of the object.
     *
     * @param dt the time step in seconds (s) since the last update
     */
    void Update(float dt, Vec3f gravity);
  };
};

#endif
