/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef ENGINE_UIINPUT
#define ENGINE_UIINPUT

#include "UIElement.hpp"
#include <string>

namespace Engine::UI {

  class UIInput : public UIElement {
    const char* m_placeholder;
    std::string m_value;

    public:

    /**
     * Default Constructor
     */
    UIInput(std::string name, const char* placeholder = "");

    void Init() override;

    /**
     * Returns the input as an integer
     * 
     * @return The input as an integer
     */
    int getInputInt();

    /**
     * Returns the input as a double
     * 
     * @return The input as a double
     */
    double getInputDouble();

    /**
     * Returns the input as a string
     * 
     * @return The input as a string
     */
    std::string getInputString();
  };

}

#endif