/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef ENGINE_UILABEL
#define ENGINE_UILABEL

#include "UIElement.hpp"

namespace Engine::UI {
  class UILabel : public UIElement {
    protected:
    std::string m_text;

    public:
      UILabel(std::string name, std::string text);

      void Init() override;

      /**
       * Sets the text of the label
       */
      void SetText(std::string text);
  };
}

#endif