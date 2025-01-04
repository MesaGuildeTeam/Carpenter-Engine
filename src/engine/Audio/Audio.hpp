/**
 * @file Audio.hpp
 * @brief The basic foundation to all audio classes in the framework
 */

#ifndef ENGINE_AUDIO
#define ENGINE_AUDIO

namespace Engine::Audio {
 
  /**
   * Enumerator used to represent the state of the audio file
   * 
   * States:
   * - Ready - Song is ready to be queued
   * - Queued - Song is in the queue but is not playing yet
   * - Playing - Song is currently playing
   */
  typedef enum {
    Ready,
    Queued,
    Playing
  } SoundState;

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
     * Plays the audio file
     */
    void Play();
  };
};

#endif
