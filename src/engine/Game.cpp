/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "Game.hpp"
#include "Utils.hpp"
#include <emscripten.h>

Engine::Game& Engine::Game::getInstance(Engine::Scene* startingScene) {
  static Game instance(startingScene);
  return instance;
}

Engine::Game::Game(Scene* startingScene) {
  AddScene("Scene0", startingScene);
  SwitchScene("Scene0");
  m_renderer = Graphics::Renderer();

  EM_ASM(
    game.canvases["canvas"].width = window.innerWidth;
    game.canvases["canvas"].height = window.innerHeight;
    game.gl["canvas"].viewport(0, 0, window.innerWidth, window.innerHeight);

    game.uiContainer = document.getElementById('ui-layer');
    game.ready = true;
  );
}

Engine::Success Engine::Game::AddScene(const char* id, Scene* scene) {
  if (m_loadedScenes.find(id) != m_loadedScenes.end())
    return FAILURE;
  m_loadedScenes.emplace(id, scene);
  scene->Init();
  return SUCCESS;
}

Engine::Success Engine::Game::SwitchScene(const char* id) {
  if (m_currentScene != nullptr)
    m_currentScene->SetEnabled(false);

  if (m_loadedScenes.find(id) == m_loadedScenes.end())
    return FAILURE;

  m_currentScene = m_loadedScenes[id];
  m_currentScene->SetEnabled(true);
  return SUCCESS;
}

Engine::Success Engine::Game::UnloadScene(const char* id) {
  if (m_loadedScenes.find(id) == m_loadedScenes.end())
    return FAILURE;
  m_loadedScenes.erase(id);
  return SUCCESS;
}

void Engine::Game::DrawScene() {
  m_renderer.ClearBuffer();
  m_currentScene->Draw();
}

void Engine::Game::UpdateScene(float dt) {
  m_currentScene->Update(dt);
}

Engine::Graphics::Renderer& Engine::Game::GetRenderer() {
  return m_renderer;
}

Engine::Vec2f Engine::Game::WindowDimensions() {
  return {
    (float)EM_ASM_DOUBLE({
      return window.innerWidth;
    }),
    (float)EM_ASM_DOUBLE({
      return window.innerHeight;
    })
  };
}

extern "C" {
    void Engine_CallDraw() { Engine::Game::getInstance().DrawScene(); }
    void Engine_CallUpdate(float dt) { Engine::Game::getInstance().UpdateScene(dt); }
}
