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

    /**
     * Returns if the sound is playing or not
     * 
     * @return SoundState if sound is playing or not
     */
    SoundState playing();

    /**
     * Pauses the music
     */
    void Pause();
  };

};

#endif