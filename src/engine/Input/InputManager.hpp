#ifndef ENGINE_INPUTMANAGER
#define ENGINE_INPUTMANAGER

#include "Input.hpp"
#include <map>

#include <emscripten/html5.h>

namespace Engine::Input {
  
  /**
   * The input manager used to handle input events
   */
  class InputManager {
    private:

    struct Axis {
      Input* positive;
      Input* negative;
    }; 

    std::map<const char*, Axis> m_axes;  

    public:

    InputManager();

    /**
     * Updates the input manager based on the inputs available
     */
    void Update();

    /**
     * Adds an axis to the input manager
     * 
     * This can be accessed later using the `GetAxis` function
     */
    void AddAxis(const char* axis, InputParams positive, InputParams negative);

    /**
     * Returns the value of the axis at the frame with the given name
     * 
     * @return The value of the axis between -1 and 1
     */
    float GetAxis(const char* axis);

    /**
     * Adds a single input to the input manager
     * 
     * This can be accessed later using the `GetInput` function
     */
    void AddInput(const char* name, InputParams input);

    /**
     * Returns the value of the input at the frame with the given name
     * 
     * @return The value of the input between 0 and 1
     */
    Input* GetInput(const char* name);
  };
}

#endif