/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef ENGINE_MOUSE
#define ENGINE_MOUSE

#include "Input.hpp"
#include "../Utils.hpp"

#include <vector>
#include <emscripten/html5.h>

namespace Engine::Input {
  
  /**
   * Singleton class used to handle mouse input
   * 
   * Primarily used to return the current position of the mouse. If you want to listen for mouse events, use the InputManager instead
   */
  class Mouse {
    private:

    Vec2f m_position = {0, 0};

    Mouse();

    std::vector<Input*> m_listeners;

    static bool mouseMove_emscripten(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData);

    static bool mouseDown_emscripten(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData);

    static bool mouseUp_emscripten(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData);

    static bool mouseScroll_emscripten(int eventType, const EmscriptenWheelEvent *wheelEvent, void *userData);

    public:

    /**
     * Returns the singleton instance
     */
    static Mouse& GetInstance();

    /**
     * Adds an input listener to the mouse
     */
    void AddListener(Input* input);

    /**
     * Removes an input listener 
     */
    void RemoveListener(Input* input);

    /**
     * Returns the x position of the mouse
     */
    Vec2f GetPosition();
  };
}

#endif