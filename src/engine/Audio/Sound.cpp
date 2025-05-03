/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "Sound.hpp"
#include <emscripten.h>

Engine::Audio::Sound::Sound(const char* filename) : Engine::Audio::Audio::Audio(filename) {
  EM_ASM({
    game.sounds[UTF8ToString($0)].makeSound();
  }, m_filename);
}

void Engine::Audio::Sound::m_playThreadMethod(Vec3f position) {
  float gain = 1.0f, panning = 0.0f;

  // These algorithms may need to be revised. I will trust that these work for now though.
  panning = position.x / 60.0f;
  gain = (1 - Engine::InvSQRT(position.lengthSquared())) * 2; 
  
  EM_ASM({
    game.sounds[UTF8ToString($0)].setBuffers($1, $2);
    game.sounds[UTF8ToString($0)].play();
  }, m_filename, gain, panning);
}

void Engine::Audio::Sound::Play() {
  Engine::Audio::Audio::Play();
}

void Engine::Audio::Sound::Play(Vec3f position) {
  // Threads are funny in Emscripten. Add the parameter in the build system when we are ready to use it
  #ifdef ENGNINE_THREADING
  std::thread t(&Engine::Audio::Sound::m_playThreadMethod, this, position);
  t.detach();
  #else
  m_playThreadMethod(position);
  #endif
}