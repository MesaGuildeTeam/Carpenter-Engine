#include "vec3.hpp"
#include <cmath>
#include <stdexcept>

/**
 * converts a vector to a string
 */
std::string std::to_string(const Engine::vec3& vec) {
    return "[" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z) + "]";
}

namespace Engine {

#pragma region constants

/**
 * vector of all zeros
 */
const vec3 vec3::zero = vec3(0);
/**
 * vector of all ones
 */
const vec3 vec3::one = vec3(1);
/**
 * positive x unit vector
 */
const vec3 vec3::right = vec3(1,0,0);
/**
 * negative x unit vector
 */
const vec3 vec3::left = vec3(-1,0,0);
/**
 * positive y unit vector
 */
const vec3 vec3::up = vec3(0,1,0);
/**
 * negative y unit vector
 */
const vec3 vec3::down = vec3(0,-1,0);
/**
 * positive z unit vector
 */
const vec3 vec3::forward = vec3(0,0,1);
/**
 * negative z unit vector
 */
const vec3 vec3::back = vec3(0,0,-1);

#pragma endregion constants

#pragma region constructors

/**
 * default constructor, fills the vector with 0
 */
vec3::vec3(){
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

#pragma endregion constructors

#pragma region conversions

/**
 * casts a vector to a bool
 * true if all components are non-zero
 * to check if any components are non-zero, compare with vec3::zero rather than casting
 */
vec3::operator bool() const {
    return x && y && z;
}

/**
 * casts a boolean vector to a float vector
 */
vec3::vec3(const vec3b& vec){
    x = vec.x;
    y = vec.y;
    z = vec.z;
}

#pragma endregion conversions

#pragma region accessors

/**
 * Array accessor
 * Returns the component at index i, 0-indexed
 */
float& vec3::operator [](unsigned int i) {
    if (i >= 3) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

/**
 * Array accessor
 * Returns the component at index i, 0-indexed
 */
const float& vec3::operator [](unsigned int i) const {
    if (i >= 3) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

#pragma endregion accessors

#pragma region iteration

/**
 * Iterator to the first component
 */
auto vec3::begin() noexcept {
    return data.begin();
}

/**
 * Iterator to the end of the components
 */
auto vec3::end() noexcept {
    return data.end();
}

/**
 * Iterator to the first component
 */
auto vec3::begin() const noexcept {
    return data.begin();
}

/**
 * Iterator to the end of the components
 */
auto vec3::end() const noexcept {
    return data.end();
}

/**
 * Iterator to the first component
 */
auto vec3::cbegin() const noexcept {
    return data.cbegin();
}

/**
 * Iterator to the end of the components
 */
auto vec3::cend() const noexcept {
    return data.cend();
}

/**
 * Reverse iterator to the first component
 */
auto vec3::rbegin() noexcept {
    return data.rbegin();
}

/**
 * Reverse iterator to the end of the components
 */
auto vec3::rend() noexcept {
    return data.rend();
}

/**
 * Reverse iterator to the first component
 */
auto vec3::rbegin() const noexcept {
    return data.rbegin();
}

/**
 * Reverse iterator to the end of the components
 */
auto vec3::rend() const noexcept {
    return data.rend();
}

/**
 * Reverse iterator to the first component
 */
auto vec3::crbegin() const noexcept {
    return data.crbegin();
}

/**
 * Reverse iterator to the end of the components
 */
auto vec3::crend() const noexcept {
    return data.crend();
}

#pragma endregion iteration

#pragma region overloads

/**
 * stream insertion operator
 */
std::ostream& operator <<(std::ostream& os, const vec3& vec) {
    os << std::to_string(vec);
    return os;
}

/**
 * Copy assignment operator
 */
vec3& vec3::operator =(const vec3& other) {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}

/**
 * Component-wise addition operator
 */
vec3 operator +(const vec3& a, const vec3& b) {
    return vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

/**
 * Component-wise addition operator
 */
vec3 operator +(const float& a, const vec3& b) {
    return vec3(a + b.x, a + b.y, a + b.z);
}

/**
 * Component-wise addition operator
 */
vec3 operator +(const vec3& a, const float& b) {
    return vec3(a.x + b, a.y + b, a.z + b);
}

/**
 * Component-wise subtraction operator
 */
vec3 operator -(const vec3& a, const vec3& b) {
    return vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

/**
 * Component-wise subtraction operator
 */
vec3 operator -(const float& a, const vec3& b) {
    return vec3(a - b.x, a - b.y, a - b.z);
}

/**
 * Component-wise subtraction operator
 */
vec3 operator -(const vec3& a, const float& b) {
    return vec3(a.x - b, a.y - b, a.z - b);
}

/**
 * Component-wise negation operator
 */
vec3 vec3::operator -() const {
    return vec3(-x, -y, -z);
}

/**
 * Component-wise multiplication operator
 */
vec3 operator *(const vec3& a, const vec3& b) {
    return vec3(a.x * b.x, a.y * b.y, a.z * b.z);
}

/**
 * Component-wise multiplication operator
 */
vec3 operator *(const float& a, const vec3& b) {
    return vec3(a * b.x, a * b.y, a * b.z);
}

/**
 * Component-wise multiplication operator
 */
vec3 operator *(const vec3& a, const float& b) {
    return vec3(a.x * b, a.y * b, a.z * b);
}

/**
 * Component-wise division operator
 */
vec3 operator /(const vec3& a, const vec3& b) {
    return vec3(a.x / b.x, a.y / b.y, a.z / b.z);
}

/**
 * Component-wise division operator
 */
vec3 operator /(const float& a, const vec3& b) {
    return vec3(a / b.x, a / b.y, a / b.z);
}

/**
 * Component-wise division operator
 */
vec3 operator /(const vec3& a, const float& b) {
    return vec3(a.x / b, a.y / b, a.z / b);
}

/**
 * Component-wise equality operator
 */
vec3b vec3::operator ==(const vec3& other) const {
    return vec3b(x == other.x, y == other.y, z == other.z);
}

/**
 * Component-wise inequality operator
 */
vec3b vec3::operator !=(const vec3& other) const {
    return vec3b(x != other.x, y != other.y, z != other.z);
}

/**
 * Component-wise less than operator
 */
vec3b vec3::operator <(const vec3& other) const {
    return vec3b(x < other.x, y < other.y, z < other.z);
}

/**
 * Component-wise greater than operator
 */
vec3b vec3::operator >(const vec3& other) const {
    return vec3b(x > other.x, y > other.y, z > other.z);
}

/**
 * Component-wise less than or equal to operator
 */
vec3b vec3::operator <=(const vec3& other) const {
    return vec3b(x <= other.x, y <= other.y, z <= other.z);
}

/**
 * Component-wise greater than or equal to operator
 */
vec3b vec3::operator >=(const vec3& other) const {
    return vec3b(x >= other.x, y >= other.y, z >= other.z);
}

/**
 * Component-wise addition assignment operator
 */
vec3 vec3::operator +=(const vec3& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

/**
 * Component-wise addition assignment operator
 */
vec3 vec3::operator +=(const float& other) {
    x += other;
    y += other;
    z += other;
    return *this;
}

/**
 * Component-wise subtraction assignment operator
 */
vec3 vec3::operator -=(const vec3& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

/**
 * Component-wise subtraction assignment operator
 */
vec3 vec3::operator -=(const float& other) {
    x -= other;
    y -= other;
    z -= other;
    return *this;
}

/**
 * Component-wise multiplication assignment operator
 */
vec3 vec3::operator *=(const vec3& other) {
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
}

/**
 * Component-wise multiplication assignment operator
 */
vec3 vec3::operator *=(const float& other) {
    x *= other;
    y *= other;
    z *= other;
    return *this;
}

/**
 * Component-wise division assignment operator
 */
vec3 vec3::operator /=(const vec3& other) {
    x /= other.x;
    y /= other.y;
    z /= other.z;
    return *this;
}

/**
 * Component-wise division assignment operator
 */
vec3 vec3::operator /=(const float& other) {
    x /= other;
    y /= other;
    z /= other;
    return *this;
}

/**
 * Component-wise increment operator
 */
vec3 vec3::operator ++() {
    x++;
    y++;
    z++;
    return *this;
}

/**
 * Component-wise decrement operator
 */
vec3 vec3::operator --() {
    x--;
    y--;
    z--;
    return *this;
}

#pragma endregion overloads

#pragma region vector operations

/**
 * dot product of two vectors
 */
float vec3::dot(const vec3& a, const vec3& b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

/**
 * cross product of two vectors
 */
vec3 vec3::cross(const vec3& a, const vec3& b) {
    return vec3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}

/**
 * angle between two vectors
 */
double vec3::angleBetween(const vec3& a, const vec3& b) {
    return acos( dot(a,b) / sqrt(a.lengthSquared()*b.lengthSquared()) );
}

/**
 * reflects incident vector, I, over surface with normal, N
 */
vec3 vec3::reflect(const vec3& I, const vec3& N) {
    return I - 2.0f*N*dot(N, I)/dot(N,N);
}

/**
 * returns a vector in the same direction as the input vector, but with a length of 1
 */
vec3 vec3::normalize(const vec3& vec) {
    return vec/vec.length();
}

/**
 * returns a vector in the same direction as this vector, but with a length of 1
 */
vec3 vec3::normalized() const {
    return *this/length();
}

/**
 * returns the squared distance between two vectors
 */
float vec3::distanceSquared(const vec3& a, const vec3& b) {
    return (b - a).lengthSquared();
}

/**
 * returns the distance between two vectors
 */
float vec3::distance(const vec3& a, const vec3& b) {
    return (b - a).length();
}

/**
 * Returns the length squared of the vector
 * equivalent to dot product with itself
 */
float vec3::lengthSquared() const {
    return dot(*this, *this);
}

/**
 * Returns the length squared of the vector
 * equivalent to dot product with itself
 */
float vec3::lengthSquared(const vec3& a) {
    return dot(a, a);
}

/**
 * Returns the length of the vector
 */
float vec3::length() const {
    return sqrtf(lengthSquared());
}

/**
 * Returns the length of the vector
 */
float vec3::length(const vec3& a) {
    return sqrtf(a.lengthSquared());
}

/**
 * Returns a tangent vector of the same length to the current vector
 * the expression used is (-y,x,0) if |x| <= |z|, else (0,-z,y)
 */
vec3 vec3::tangent() const {
    if (fabs(x) <= fabs(z)) {
        return vec3(-y, x, 0);
    } else {
        return vec3(0, -z, y);
    }
}

/**
 * Returns a tangent vector of the same length to the current vector
 * the expression used is (-y,x,0) if |x| <= |z|, else (0,-z,y)
 */
vec3 vec3::tangent(const vec3& vec) {
    if (fabs(vec.x) <= fabs(vec.z)) {
        return vec3(-vec.y, vec.x, 0);
    } else {
        return vec3(0, -vec.z, vec.y);
    }
}

#pragma endregion vector operations

}
