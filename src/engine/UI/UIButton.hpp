#ifndef ENGINE_UIBUTTON
#define ENGINE_UIBUTTON

#include "UILabel.hpp"
#include <emscripten/html5.h>

namespace Engine::UI {

  class UIButton : public UILabel {
    private:

    /**
     * Emscripten mouse click callback. Init uses this to set the callback which then calls UIButton::OnClick
     * 
     * @param eventType The type of event
     * @param mouseEvent The mouse event
     * @param userData The class itself
     */
    static bool m_mouseClickEmscripten(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData);

    public:

    /** 
     * The default constructor. Creates a button with the given name and text. The callback is assigned to OnClick
     */
    UIButton(std::string name, std::string text, void (&callback)());

    /**
     * Besides all the functionality of UILabel, UIButton also sets the OnClick callback to the given function
     */
    void Init() override;

    /**
     * A reference to the function to be called when the button is clicked
     */
    void (&OnClick)();

  };

}

#endif