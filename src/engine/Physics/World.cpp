#include "World.hpp"
#include "CollisionMesh.hpp"
#include "Object.hpp"

#include <cmath>

Engine::Physics::World::World() {}

void Engine::Physics::World::AddObject(Engine::Physics::Object& obj) {
  m_objectsList.push_back(&obj);
}

bool HasCollision(Engine::Physics::Object* obj1, Engine::Physics::Object* obj2) {
  // Code is not repeating. Instead, swap the objects for specific cases
  // REPEATING ROUTES
  // Sphere-Box Collision
  if (obj1->objectMesh.shape == Engine::Physics::Shapes::SPHERE &&
    obj2->objectMesh.shape == Engine::Physics::Shapes::BOX)
    return HasCollision(obj2, obj1);

  // Sphere-Point Collision
  if (obj1->objectMesh.shape == Engine::Physics::Shapes::SPHERE &&
    obj2->objectMesh.shape == Engine::Physics::Shapes::POINT)
    return HasCollision(obj2, obj1);
  // Box-Point Collision
  if (obj1->objectMesh.shape == Engine::Physics::Shapes::BOX &&
    obj2->objectMesh.shape == Engine::Physics::Shapes::POINT)
    return HasCollision(obj2, obj1);


  // Point Collisions
  if (obj1->objectMesh.shape == Engine::Physics::Shapes::POINT) {
    // Point-Point Collision
    if (obj2->objectMesh.shape == Engine::Physics::Shapes::POINT)
      return obj1->position == obj2->position;

    // Point-Box Collision
    if (obj2->objectMesh.shape == Engine::Physics::Shapes::BOX) {
      Engine::Vec3f min = obj2->position - obj2->objectMesh.shapeData.Box / 2;
      Engine::Vec3f max = obj2->position + obj2->objectMesh.shapeData.Box / 2;
      return obj1->position.x >= min.x && obj1->position.x <= max.x &&
        obj1->position.y >= min.y && obj1->position.y <= max.y &&
        obj1->position.z >= min.z && obj1->position.z <= max.z;
    }

    // Point-Sphere Collision
    if (obj2->objectMesh.shape == Engine::Physics::Shapes::SPHERE) {
      Engine::Vec3f diff = obj1->position - obj2->position;
      float distance = sqrt(diff.lengthSquared());
      return distance <= obj2->objectMesh.shapeData.Sphere.radius;
    }
  }

  // Box Collisions
  if (obj1->objectMesh.shape == Engine::Physics::Shapes::BOX) {
    Engine::Vec3f min1 = obj1->position - obj1->objectMesh.shapeData.Box / 2;
    Engine::Vec3f max1 = obj1->position + obj1->objectMesh.shapeData.Box / 2;

    // Box-Box Collision
    if (obj2->objectMesh.shape == Engine::Physics::Shapes::BOX) {
      Engine::Vec3f min2 = obj2->position - obj2->objectMesh.shapeData.Box / 2;
      Engine::Vec3f max2 = obj2->position + obj2->objectMesh.shapeData.Box / 2;
      return max1.x >= min2.x && min1.x <= max2.x &&
        max1.y >= min2.y && min1.y <= max2.y &&
        max1.z >= min2.z && min1.z <= max2.z;
    }

    // Box-Sphere Collision
    if (obj2->objectMesh.shape == Engine::Physics::Shapes::SPHERE) {
      Engine::Vec3f closestPoint = {
        obj1->position.x > obj2->position.x ? max1.x : min1.x,
        obj1->position.y > obj2->position.y ? max1.y : min1.y,
        obj1->position.z > obj2->position.z ? max1.z : min1.z
      };
      Engine::Vec3f diff = closestPoint - obj2->position;
      float distance = sqrt(diff.lengthSquared());
      return distance <= obj2->objectMesh.shapeData.Sphere.radius;
    }
  }

  // Sphere-Sphere Collision
  if (obj1->objectMesh.shape == Engine::Physics::Shapes::SPHERE && obj2->objectMesh.shape == Engine::Physics::Shapes::SPHERE) {
      Engine::Vec3f diff = obj1->position - obj2->position;
      float distance = sqrt(diff.lengthSquared());
      return distance <= obj2->objectMesh.shapeData.Sphere.radius + obj1->objectMesh.shapeData.Sphere.radius;
  }

  // Error Fallback
  return false;
}

void Engine::Physics::World::Update(float dt) {
  // Implement Physics
  for (int i = 0; i < m_objectsList.size(); i++) {
    Engine::Physics::Object* obj1 = m_objectsList[i];

    // Run Collision Checks
    for (int j = i+1; i < m_objectsList.size(); j++) {
      Engine::Physics::Object* obj2 = m_objectsList[j];
      if (obj1 == obj2) continue;
      if (HasCollision(obj1, obj2)) {
        // Implement collision math using conservation of momentum
        Vec3f dv = (obj1->mass * obj1->velocity + obj2->mass * obj2->velocity)
          * (1 / (obj1->mass + obj2->mass));

        Vec3f newobj1v = dv + (obj2->mass * (obj1->velocity - obj2->velocity)
          * (1 / (obj1->mass + obj2->mass)));

        Vec3f newobj2v = dv + (obj1->mass * (obj1->velocity - obj2->velocity)
          * (1 / (obj1->mass + obj2->mass)));

        obj1->velocity = newobj1v;
        obj2->velocity = newobj2v;
      }
    }

    // Call the kinematics update of the object
    obj1->Update(dt);
  }
}
