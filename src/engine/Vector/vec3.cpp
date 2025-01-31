#include "vec3.hpp"
#include <cmath>
#include <stdexcept>

namespace Engine {

#pragma region constants


const vec3 vec3::zero = vec3(0);

const vec3 vec3::one = vec3(1);

const vec3 vec3::right = vec3(1,0,0);

const vec3 vec3::left = vec3(-1,0,0);

const vec3 vec3::up = vec3(0,1,0);

const vec3 vec3::down = vec3(0,-1,0);

const vec3 vec3::forward = vec3(0,0,1);

const vec3 vec3::back = vec3(0,0,-1);

#pragma endregion constants

#pragma region constructors


vec3::vec3(){
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

#pragma endregion constructors

#pragma region conversions


vec3::operator bool() const {
    return x && y && z;
}


vec3::vec3(const bvec3& vec){
    x = vec.x;
    y = vec.y;
    z = vec.z;
}

#pragma endregion conversions

#pragma region accessors


float& vec3::operator [](unsigned int i) {
    if (i >= 3) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}


const float& vec3::operator [](unsigned int i) const {
    if (i >= 3) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

#pragma endregion accessors

#pragma region iteration


auto vec3::begin() noexcept {
    return data.begin();
}


auto vec3::end() noexcept {
    return data.end();
}


auto vec3::begin() const noexcept {
    return data.begin();
}


auto vec3::end() const noexcept {
    return data.end();
}


auto vec3::cbegin() const noexcept {
    return data.cbegin();
}


auto vec3::cend() const noexcept {
    return data.cend();
}


auto vec3::rbegin() noexcept {
    return data.rbegin();
}


auto vec3::rend() noexcept {
    return data.rend();
}


auto vec3::rbegin() const noexcept {
    return data.rbegin();
}


auto vec3::rend() const noexcept {
    return data.rend();
}


auto vec3::crbegin() const noexcept {
    return data.crbegin();
}


auto vec3::crend() const noexcept {
    return data.crend();
}

#pragma endregion iteration

#pragma region overloads


vec3& vec3::operator =(const vec3& other) {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}


vec3 operator +(const vec3& a, const vec3& b) {
    return vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}


vec3 operator +(const float& a, const vec3& b) {
    return vec3(a + b.x, a + b.y, a + b.z);
}


vec3 operator +(const vec3& a, const float& b) {
    return vec3(a.x + b, a.y + b, a.z + b);
}


vec3 operator -(const vec3& a, const vec3& b) {
    return vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}


vec3 operator -(const float& a, const vec3& b) {
    return vec3(a - b.x, a - b.y, a - b.z);
}


vec3 operator -(const vec3& a, const float& b) {
    return vec3(a.x - b, a.y - b, a.z - b);
}


vec3 vec3::operator -() const {
    return vec3(-x, -y, -z);
}


vec3 operator *(const vec3& a, const vec3& b) {
    return vec3(a.x * b.x, a.y * b.y, a.z * b.z);
}


vec3 operator *(const float& a, const vec3& b) {
    return vec3(a * b.x, a * b.y, a * b.z);
}


vec3 operator *(const vec3& a, const float& b) {
    return vec3(a.x * b, a.y * b, a.z * b);
}


vec3 operator /(const vec3& a, const vec3& b) {
    return vec3(a.x / b.x, a.y / b.y, a.z / b.z);
}


vec3 operator /(const float& a, const vec3& b) {
    return vec3(a / b.x, a / b.y, a / b.z);
}


vec3 operator /(const vec3& a, const float& b) {
    return vec3(a.x / b, a.y / b, a.z / b);
}


bvec3 vec3::operator ==(const vec3& other) const {
    return bvec3(x == other.x, y == other.y, z == other.z);
}


bvec3 vec3::operator !=(const vec3& other) const {
    return bvec3(x != other.x, y != other.y, z != other.z);
}


bvec3 vec3::operator <(const vec3& other) const {
    return bvec3(x < other.x, y < other.y, z < other.z);
}


bvec3 vec3::operator >(const vec3& other) const {
    return bvec3(x > other.x, y > other.y, z > other.z);
}


bvec3 vec3::operator <=(const vec3& other) const {
    return bvec3(x <= other.x, y <= other.y, z <= other.z);
}


bvec3 vec3::operator >=(const vec3& other) const {
    return bvec3(x >= other.x, y >= other.y, z >= other.z);
}


vec3 vec3::operator +=(const vec3& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}


vec3 vec3::operator +=(const float& other) {
    x += other;
    y += other;
    z += other;
    return *this;
}


vec3 vec3::operator -=(const vec3& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}


vec3 vec3::operator -=(const float& other) {
    x -= other;
    y -= other;
    z -= other;
    return *this;
}


vec3 vec3::operator *=(const vec3& other) {
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
}


vec3 vec3::operator *=(const float& other) {
    x *= other;
    y *= other;
    z *= other;
    return *this;
}


vec3 vec3::operator /=(const vec3& other) {
    x /= other.x;
    y /= other.y;
    z /= other.z;
    return *this;
}


vec3 vec3::operator /=(const float& other) {
    x /= other;
    y /= other;
    z /= other;
    return *this;
}


vec3 vec3::operator ++() {
    x++;
    y++;
    z++;
    return *this;
}


vec3 vec3::operator --() {
    x--;
    y--;
    z--;
    return *this;
}

#pragma endregion overloads

#pragma region vector operations


vec3 vec3::normalized() const {
    return *this/length();
}


float vec3::lengthSquared() const {
    return dot(*this, *this);
}


float vec3::length() const {
    return sqrtf(lengthSquared());
}


vec3 vec3::tangent() const {
    if (fabs(x) <= fabs(z)) {
        return vec3(-y, x, 0);
    } else {
        return vec3(0, -z, y);
    }
}


float distanceSquared(const vec3& a, const vec3& b) {
    return (b - a).lengthSquared();
}


float distance(const vec3& a, const vec3& b) {
    return (b - a).length();
}


float dot(const vec3& a, const vec3& b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}


vec3 cross(const vec3& a, const vec3& b) {
    return vec3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}


double angleBetween(const vec3& a, const vec3& b) {
    return acos( dot(a,b) / sqrt(a.lengthSquared()*b.lengthSquared()) );
}


vec3 reflect(const vec3& I, const vec3& N) {
    return I - 2.0f*N*dot(N, I)/dot(N,N);
}

std::string to_string(const vec3& vec) {
    return "[" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z) + "]";
}

#pragma endregion vector operations

}
