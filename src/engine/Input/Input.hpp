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
    
    /**
     * Intended Constructor 
     */
    Input(char keyCode, char mouseButton, char gamepadInput);
    
    /**
     * Base Constructor
     */
    Input() : Input(0, 0, 0) {};
  
    /**
     * Updates the state of each possible input solution
     * 
     * @param strength A value between 0 and 1 on the magnitude of the input
     * @warning This should only be called by the InputManager
     */ 
    void Update(float strength);
      
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

    char GetInput(InputDevice mode) const;
  };
}

#endif