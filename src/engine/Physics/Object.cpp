#include "Object.hpp"

Engine::Physics::Object::Object(Engine::GameObject& self, float mass, Mesh mesh, bool isStatic):
  position(self.Position), mass(mass), acceleration{0.0f, 0.0f, 0.0f},
  velocity{0.0f, 0.0f, 0.0f}, objectMesh(mesh), m_isStatic(isStatic) {}

void Engine::Physics::Object::Update(float dt, Vec3f gravity) {
  if (m_isStatic) return;

  Vec3f newAcceleration = acceleration + gravity;
  position += (velocity * dt) + (newAcceleration * (dt * dt) / 2);
  velocity += newAcceleration * dt;
}
