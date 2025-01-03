#ifndef ENGINE_MUSIC
#define ENGINE_MUSIC

#include "Audio.hpp"

namespace Engine::Audio {

  /**
   * An Audio class that queues itself into the music player of the engine
   */
  class Music : public Audio {
  public:
    Music(const char* filename);

    void Play() override;

    SoundState playing() override;

    void Pause();
  };

};

#endif