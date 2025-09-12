/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

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
   * @brief A simple cube mesh with a repeating pattern
   * 
   * A unit size cube (1x1x1).
   */
  class Cube : public Mesh {
  public:
    Cube() : Mesh() {
      // Front
      AddQuad({-0.5, -0.5, -0.5, 0, 1}, {0.5, -0.5, -0.5, 1, 1},
        {0.5, 0.5, -0.5, 1, 0}, {-0.5, 0.5, -0.5, 0, 0});

      // Back
      AddQuad({-0.5, -0.5, 0.5, 1, 1}, {-0.5, 0.5, 0.5, 1, 0},
        {0.5, 0.5, 0.5, 0, 0}, {0.5, -0.5, 0.5, 0, 1});
      
      // Left
      AddQuad({-0.5, -0.5, -0.5, 0, 1}, {-0.5, 0.5, -0.5, 0, 0},
        {-0.5, 0.5, 0.5, 1, 0}, {-0.5, -0.5, 0.5, 1, 1});
      
      // Right
      AddQuad({0.5, 0.5, -0.5, 0, 0}, {0.5, -0.5, -0.5, 0, 1},
        {0.5, -0.5, 0.5, 1, 1}, {0.5, 0.5, 0.5, 1, 0});
      
      // Bottom
      AddQuad({-0.5, -0.5, -0.5, 0, 1}, {-0.5, -0.5, 0.5, 1, 1},
        {0.5, -0.5, 0.5, 1, 0}, {0.5, -0.5, -0.5, 0, 0});
      
      // Top
      AddQuad({-0.5, 0.5, -0.5, 0, 1}, {0.5, 0.5, -0.5, 1, 1},
        {0.5, 0.5, 0.5, 1, 0}, {-0.5, 0.5, 0.5, 0, 0});
    }
  };

  /**
   * @brief A cube mesh with a wrapping pattern
   * 
   * Create your textures with the following 4:3 UV structure:
   * ```
   * _T__
   * LFRB
   * _b__
   * ```
   */
  class Cube2 : public Mesh {
  public:
    Cube2() : Mesh() {
      // Front
      AddQuad({-0.5, -0.5, -0.5, 0.25, 2.0/3}, {0.5, -0.5, -0.5, 0.5, 2.0/3},
        {0.5, 0.5, -0.5, 0.5, 1.0/3}, {-0.5, 0.5, -0.5, 0.25, 1.0/3});

      // Back
      AddQuad({-0.5, -0.5, 0.5, 1, 2.0/3}, {-0.5, 0.5, 0.5, 1, 1.0/3},
        {0.5, 0.5, 0.5, 0.5, 1.0/3}, {0.5, -0.5, 0.5, 0.5, 2.0/3});
      
      // Left
      AddQuad({-0.5, -0.5, -0.5, 0, 2.0/3}, {-0.5, 0.5, -0.5, 0, 1.0/3},
        {-0.5, 0.5, 0.5, 0.25, 1.0/3}, {-0.5, -0.5, 0.5, 0.25, 2.0/3});
      
      // Right
      AddQuad({0.5, 0.5, -0.5, 0.5, 1.0/3}, {0.5, -0.5, -0.5, 0.5, 2.0/3},
        {0.5, -0.5, 0.5, 0.75, 2.0/3}, {0.5, 0.5, 0.5, 0.75, 1.0/3});
      
      // Bottom
      AddQuad({-0.5, -0.5, -0.5, 0.25, 1}, {-0.5, -0.5, 0.5, 0.5, 1},
        {0.5, -0.5, 0.5, 0.5, 2.0/3}, {0.5, -0.5, -0.5, 0.25, 2.0/3});
      
      // Top
      AddQuad({-0.5, 0.5, -0.5, 0.25, 1.0/3}, {0.5, 0.5, -0.5, 0.5, 1.0/3},
        {0.5, 0.5, 0.5, 0.5, 0}, {-0.5, 0.5, 0.5, 0.25, 0});
    }
  };
}

#endif