#include "GameObject.hpp"

Engine::GameObject::GameObject(std::string name): Engine::Node(name) {
  m_nodeType = "GameObject";
}

Engine::Vec3f Engine::GameObject::GetGlobalPosition() { 
  return Position;
}

Engine::Vec3f Engine::GameObject::GetGlobalRotation() { 
  return Rotation;
}