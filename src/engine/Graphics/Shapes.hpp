#ifndef ENGINE_SHAPES
#define ENGINE_SHAPES

#include "Mesh.hpp"

namespace Engine::Graphics {

  /**
   * @brief A simple plane mesh
   * 
   * A single unit size quad
   */
  class Plane : public Mesh {
  public:
    Plane() : Mesh() {
      AddQuad({-0.5, -0.5, 0, 0, 1}, {0.5, -0.5, 0, 1, 1}, {0.5, 0.5, 0, 1, 0},
        {-0.5, 0.5, 0, 0, 0});
    }
  };

  /**
   * @brief A simple cube mesh
   * 
   * A unit size cube (1x1x1).
   */
  class Cube : public Mesh {
  public:
    Cube() : Mesh() {
      AddQuad({-0.5, -0.5, -0.5, 0, 1}, {0.5, -0.5, -0.5, 1, 1},
        {0.5, 0.5, -0.5, 1, 0}, {-0.5, 0.5, -0.5, 0, 0});

      AddQuad({-0.5, -0.5, 0.5, 0, 1}, {-0.5, 0.5, 0.5, 1, 1},
        {0.5, 0.5, 0.5, 1, 0}, {0.5, -0.5, 0.5, 0, 0});
      
      AddQuad({-0.5, -0.5, -0.5, 0, 1}, {-0.5, 0.5, -0.5, 0, 0},
        {-0.5, 0.5, 0.5, 1, 0}, {-0.5, -0.5, 0.5, 1, 1});
      
      AddQuad({0.5, 0.5, -0.5, 0, 1}, {0.5, -0.5, -0.5, 0, 0},
        {0.5, -0.5, 0.5, 1, 0}, {0.5, 0.5, 0.5, 1, 1});
      
      AddQuad({-0.5, -0.5, -0.5, 0, 1}, {-0.5, -0.5, 0.5, 1, 1},
        {0.5, -0.5, 0.5, 1, 0}, {0.5, -0.5, -0.5, 0, 0});
      
      AddQuad({-0.5, 0.5, -0.5, 0, 1}, {0.5, 0.5, -0.5, 1, 1},
        {0.5, 0.5, 0.5, 1, 0}, {-0.5, 0.5, 0.5, 0, 0});
    }
  };
}

#endif