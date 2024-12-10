#include "Game.hpp"

Engine::Game::Game(Scene* startingScene) {
  AddScene("Scene0", startingScene);
  SwitchScene("Scene0");
}

Engine::Success Engine::Game::AddScene(const char* id, Scene* scene) {
  if (m_loadedScenes.find(id) != m_loadedScenes.end())
    return FAILURE;
  m_loadedScenes.emplace(id, scene);
  return SUCCESS;
}

Engine::Success Engine::Game::SwitchScene(const char* id) {
  if (m_loadedScenes.find(id) == m_loadedScenes.end())
    return FAILURE;
  m_currentScene = m_loadedScenes[id];
  return SUCCESS;
}

Engine::Success Engine::Game::UnloadScene(const char* id) {
  if (m_loadedScenes.find(id) == m_loadedScenes.end())
    return FAILURE;
  m_loadedScenes.erase(id);
  return SUCCESS;
}

void Engine::Game::DrawScene() {
  m_currentScene->Draw();
}

void Engine::Game::UpdateScene(float dt) {
  m_currentScene->Update(dt);
}