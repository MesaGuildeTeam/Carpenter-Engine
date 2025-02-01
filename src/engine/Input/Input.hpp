#ifndef ENGINE_INPUT
#define ENGINE_INPUT

namespace Engine::Input {
  
  /**
   * A class used to represent a single generic input. Your input is a combination of the following:
   * - Keyboard keys
   * - Mouse events 
   * - Gamepad buttons
   */
  class Input {
    private:
    char keyCode;
    char mouseButton;
    char gamepadButton;
  
    public:
    /**
     * Checks if the input is just pressed
     * 
     * @return True if the input is just pressed
     */
    bool IsPressed() const;

    /**
     * Checks if the input is just released
     * 
     * @return True if the input is just released
     */
    bool IsReleased() const;

    /**
     * Checks if the input is down
     * 
     * @return a value between 0 and 1 depending on how strong the input is
     */
    float IsDown() const;
  };
}

#endif