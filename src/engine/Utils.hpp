/**
 * @file Utils.hpp
 * @author Roberto Selles
 * @brief A collection of utilities for the game engine code
 */

#ifndef ENGINE_UTILS
#define ENGINE_UTILS

#include "Vector/vec2.hpp"
#include "Vector/vec3.hpp"
#include "Vector/vec4.hpp"
#include "Vector/bvec2.hpp"
#include "Vector/bvec3.hpp"
#include "Vector/bvec4.hpp"
#include "Vector/mat2.hpp"
#include "Vector/mat3.hpp"
#include "Vector/mat4.hpp"

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
  vec2 rotate(const vec2& vec, const float& angle);

  /**
   * Rotates a vector by an angle
   * 
   * @param vec The vector to rotate
   * @param angle The angle to rotate by
   * @return The rotated vector
   */
  vec3 rotate(const vec3& vec, const vec3& angle);

  float sign(float x);

  /**
   * Using SIMD Intrinsics, returns the inverse square root of a float
   * 
   * @param x The float to take the inverse square root of
   * @return The inverse square root
   */
  float InvSQRT(float x);
}

#endif