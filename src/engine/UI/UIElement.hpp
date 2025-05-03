/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef ENGINE_UIELEMENT
#define ENGINE_UIELEMENT

#include "../Node.hpp"
#include "../Utils.hpp"

namespace Engine::UI {

  /**
   * @brief Base class for UI elements
   * 
   * Uses the Node class to create an element in the DOM. Although this is 
   * considered an abstract class, you by freely use it as a container for
   * UI Elements.
   * 
   * @author Roberto Selles
   */
  class UIElement : public Engine::Node {
    protected:

    const char* m_uiTag;
    const char* m_uiClass;
    
    public:

    /**
     * @brief Default Constructor
     * 
     * Takes in a name to make identification easier in the DOM
     * 
     * @param name The name of the UI element
     */
    UIElement(std::string name);

    /**
     * Destructor Method
     */
    ~UIElement() override;

    /**
     * @brief Creates the UI element and adds it to the DOM
     */
    void Init() override;

    /**
     * @brief Sets the theme of the UI element 
     * 
     * This theme will be applied and is inherited by children elements 
     * that are attached to this object. 
     * 
     * @param theme The CSS class to use as a theme
     */
    void AddTheme(const char* theme);

    /**
     * @brief Sets the anchor of the UI element. 
     * 
     * By default, the element is placed in the top left, but you can set to 
     * anchor any of the following:
     * - "topright"
     * - "bottomleft"
     * - "bottomright"
     * - "center"
     * 
     * If you do anchor the element to a centered position, the offset will 
     * assume to translate either to the bottom or right of the anchor.
     * (depending on the axis that has been centered)
     * 
     * @warning This should only be called once per UI element
     * 
     * @param anchor The anchor as a string
     */
    void SetAnchor(const char* anchor);

    /**
     * @brief Sets the dimensions of the UI element
     * 
     * @param dimensions The dimensions where x is the width, and y is the height
     */
    void SetDimensions(Vec2f dimensions);

    /**
     * @brief Sets the offset of the UI element
     * 
     * @param dimensions The dimensions where x is the width, and y is the height
     */
    void SetOffset(Vec2f offset);

    /**
     * @brief Shows the UI element when enabled
     * 
     * Override for `Node::OnEnable()`
     */
    void OnEnable() override;

    /**
     * @brief Hides the UI element when disabled
     * 
     * Override for `Node::OnDisable()`
     */
    void OnDisable() override;
  };
}

#endif
