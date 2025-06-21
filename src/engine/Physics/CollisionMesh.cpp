#include "CollisionMesh.hpp"

Engine::Physics::Mesh Engine::Physics::BoxMesh(float w, float h, float l) {
  Engine::Physics::ShapeData boxData;
  boxData.Box = {w, h, l};

  return {Engine::Physics::Shapes::BOX, boxData};
}

Engine::Physics::Mesh Engine::Physics::SphereMesh(float radius) {
  Engine::Physics::ShapeData sphereData;
  sphereData.Sphere = {radius};

  return {Engine::Physics::Shapes::SPHERE, sphereData};
}

Engine::Physics::Mesh Engine::Physics::PointMesh() {

  return {Engine::Physics::Shapes::POINT};
}
