#include "Object.hpp"

Engine::Physics::Object::Object(Engine::GameObject& self, float mass):
position(self.Position), mass(mass) {
}

void Engine::Physics::Object::Update(float dt) {
  position += (velocity * dt) + (acceleration * (dt * dt / 2));
  velocity += acceleration * dt;
}
