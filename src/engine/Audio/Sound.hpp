#ifndef ENGINE_SOUND
#define ENGINE_SOUND

#include "Audio.hpp"

namespace Engine::Audio {

  /**
   * An Audio class that plays a multi-threaded impulse
   */
  class Sound : public Audio {
  public:

    Sound(const char* filename);
  };

}

#endif