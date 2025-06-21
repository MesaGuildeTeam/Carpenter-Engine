/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/**
 * @file Utils.hpp
 * @author Roberto Selles
 * @brief A collection of utilities for the game engine code
 */

#ifndef ENGINE_UTILS
#define ENGINE_UTILS

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
    FAILURE = -1,
    SUCCESS = -2,
    WARNING = -3
  } Success;

  /**
   * @brief A 2D vector struct with overloaded operators
   */
  struct Vec2f {
    float x;
    float y;

    // /**
    //  * Assign a Vec2f
    //  */
    // Vec2f operator=(const Vec2f& rhs);

    /**
     * @brief Add two Vec2f objects together
     */
    Vec2f operator+(const Vec2f& rhs);

    // /**
    //  * Subtract two Vec2f objects
    //  */
    // Vec2f operator-(const Vec2f& rhs);

    /**
     * @brief Compute scalar multiplication
     */
    Vec2f operator*(const float& rhs);

    /**
     * @brief Compute multiplication in parallel
     */
    Vec2f operator*(const Vec2f& rhs);

    // /**
    //  * Dot product calculation
    //  */
    // Vec2f operator*(const Vec2f& rhs);

    // /**
    //  * Scalar division
    //  */
    // Vec2f operator/(const float& rhs);

    // /**
    //  * Negate a Vec2f
    //  */
    // Vec2f operator-();
  };

  /**
   * @brief A 3D vector struct with overloaded operators
   */
  struct Vec3f {
    float x;
    float y;
    float z;

    /**
     * @brief Adds two Vec3f objects
     */
    Vec3f operator+(const Vec3f& rhs);

    /**
     * @brief Subtracts two Vec3f objects
     */
    Vec3f operator-(const Vec3f& rhs);

    /**
     * @brief Compute scalar multiplication
     */
    Vec3f operator*(const float& rhs);

    /**
     * @brief Computes Multiplication in parallel
     */
    Vec3f operator*(const Vec3f& rhs);

    Vec3f& operator+=(const Vec3f& rhs);

    Vec3f operator/(const float& rhs) const;

    /**
     * @brief Returns the length of the vector
     */
    float lengthSquared();

    bool operator==(const Vec3f& rhs);

    bool operator!=(const Vec3f& rhs);
  };

  extern Vec3f operator*(const float& lhs, const Vec3f& rhs);

  /**
   * @brief A color struct with 4 components: RGBA
   */
  struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
  };

  /**
   * @brief Rotates a 2D vector by an angle
   *
   * @param v The vector to rotate
   * @param angle The angle to rotate by
   * @return The rotated vector
   */
  Vec2f Rotate(Vec2f v, float angle);

  /**
   * @brief Rotates a 3D vector in three dimensions
   *
   * @param v The vector to rotate
   * @param angle The angles to rotate by
   * @return The rotated vector
   */
  Vec3f Rotate(Vec3f v, Vec3f angle);

  /**
   * @brief returns the inverse square root of a float
   *
   * TODO: Use SIMD Instrinsics to accelerate the calculation
   *
   * @param x The float to take the inverse square root of
   * @return The inverse square root
   */
  float InvSQRT(float x);
}

#endif
