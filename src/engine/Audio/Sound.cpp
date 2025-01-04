#include "Sound.hpp"
#include <emscripten.h>

Engine::Audio::Sound::Sound(const char* filename) : Engine::Audio::Audio::Audio(filename) {
  EM_ASM({
    game.sounds[UTF8ToString($0)].makeSound();
  }, m_filename);
}