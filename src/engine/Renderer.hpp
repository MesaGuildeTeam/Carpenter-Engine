/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef ENGINE_WINDOW
#define ENGINE_WINDOW

namespace Engine {
  
  /**
   * The window used to interact with the DOM Canvas 
   */
  class Renderer {
    private:
    const char* m_canvasId;

    public:

    Renderer(const char* id = "canvas");
  };
}

#endif