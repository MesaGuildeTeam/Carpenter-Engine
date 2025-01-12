/**
 * @file Utils.hpp
 * @author Roberto Selles
 * @brief A collection of utilities for the game engine code
 */

#ifndef ENGINE_UTILS
#define ENGINE_UTILS

#include "Vector.hpp"
#include "Matrix.hpp"

namespace Engine {
  /**
   * A generic success type that determines the stabitility of the code.
   * This is recommended to be used as voids that need to check for errors
   * without using try/catch blocks
   * 
   * - SUCCESS - The method was run successfully
   * - FAILURE - The method failed to run
   * - WARNING - The method was run successfully but with warnings
   * 
   * @brief A generic success type
   * @author Roberto Selles
   */
  typedef enum {
    FAILURE,
    SUCCESS,
    WARNING
  } Success;

  /**
   * Rotates a vector by an angle
   * 
   * @param vec The vector to rotate
   * @param angle The angle to rotate by
   * @return The rotated vector
   */
  vec2f rotate(const vec2f& vec, const float& angle);

  /**
   * Rotates a vector by an angle
   * 
   * @param vec The vector to rotate
   * @param angle The angle to rotate by
   * @return The rotated vector
   */
  vec3f rotate(const vec3f& vec, const vec3f& angle);
}

#endif