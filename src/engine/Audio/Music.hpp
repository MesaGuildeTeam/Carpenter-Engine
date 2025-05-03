/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef ENGINE_MUSIC
#define ENGINE_MUSIC

#include "Audio.hpp"

namespace Engine::Audio {

  /**
   * @brief An Audio file that queues itself into the music player of the engine
   * 
   * @author Roberto Selles
   */
  class Music : public Audio {
  public:
    Music(const char* filename);

    /**
     * @brief Returns if the sound is playing or not
     * 
     * @return SoundState if sound is playing or not
     */
    SoundState playing();

    /**
     * @brief Pauses the music. 
     * 
     * This will pause the whole queue, 
     * but we can assume that the song will be playing when this song is playing
     */
    void Pause();

    /**
     * @brief Sets if the song should loop
     *
     * @param {shouldLoop} the value set to the song
     */
    void setLoop(bool shouldLoop);
  };

  /**
   * @brief Skips the current song being played
   */
  extern void SkipTrack();

};

#endif
