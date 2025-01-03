#include "Audio.hpp"
#include <emscripten.h>

Engine::Audio::Audio::Audio(const char* filename) {
  m_filename = filename;

  EM_ASM({
    game.sounds[UTF8ToString($0)] = new game.Audio(UTF8ToString($0));
  }, m_filename);

}
