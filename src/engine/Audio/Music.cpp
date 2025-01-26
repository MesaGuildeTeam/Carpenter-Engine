#include "Music.hpp"
#include <emscripten.h>

Engine::Audio::Music::Music(const char* filename) : Audio(filename) {
  EM_ASM({
    game.sounds[UTF8ToString($0)].makeSong();
  }, m_filename);
}

void Engine::Audio::Music::Pause() {
  EM_ASM({
    game.sounds[UTF8ToString($0)].pause();
  }, m_filename);
}

Engine::Audio::SoundState Engine::Audio::Music::playing() {
  int result = EM_ASM_INT({
    if (game.songQueue.includes(game.sounds[UTF8ToString($0)])) {
      if (game.sounds[UTF8ToString($0)].isPlaying()) {
        return 2; // Playing
      }
      
      return 1; // Queued
    }

    return 0; // Ready
  }, m_filename);

  return (Engine::Audio::SoundState)result;
}

void Engine::Audio::Music::setLoop(bool shouldLoop) {
  EM_ASM({
    game.sounds[UTF8ToString($0)].setLoop($1);
  }, m_filename, shouldLoop);
};

EMSCRIPTEN_KEEPALIVE
void Engine::Audio::SkipTrack() {
  EM_ASM({
    game.songQueue[0].element.pause();
    game.songQueue[0].element.currentTime = 0;
    game.songQueue.shift();
    if (game.songQueue.length > 0)
      game.songQueue[0].element.play();
  });
}