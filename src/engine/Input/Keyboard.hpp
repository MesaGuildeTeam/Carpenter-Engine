/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef ENGINE_KEYBOARD
#define ENGINE_KEYBOARD

#include <vector>
#include <emscripten/html5.h>

#include "Input.hpp"


namespace Engine::Input {

  /**
   * Singleton class used to handle keyboard input
   */
  class Keyboard {
    private:

    std::vector<Input*> m_listeners;

    Keyboard();

    static bool keyDown_emscripten(int eventType, const EmscriptenKeyboardEvent *keyEvent, void *userData);
    
    static bool keyUp_emscripten(int eventType, const EmscriptenKeyboardEvent *keyEvent, void *userData);

    public:

    /**
     * Returns the singleton instance
     */
    static Keyboard& GetInstance();

    /**
     * Adds an input listener to the keyboard
     */
    void AddListener(Input* input);

    /**
     * Removes an input listener
     */
    void RemoveListener(Input* input);
  };
};

#endif