/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef ENGINE_GRAPHICS_LINES
#define ENGINE_GRAPHICS_LINES

#include "Mesh.hpp"

namespace Engine::Graphics {

  /**
   * @brief A mesh class that turns a function with one float intput int a mesh
   * 
   * Take an `Engine::Vec3f function(float)` and converts it into a mesh.
   * 
   * @authors
   * - Henderythmix/Roberto Selles
   */
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
