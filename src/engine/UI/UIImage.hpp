#ifndef ENGINE_UIIMAGE
#define ENGINE_UIIMAGE

#include "UIElement.hpp"

namespace Engine::UI {
  class UIImage : public UIElement {
    protected:
    std::string m_path;

    public:

    /**
     * @brief Default constructor for a UI Image element
     * @param name The name of the UI Image element
     * @param path The path to the image file
     */
    UIImage(std::string name, std::string path);

    /**
     * @brief Initializes and instantiates the UI Image element
     */
    void Init() override;

    /**
     * @brief Sets the image path for the UI Image element
     * @param path The path to the image file
     */
    void SetImage(std::string path);
  };
}

#endif
