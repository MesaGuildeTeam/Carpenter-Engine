#include "Audio.hpp"
#include <emscripten.h>

Engine::Audio::Audio::Audio(const char* filename) {
  m_filename = filename;

  EM_ASM({
    game.soundElements[UTF8ToString($0)] = new Audio(UTF8ToString($0));
    game.sounds[UTF8ToString($0)] = new MediaElementAudioSourceNode(game.soundManager, 
        {mediaElement: game.soundElements[UTF8ToString($0)]});
  }, m_filename);

}
