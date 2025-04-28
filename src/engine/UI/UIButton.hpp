/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef ENGINE_UIBUTTON
#define ENGINE_UIBUTTON

#include "UILabel.hpp"
#include <emscripten/html5.h>

namespace Engine::UI {

  /**
   * @brief A Button associated with a scene
   * 
   * Allows a function to be called when the button is clicked
   * 
   * @see UIElement
   * @author Roberto Selles
   */
  class UIButton : public UILabel {
    private:

    /**
     * @brief Emscripten mouse click callback. 
     * 
     * Init uses this to set the callback which then calls UIButton::OnClick
     * 
     * @param eventType The type of event
     * @param mouseEvent The mouse event
     * @param userData The class itself
     */
    static bool m_mouseClickEmscripten(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData);

    public:

    /** 
     * @brief The default constructor. 
     * 
     * Creates a button with the given name and text. The callback is assigned to OnClick
     * 
     * @param name The name of the button
     * @param text The text of the button
     * @param callback The function to be called when the button is clicked
     */
    UIButton(std::string name, std::string text, void (&callback)());

    /**
     * Besides all the functionality of UILabel, UIButton also sets the OnClick callback to the given function
     */
    void Init() override;

    /**
     * @brief  reference to the function to be called when the button is clicked
     */
    void (&OnClick)();

  };

}

#endif