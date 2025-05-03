/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef ENGINE_INPUTMANAGER
#define ENGINE_INPUTMANAGER

#include "Input.hpp"
#include <map>

#include <emscripten/html5.h>

namespace Engine::Input {
  
  /**
   * @brief A class used to handle inputs
   * 
   * When creating an input manager, you can either create a button via the
   * `AddInput` function, or an axis via the `AddAxis` function.
   * 
   * A Scene can have multiple InputManagers which can be used to organize 
   * inputs by object.
   * 
   * ## Example
   * 
   * ```cpp
   * class ExampleObject : public GameObject {
   *   private:
   *
   *   Input::InputManager inputManager;
   * 
   *   public:
   *   ExampleScene() : Scene("ExampleScene") {
   *     inputManager.AddAxis("Horizontal", {'d'}, {'a'});
   *     inputManager.AddInput("Jump", {Input::KeyCodes::SPACE});
   *     inputManager.AddInput("MouseClick", {-1, 0});
   *     inputManager.AddAxis("Scroll", {-1, 4}, {-1, 3});
   *   }
   * }
   * ```
   */
  class InputManager {
    private:

    struct Axis {
      Input* positive;
      Input* negative;
    }; 

    std::map<const char*, Axis> m_axes;  

    public:

    /**
     * @brief Default Constructor
     */
    InputManager();

    /**
     * @brief Updates the input manager based on the input data available
     */
    void Update();

    /**
     * @brief Adds an axis to the input manager
     * 
     * This can be accessed later using the `GetAxis` function
     * 
     * @param axis The name of the axis
     * @param positive The positive side of the axis (If down, axis = 1)
     * @param negative The negative side of the axis (If down, axis = -1)
     * 
     * ## Note:
     * 
     * If both positive and negative are down, the axis will be set to 0 because
     * the inputs will cancel out
     */
    void AddAxis(const char* axis, InputParams positive, InputParams negative);

    /**
     * @brief Returns the value of the axis at the frame with the given name
     * 
     * @return The value of the axis between -1 and 1
     */
    float GetAxis(const char* axis);

    /**
     * @brief Adds a single input to the input manager
     * 
     * This can be accessed later using the `GetInput` function
     */
    void AddInput(const char* name, InputParams input);

    /**
     * @brief Returns the value of the input at the frame with the given name
     * 
     * @return The value of the input between 0 and 1
     */
    Input* GetInput(const char* name);
  };
}

#endif