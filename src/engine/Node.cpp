/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "Node.hpp"

Engine::Node::Node(std::string name) {
  m_name = name;
  m_parent = nullptr;
  m_enabled = true;
  m_nodeType = "Node";
}

Engine::Node::~Node() {
  for (Node* child : m_children)
    if (child->m_parent != nullptr)
      delete child;
}

size_t Engine::Node::AddChild(Node* child) {
  child->m_parent = this;
  child->Init();
  m_children.push_back(child);
  return m_children.size() - 1;
}

Engine::Node* Engine::Node::GetChild(size_t index) {
  return m_children[index];
}

Engine::Success Engine::Node::RemoveChild(size_t index) {
  m_children[index]->OnDisable();
  delete m_children[index];
  m_children.erase(m_children.begin() + index);
  m_children.shrink_to_fit();
  return SUCCESS;
}

Engine::Success Engine::Node::SetEnabled(bool enabled) {
  if (m_enabled == enabled)
    return FAILURE;

  m_enabled = enabled;

  if (enabled)
    OnEnable();
  else
    OnDisable();

  return SUCCESS;
}

void Engine::Node::OnEnable() {
    for (Node* child : m_children)
        child->OnEnable();
}

void Engine::Node::OnDisable() {
    for (Node* child : m_children)
        child->OnDisable();
}

void Engine::Node::Init() {}

void Engine::Node::Draw() {
  if (!m_enabled)
    return;

  for (Node* child : m_children)
    child->Draw();
}

void Engine::Node::Update(float dt) {
  if (!m_enabled)
    return;
  for (Node* child : m_children)
    child->Update(dt);
}
