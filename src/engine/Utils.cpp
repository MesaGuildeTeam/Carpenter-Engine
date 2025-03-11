#include "Utils.hpp"
#include <cmath>

#define M_PI 3.14159265358979323846

// 2D Vector Operations

Engine::Vec2f Engine::Vec2f::operator+(const Engine::Vec2f& rhs) {
  return {x + rhs.x, y + rhs.y};
}

Engine::Vec2f Engine::Vec2f::operator*(const float& rhs) {
  return {x * rhs, y * rhs};
}

Engine::Vec2f Engine::Vec2f::operator*(const Vec2f& rhs) {
  return {x * rhs.x, y * rhs.y};
}

// 3D Vector Operations

Engine::Vec3f Engine::Vec3f::operator+(const Engine::Vec3f& rhs) {
  return {x + rhs.x, y + rhs.y, z + rhs.z};
}

Engine::Vec3f Engine::Vec3f::operator*(const float& rhs) {
  return {x * rhs, y * rhs, z * rhs};
}

Engine::Vec3f Engine::Vec3f::operator*(const Vec3f& rhs) {
  return {x * rhs.x, y * rhs.y, z * rhs.z};
}

float Engine::Vec3f::lengthSquared() {
  return sqrt(x * x + y * y + z * z);
}

bool Engine::Vec3f::operator==(const Engine::Vec3f& rhs) {
  return x == rhs.x && y == rhs.y && z == rhs.z;
}

// Vector Rotations

Engine::Vec2f Engine::Rotate(Vec2f v, float angle) {
  return {v.x * cos(angle) - v.y * sin(angle), v.x * sin(angle) + v.y * cos(angle)};
}

Engine::Vec3f Engine::Rotate(Vec3f v, Vec3f angle) {
  float cosX = cosf(angle.x);
  float sinX = sinf(angle.x);
  float cosY = cosf(angle.y);
  float sinY = sinf(angle.y);
  float cosZ = cosf(angle.z);
  float sinZ = sinf(angle.z);

  return {
    cosY * (sinZ * v.y + cosZ * v.x) - sinY * v.z,
    sinX * (cosY * v.z + sinY * (sinZ * v.y + cosZ * v.x)) + cosX * (cosZ * v.y - sinZ * v.x),
    cosX * (cosY * v.z + sinY * (sinZ * v.y + cosZ * v.x)) - sinX * (cosZ * v.y - sinZ * v.x)
  };
}

float Engine::InvSQRT(float x) {
  // There is a better way to do this
  return 1.0f / sqrt(x);
}