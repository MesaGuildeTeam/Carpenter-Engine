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
   * @brief Singleton class used to handle mouse input
   * 
   * This class is primarily used to return the current position of the mouse. 
   * If you want to listen for mouse button events, use the InputManager instead.
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
     * @brief Returns the singleton instance
     */
    static Mouse& GetInstance();

    /**
     * @biref Adds an input listener to the mouse
     * 
     * @param input Reference to the input to add
     */
    void AddListener(Input* input);

    /**
     * Removes an input listener 
     * 
     * @param input Reference to the input to remove
     */
    void RemoveListener(Input* input);

    /**
     * @brief Returns the position of the mouse
     * 
     * @return The X and Y coordinates of the mouse from the top left of the
     * window.
     */
    Vec2f GetPosition();
  };
}

#endif