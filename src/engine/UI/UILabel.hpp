/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef ENGINE_UILABEL
#define ENGINE_UILABEL

#include "UIElement.hpp"

namespace Engine::UI {

  /**
   * @brief A Label associated with a scene
   * 
   * Allows the UI to show a simple label of text
   * 
   * @see UIElement
   * 
   * @author Roberto Selles
   */
  class UILabel : public UIElement {
    protected:
    std::string m_text;

    public:

      /**
       * @brief Default Constructor
       * 
       * Takes in a name, and some text to render in the DOM
       * 
       * @param name The name of the UI element
       * @param text The text to display
       */
      UILabel(std::string name, std::string text);

      /**
       * @brief Override of UIElement::Init(). Nothing important
       */
      void Init() override;

      /**
       * @brief Updates the text of the label
       * 
       * @param text The new text to display
       */
      void SetText(std::string text);
  };
}

#endif