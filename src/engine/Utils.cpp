#include "Utils.hpp"
#include <cmath>

#define M_PI 3.14159265358979323846

// 2D Vector Operations

Engine::vec2f Engine::vec2f::operator+(const Engine::vec2f& rhs) {
  return {x + rhs.x, y + rhs.y};
}

Engine::vec2f Engine::vec2f::operator*(const float& rhs) {
  return {x * rhs, y * rhs};
}

Engine::vec2f Engine::vec2f::operator*(const vec2f& rhs) {
  return {x * rhs.x, y * rhs.y};
}

// 3D Vector Operations

Engine::vec3f Engine::vec3f::operator+(const Engine::vec3f& rhs) {
  return {x + rhs.x, y + rhs.y, z + rhs.z};
}

Engine::vec3f Engine::vec3f::operator*(const float& rhs) {
  return {x * rhs, y * rhs, z * rhs};
}

Engine::vec3f Engine::vec3f::operator*(const vec3f& rhs) {
  return {x * rhs.x, y * rhs.y, z * rhs.z};
}

// Vector Rotations

Engine::vec2f Engine::rotate(const vec2f& vec, const float& angle) {
  return {vec.x * cos(angle) - vec.y * sin(angle), vec.x * sin(angle) + vec.y * cos(angle)};
}

Engine::vec3f Engine::rotate(const vec3f& vec, const vec3f& angle) {
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
