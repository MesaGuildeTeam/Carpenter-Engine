/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef ENGINE_SOUND
#define ENGINE_SOUND

#include "Audio.hpp"
#include "../Utils.hpp"

namespace Engine::Audio {

  /**
   * @brief An Audio class that plays a multi-threaded impulse
   * 
   * When needed, this class will play the sound in a separate thread allowing
   * the sound to be played multiple times while the main code is running.
   * 
   * @author Roberto Selles
   */
  class Sound : public Audio {
    private:

    /**
     * @brief A private method to play the sound
     * 
     * Starts a thread that plays the sound as the main code continues
     */
    void m_playThreadMethod(Vec3f position);

    public:

    /**
     * @brief Default constructor
     */
    Sound(const char* filename);

    /**
     * @brief Plays the sound normally
     */
    void Play();

    /**
     * @brief Plays the sound relative to where the camera position is to the object
     * 
     * The position is the distance from the camera. When you determine the
     * position of the sound, you should assume the following computation:
     * 
     * Sound Position = Global Position - Camera Global Position
     * 
     * @param {position} The distance in each axis from the camera
     */
    void Play(Vec3f position);
  };

}

#endif