#ifndef ENGINE_INPUT
#define ENGINE_INPUT

namespace Engine::Input {
  
  enum InputDevice {
    KEYBOARD,
    GAMEPAD,
    MOUSE
  };

  /**
   * A class used to represent a single generic input. 
   * Used as a compositional class to the InputManager class
   *
   * Your input is a combination of the following:
   * - Keyboard keys
   * - Mouse events 
   * - Gamepad buttons
   */
  class Input {
    private:
    char m_keyCode;
    char m_mouseButton;
    char m_gamepadInput;
 
    float m_isDown = 0;
    bool m_isPressed = false;
    bool m_isReleased = false;
      
    public:

    float currentStrength = 0;
    
    /**
     * Intended Constructor 
     */
    Input(char keyCode, char mouseButton, char gamepadInput);
    
    /**
     * Base Constructor
     */
    Input() : Input(0, 0, 0) {};
  
    /**
     * Updates the state of each possible input solution.
     * Override currentStrength first with a value between 0 and 1 to indicate the strength of the input to update to.
     * 
     * @warning This should only be called by the InputManager
     */ 
    void Update();
      
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
     * @return True if the input is down 
     */
    bool IsDown() const;
    
    /**
     * Returns the input strength of the current input
     *
     * @return a value between 0 and 1 on the magnitude of the input
     */
    float Strength() const;

    /**
     * Returns the input parameter for the given device
     * 
     * ## Specific Cases
     * 
     * These are the specific cases based on the input device:
     * 
     * - KEYBOARD: Returns the key code
     * 
     * - MOUSE: Returns the mouse button
     * 
     * - GAMEPAD: Returns the gamepad input
     * 
     * @param mode The input device
     * @return The input parameter
     */
    char GetInput(InputDevice mode) const;
  };
}

#endif