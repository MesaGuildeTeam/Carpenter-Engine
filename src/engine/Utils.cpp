#include "Utils.hpp"
#include <cmath>

#define M_PI 3.14159265358979323846

// Vector Rotations

Engine::vec2 Engine::rotate(const vec2& vec, const float& angle) {
  return {vec.x * cos(angle) - vec.y * sin(angle), vec.x * sin(angle) + vec.y * cos(angle)};
}

Engine::vec3 Engine::rotate(const vec3& vec, const vec3& angle) {
  float cosX = cosf(angle.x);
  float sinX = sinf(angle.x);
  float cosY = cosf(angle.y);
  float sinY = sinf(angle.y);
  float cosZ = cosf(angle.z);
  float sinZ = sinf(angle.z);

  return {
    cosY * (sinZ * vec.y + cosZ * vec.x) - sinY * vec.z,
    sinX * (cosY * vec.z + sinY * (sinZ * vec.y + cosZ * vec.x)) + cosX * (cosZ * vec.y - sinZ * vec.x),
    cosX * (cosY * vec.z + sinY * (sinZ * vec.y + cosZ * vec.x)) - sinX * (cosZ * vec.y - sinZ * vec.x)
  };
}

float Engine::sign(float x) {
  return (0 < x) - (x < 0);
}
