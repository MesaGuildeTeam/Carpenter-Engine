#ifndef ENGINE_SOUND
#define ENGINE_SOUND

#include "Audio.hpp"
#include "../Utils.hpp"

namespace Engine::Audio {

  /**
   * An Audio class that plays a multi-threaded impulse
   */
  class Sound : public Audio {
    private:

    /**
     * A Private method to start a thread that plays the sound as the main code continues
     */
    void m_playThreadMethod(Vec3f position);

    public:

    Sound(const char* filename);

    /**
     * Plays the sound relative to where the camera position is
     */
    void Play(Vec3f position);
  };

}

#endif