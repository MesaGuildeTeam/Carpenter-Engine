/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

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