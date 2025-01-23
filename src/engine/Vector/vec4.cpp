#include "vec4.hpp"
#include <cmath>
#include <stdexcept>

/**
 * converts a vector to a string
 */
std::string std::to_string(const Engine::vec4& vec) {
    return "[" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z) + ", " + std::to_string(vec.w) + "]";
}

namespace Engine {

#pragma region constants

/**
 * vector of all zeros
 */
const vec4 vec4::zero = vec4(0);
/**
 * vector of all ones
 */
const vec4 vec4::one = vec4(1);
/**
 * positive x unit vector
 */
const vec4 vec4::up = vec4(1,0,0,0);
/**
 * negative x unit vector
 */
const vec4 vec4::down = vec4(-1,0,0,0);
/**
 * positive y unit vector
 */
const vec4 vec4::left = vec4(0,1,0,0);
/**
 * negative y unit vector
 */
const vec4 vec4::right = vec4(0,-1,0,0);
/**
 * positive z unit vector
 */
const vec4 vec4::forward = vec4(0,0,1,0);
/**
 * negative z unit vector
 */
const vec4 vec4::back = vec4(0,0,-1,0);
/**
 * positive w unit vector
 */
const vec4 vec4::ana = vec4(0,0,0,1);
/**
 * negative w unit vector
 */
const vec4 vec4::kata = vec4(0,0,0,-1);

#pragma endregion constants

#pragma region constructors

/**
 * default constructor, fills the vector with 0
 */
vec4::vec4(){
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    w = 0.0f;
}

#pragma endregion constructors

#pragma region conversions

/**
 * casts a vector to a bool
 * true if all components are non-zero
 * to check if any components are non-zero, compare with vec4::zero rather than casting
 */
vec4::operator bool() const {
    return x && y && z && w;
}

/**
 * casts a boolean vector to a float vector
 */
vec4::vec4(const vec4b& vec){
    x = vec.x;
    y = vec.y;
    z = vec.z;
    w = vec.w;
}

#pragma endregion conversions

#pragma region accessors

/**
 * Array accessor
 * Returns the component at index i, 0-indexed
 */
float& vec4::operator [](unsigned int i) {
    if (i >= 4) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

/**
 * Array accessor
 * Returns the component at index i, 0-indexed
 */
const float& vec4::operator [](unsigned int i) const {
    if (i >= 4) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

#pragma endregion accessors

#pragma region iteration

/**
 * Iterator to the first component
 */
auto vec4::begin() noexcept {
    return data.begin();
}

/**
 * Iterator to the end of the components
 */
auto vec4::end() noexcept {
    return data.end();
}

/**
 * Iterator to the first component
 */
auto vec4::begin() const noexcept {
    return data.begin();
}

/**
 * Iterator to the end of the components
 */
auto vec4::end() const noexcept {
    return data.end();
}

/**
 * Iterator to the first component
 */
auto vec4::cbegin() const noexcept {
    return data.cbegin();
}

/**
 * Iterator to the end of the components
 */
auto vec4::cend() const noexcept {
    return data.cend();
}

/**
 * Reverse iterator to the first component
 */
auto vec4::rbegin() noexcept {
    return data.rbegin();
}

/**
 * Reverse iterator to the end of the components
 */
auto vec4::rend() noexcept {
    return data.rend();
}

/**
 * Reverse iterator to the first component
 */
auto vec4::rbegin() const noexcept {
    return data.rbegin();
}

/**
 * Reverse iterator to the end of the components
 */
auto vec4::rend() const noexcept {
    return data.rend();
}

/**
 * Reverse iterator to the first component
 */
auto vec4::crbegin() const noexcept {
    return data.crbegin();
}

/**
 * Reverse iterator to the end of the components
 */
auto vec4::crend() const noexcept {
    return data.crend();
}

#pragma endregion iteration

#pragma region overloads

/**
 * stream insertion operator
 */
std::ostream& operator <<(std::ostream& os, const vec4& vec) {
    os << std::to_string(vec);
    return os;
}

/**
 * Copy assignment operator
 */
vec4& vec4::operator =(const vec4& other) {
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
}

/**
 * Component-wise addition operator
 */
vec4 operator +(const vec4& a, const vec4& b) {
    return vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

/**
 * Component-wise addition operator
 */
vec4 operator +(const float& a, const vec4& b) {
    return vec4(a + b.x, a + b.y, a + b.z, a + b.w);
}

/**
 * Component-wise addition operator
 */
vec4 operator +(const vec4& a, const float& b) {
    return vec4(a.x + b, a.y + b, a.z + b, a.w + b);
}

/**
 * Component-wise subtraction operator
 */
vec4 operator -(const vec4& a, const vec4& b) {
    return vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

/**
 * Component-wise subtraction operator
 */
vec4 operator -(const float& a, const vec4& b) {
    return vec4(a - b.x, a - b.y, a - b.z, a - b.w);
}

/**
 * Component-wise subtraction operator
 */
vec4 operator -(const vec4& a, const float& b) {
    return vec4(a.x - b, a.y - b, a.z - b, a.w - b);
}

/**
 * Component-wise negation operator
 */
vec4 vec4::operator -() const {
    return vec4(-x, -y, -z, -w);
}

/**
 * Component-wise multiplication operator
 */
vec4 operator *(const vec4& a, const vec4& b) {
    return vec4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

/**
 * Component-wise multiplication operator
 */
vec4 operator *(const float& a, const vec4& b) {
    return vec4(a * b.x, a * b.y, a * b.z, a * b.w);
}

/**
 * Component-wise multiplication operator
 */
vec4 operator *(const vec4& a, const float& b) {
    return vec4(a.x * b, a.y * b, a.z * b, a.w * b);
}

/**
 * Component-wise division operator
 */
vec4 operator /(const vec4& a, const vec4& b) {
    return vec4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}

/**
 * Component-wise division operator
 */
vec4 operator /(const float& a, const vec4& b) {
    return vec4(a / b.x, a / b.y, a / b.z, a / b.w);
}

/**
 * Component-wise division operator
 */
vec4 operator /(const vec4& a, const float& b) {
    return vec4(a.x / b, a.y / b, a.z / b, a.w / b);
}

/**
 * Component-wise equality operator
 */
vec4b vec4::operator ==(const vec4& other) const {
    return vec4b(x == other.x, y == other.y, z == other.z, w == other.w);
}

/**
 * Component-wise inequality operator
 */
vec4b vec4::operator !=(const vec4& other) const {
    return vec4b(x != other.x, y != other.y, z != other.z, w != other.w);
}

/**
 * Component-wise less than operator
 */
vec4b vec4::operator <(const vec4& other) const {
    return vec4b(x < other.x, y < other.y, z < other.z, w < other.w);
}

/**
 * Component-wise greater than operator
 */
vec4b vec4::operator >(const vec4& other) const {
    return vec4b(x > other.x, y > other.y, z > other.z, w > other.w);
}

/**
 * Component-wise less than or equal to operator
 */
vec4b vec4::operator <=(const vec4& other) const {
    return vec4b(x <= other.x, y <= other.y, z <= other.z, w <= other.w);
}

/**
 * Component-wise greater than or equal to operator
 */
vec4b vec4::operator >=(const vec4& other) const {
    return vec4b(x >= other.x, y >= other.y, z >= other.z, w >= other.w);   
}

/**
 * Component-wise addition assignment operator
 */
vec4 vec4::operator +=(const vec4& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
}

/**
 * Component-wise addition assignment operator
 */
vec4 vec4::operator +=(const float& other) {
    x += other;
    y += other;
    z += other;
    w += other;
    return *this;
}

/**
 * Component-wise subtraction assignment operator
 */
vec4 vec4::operator -=(const vec4& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return *this;
}

/**
 * Component-wise subtraction assignment operator
 */
vec4 vec4::operator -=(const float& other) {
    x -= other;
    y -= other;
    z -= other;
    w -= other;
    return *this;
}

/**
 * Component-wise multiplication assignment operator
 */
vec4 vec4::operator *=(const vec4& other) {
    x *= other.x;
    y *= other.y;
    z *= other.z;
    w *= other.w;
    return *this;
}

/**
 * Component-wise multiplication assignment operator
 */
vec4 vec4::operator *=(const float& other) {
    x *= other;
    y *= other;
    z *= other;
    w *= other;
    return *this;
}

/**
 * Component-wise division assignment operator
 */
vec4 vec4::operator /=(const vec4& other) {
    x /= other.x;
    y /= other.y;
    z /= other.z;
    w /= other.w;
    return *this;
}

/**
 * Component-wise division assignment operator
 */
vec4 vec4::operator /=(const float& other) {
    x /= other;
    y /= other;
    z /= other;
    w /= other;
    return *this;
}

/**
 * Component-wise increment operator
 */
vec4 vec4::operator ++() {
    x++;
    y++;
    z++;
    w++;
    return *this;
}

/**
 * Component-wise decrement operator
 */
vec4 vec4::operator --() {
    x--;
    y--;
    z--;
    w--;
    return *this;
}

#pragma endregion overloads

#pragma region vector operations

/**
 * dot product of two vectors
 */
float vec4::dot(const vec4& a, const vec4& b) {
    return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
}

/**
 * angle between two vectors
 */
double vec4::angleBetween(const vec4& a, const vec4& b) {
    return acos( dot(a,b) / sqrt(a.lengthSquared()*b.lengthSquared()) );
}

/**
 * reflects incident vector, I, over surface with normal, N
 */
vec4 vec4::reflect(const vec4& I, const vec4& N) {
    return I - 2.0f*N*dot(N, I)/dot(N,N);
}

/**
 * returns a vector in the same direction as the input vector, but with a length of 1
 */
vec4 vec4::normalize(const vec4& vec) {
    return vec/vec.length();
}

/**
 * returns a vector in the same direction as this vector, but with a length of 1
 */
vec4 vec4::normalized() const {
    return *this/length();
}

/**
 * returns the squared distance between two vectors
 */
float vec4::distanceSquared(const vec4& a, const vec4& b) {
    return (b - a).lengthSquared();
}

/**
 * returns the distance between two vectors
 */
float vec4::distance(const vec4& a, const vec4& b) {
    return (b - a).length();
}

/**
 * Returns the length squared of the vector
 * equivalent to dot product with itself
 */
float vec4::lengthSquared() const {
    return dot(*this, *this);
}

/**
 * Returns the length squared of the vector
 * equivalent to dot product with itself
 */
float vec4::lengthSquared(const vec4& a) {
    return dot(a, a);
}

/**
 * Returns the length of the vector
 */
float vec4::length() const {
    return sqrtf(lengthSquared());
}

/**
 * Returns the length of the vector
 */
float vec4::length(const vec4& a) {
    return sqrtf(a.lengthSquared());
}

#pragma endregion vector operations

}