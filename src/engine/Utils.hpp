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
    FAILURE,
    SUCCESS,
    WARNING
  } Success;

  /**
   * A 2D vector struct with overloaded operators
   */
  struct Vec2f {
    float x;
    float y;

    // /**
    //  * Assign a Vec2f
    //  */
    // Vec2f operator=(const Vec2f& rhs);

    /**
     * Add two Vec2f objects together
     */
    Vec2f operator+(const Vec2f& rhs);

    // /**
    //  * Subtract two Vec2f objects
    //  */
    // Vec2f operator-(const Vec2f& rhs);

    /**
     * Compute scalar multiplication
     */
    Vec2f operator*(const float& rhs);

    /**
     * Compute multiplication in parallel
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
   * A 3D vector struct with overloaded operators
   */
  struct Vec3f {
    float x;
    float y;
    float z;

    /**
     * Adds two Vec3f objects
     */
    Vec3f operator+(const Vec3f& rhs);

    /**
     * Compute scalar multiplication
     */
    Vec3f operator*(const float& rhs);

    /**
     * Computes Multiplication in parallel
     */
    Vec3f operator*(const Vec3f& rhs);

    /**
     * Returns the length of the vector
     */
    float lengthSquared();

    bool operator==(const Vec3f& rhs);
  };

  /**
   * A color struct with 4 components: RGBA
   */
  struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
  };

  /**
   * Rotates a vector by an angle
   * 
   * @param v The vector to rotate
   * @param angle The angle to rotate
   * @return The rotated vector
   */
  Vec2f Rotate(Vec2f v, float angle);

  /**
   * Rotates a vector by an angle
   * 
   * @param v The vector to rotate
   * @param angle The angle to rotate
   * @return The rotated vector
   */
  Vec3f Rotate(Vec3f v, Vec3f angle);

  /**
   * Using SIMD Intrinsics, returns the inverse square root of a float
   * 
   * @param x The float to take the inverse square root of
   * @return The inverse square root
   */
  float InvSQRT(float x);
}

#endif