#ifndef ENGINE_WINDOW
#define ENGINE_WINDOW

namespace Engine {
  
  /**
   * The window singleton used to interact with the DOM Canvas 
   */
  class Window {
    private:

    Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    public:

    /**
     * Returns a reference to the window singleton
     */
    static Window& getWindow() {
      static Window instance;
      return instance;
    }
  };
}

#endif