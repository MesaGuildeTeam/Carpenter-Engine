/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef ENGINE_INPUT
#define ENGINE_INPUT

namespace Engine::Input {
 
  /**
   * A list of keycodes that require an integer instead of a char
   */
  enum KeyCodes {
    SPACE = 32
  };

  /**
   * A list of mouse actions that you can check for
   */
  enum MouseActions {
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2,
    SCROLLUP = 3,
    SCROLLDOWN = 4
  };

  enum InputDevice {
    KEYBOARD,
    GAMEPAD,
    MOUSE
  };

  struct InputParams {
    char keyCode = -1;
    char mouseButton = -1;
    char gamepadInput = -1;
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
    Input(InputParams params);

    /**
     * Base Constructor
     */
    Input() : Input((InputParams){}) {};

    /**
     * Object Destructor
     */
    ~Input();
  
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