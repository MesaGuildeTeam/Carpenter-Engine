/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef ENGINE_AUDIO
#define ENGINE_AUDIO

namespace Engine::Audio {
 
  /**
   * @brief Enumerator used to represent the state of the audio file
   * 
   * States:
   * - Ready - Song is ready to be queued
   * - Queued - Song is in the queue but is not playing yet
   * - Playing - Song is currently playing
   * 
   * @author Roberto Selles
   */
  typedef enum {
    Ready,
    Queued,
    Playing
  } SoundState;

  /**
   * @brief An abstract C++ class used to hold the information of an audio file.
   * 
   * Wraps the JS class `game.Audio` into a C++ class usable within the C++ framework
   *
   * This gets derived into two different classes that should be used instead:
   * - `Engine::Audio::Sound` which plays a multi-threaded impulse
   * - `Engine::Audio::Music` which queues itself into the music player of the engine if it is not queued yet
   * 
   * @author Roberto Selles
   */
  class Audio {
    protected:
      
    const char* m_filename;

    public:
      
    /**
     * @brief Default constructor
     */
    Audio(const char* filename); 

    /**
     * @brief Plays the audio file
     */
    void Play();
  };
};

#endif
