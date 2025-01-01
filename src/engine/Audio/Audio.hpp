#ifndef ENGINE_SOUND
#define ENGINE_SOUND

namespace Engine::Audio {
  
  /**
   * An abstract class used to hold the information of an audio file.
   * This gets derived into two different classes that should be used instead:
   * - `Engine::Audio::Sound` which plays a multi-threaded impulse
   * - `Engine::Audio::Music` which queues itself into the music player of the engine if it is not queued yet
   */
  class Audio {
    protected:
      
      const char* m_filename;

    public:
      
      /**
       * Default constructor
       */
      Audio(const char* filename); 

      /**
       * Plays the sound
       */
      virtual void Play() = 0;

      /**
       * Returns if the sound is playing or not
       * 
       * @return bool if sound is playing or not
       */
      virtual bool playing() = 0;
  };
};

#endif
