#ifndef ENGINE_MOUSE
#define ENGINE_MOUSE

#include "../Utils.hpp"
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

    static bool mouseMove_emscripten(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData);

    public:

    /**
     * Returns the singleton instance
     */
    static Mouse& GetInstance();

    /**
     * Returns the x position of the mouse
     */
    Vec2f GetPosition();
  };
}

#endif