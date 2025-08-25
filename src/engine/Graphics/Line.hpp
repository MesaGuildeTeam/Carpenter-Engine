#ifndef ENGINE_GRAPHICS_LINES
#define ENGINE_GRAPHICS_LINES

#include "Mesh.hpp"

namespace Engine::Graphics {

  class Line : public Mesh {

    public:

    /**
     * @brief constructs a line in respect to a function
     *
     * @param lineFunction the function that defines the line in terms of t
     * @param start the start of the line
     * @param end the end of the line
     */
    Line(Engine::Vec3f (&lineFunction)(float), float start, float end, float interval, float thickness);
  };
};

#endif
