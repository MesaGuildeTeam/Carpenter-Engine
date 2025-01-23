#include "vec2.hpp"
#include <cmath>
#include <stdexcept>

/**
 * converts a vector to a string
 */
std::string std::to_string(const Engine::vec2& vec) {
    return "[" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + "]";
}

namespace Engine {

#pragma region constants

/**
 * vector of all zeros
 */
const vec2 vec2::zero = vec2(0);
/**
 * vector of all ones
 */
const vec2 vec2::one = vec2(1);
/**
 * positive x unit vector
 */
const vec2 vec2::right = vec2(1,0);
/**
 * negative x unit vector
 */
const vec2 vec2::left = vec2(-1,0);
/**
 * positive y unit vector
 */
const vec2 vec2::up = vec2(0,1);
/**
 * negative y unit vector
 */
const vec2 vec2::down = vec2(0,-1);

#pragma endregion constants

#pragma region constructors

/**
 * default constructor, fills the vector with 0
 */
vec2::vec2(){
    x = 0.0f;
    y = 0.0f;
}

#pragma endregion constructors

#pragma region conversions

/**
 * casts a vector to a bool
 * true if all components are non-zero
 * to check if any components are non-zero, compare with vec2::zero rather than casting
 */
vec2::operator bool() const {
    return x && y;
}

/**
 * casts a boolean vector to a float vector
 */
vec2::vec2(const vec2b& vec){
    x = vec.x;
    y = vec.y;
}

#pragma endregion conversions

#pragma region accessors

/**
 * Array accessor
 * Returns the component at index i, 0-indexed
 */
float& vec2::operator [](unsigned int i) {
    if (i >= 2) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

/**
 * Array accessor
 * Returns the component at index i, 0-indexed
 */
const float& vec2::operator [](unsigned int i) const {
    if (i >= 2) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

#pragma endregion accessors

#pragma region iteration

/**
 * Iterator to the first component
 */
auto vec2::begin() noexcept {
    return data.begin();
}

/**
 * Iterator to the end of the components
 */
auto vec2::end() noexcept {
    return data.end();
}

/**
 * Iterator to the first component
 */
auto vec2::begin() const noexcept {
    return data.begin();
}

/**
 * Iterator to the end of the components
 */
auto vec2::end() const noexcept {
    return data.end();
}

/**
 * Iterator to the first component
 */
auto vec2::cbegin() const noexcept {
    return data.cbegin();
}

/**
 * Iterator to the end of the components
 */
auto vec2::cend() const noexcept {
    return data.cend();
}

/**
 * Reverse iterator to the first component
 */
auto vec2::rbegin() noexcept {
    return data.rbegin();
}

/**
 * Reverse iterator to the end of the components
 */
auto vec2::rend() noexcept {
    return data.rend();
}

/**
 * Reverse iterator to the first component
 */
auto vec2::rbegin() const noexcept {
    return data.rbegin();
}

/**
 * Reverse iterator to the end of the components
 */
auto vec2::rend() const noexcept {
    return data.rend();
}

/**
 * Reverse iterator to the first component
 */
auto vec2::crbegin() const noexcept {
    return data.crbegin();
}

/**
 * Reverse iterator to the end of the components
 */
auto vec2::crend() const noexcept {
    return data.crend();
}

#pragma endregion iteration

#pragma region overloads

/**
 * stream insertion operator
 */
std::ostream& operator <<(std::ostream& os, const vec2& vec) {
    os << std::to_string(vec);
    return os;
}

/**
 * Copy assignment operator
 */
vec2& vec2::operator =(const vec2& other) {
    x = other.x;
    y = other.y;
    return *this;
}

/**
 * Component-wise addition operator
 */
vec2 operator +(const vec2& a, const vec2& b) {
    return vec2(a.x + b.x, a.y + b.y);
}

/**
 * Component-wise addition operator
 */
vec2 operator +(const float& a, const vec2& b) {
    return vec2(a + b.x, a + b.y);
}

/**
 * Component-wise addition operator
 */
vec2 operator +(const vec2& a, const float& b) {
    return vec2(a.x + b, a.y + b);
}

/**
 * Component-wise subtraction operator
 */
vec2 operator -(const vec2& a, const vec2& b) {
    return vec2(a.x - b.x, a.y - b.y);
}

/**
 * Component-wise subtraction operator
 */
vec2 operator -(const float& a, const vec2& b) {
    return vec2(a - b.x, a - b.y);
}

/**
 * Component-wise subtraction operator
 */
vec2 operator -(const vec2& a, const float& b) {
    return vec2(a.x - b, a.y - b);
}

/**
 * Component-wise negation operator
 */
vec2 vec2::operator -() const {
    return vec2(-x, -y);
}

/**
 * Component-wise multiplication operator
 */
vec2 operator *(const vec2& a, const vec2& b) {
    return vec2(a.x * b.x, a.y * b.y);
}

/**
 * Component-wise multiplication operator
 */
vec2 operator *(const float& a, const vec2& b) {
    return vec2(a * b.x, a * b.y);
}

/**
 * Component-wise multiplication operator
 */
vec2 operator *(const vec2& a, const float& b) {
    return vec2(a.x * b, a.y * b);
}

/**
 * Component-wise division operator
 */
vec2 operator /(const vec2& a, const vec2& b) {
    return vec2(a.x / b.x, a.y / b.y);
}

/**
 * Component-wise division operator
 */
vec2 operator /(const float& a, const vec2& b) {
    return vec2(a / b.x, a / b.y);
}

/**
 * Component-wise division operator
 */
vec2 operator /(const vec2& a, const float& b) {
    return vec2(a.x / b, a.y / b);
}

/**
 * Component-wise equality operator
 */
vec2b vec2::operator ==(const vec2& other) const {
    return vec2b(x == other.x, y == other.y);
}

/**
 * Component-wise inequality operator
 */
vec2b vec2::operator !=(const vec2& other) const {
    return vec2b(x != other.x, y != other.y);
}

/**
 * Component-wise less than operator
 */
vec2b vec2::operator <(const vec2& other) const {
    return vec2b(x < other.x, y < other.y);
}

/**
 * Component-wise greater than operator
 */
vec2b vec2::operator >(const vec2& other) const {
    return vec2b(x > other.x, y > other.y);
}

/**
 * Component-wise less than or equal to operator
 */
vec2b vec2::operator <=(const vec2& other) const {
    return vec2b(x <= other.x, y <= other.y);
}

/**
 * Component-wise greater than or equal to operator
 */
vec2b vec2::operator >=(const vec2& other) const {
    return vec2b(x >= other.x, y >= other.y);
}

/**
 * Component-wise addition assignment operator
 */
vec2 vec2::operator +=(const vec2& other) {
    x += other.x;
    y += other.y;
    return *this;
}

/**
 * Component-wise addition assignment operator
 */
vec2 vec2::operator +=(const float& other) {
    x += other;
    y += other;
    return *this;
}

/**
 * Component-wise subtraction assignment operator
 */
vec2 vec2::operator -=(const vec2& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

/**
 * Component-wise subtraction assignment operator
 */
vec2 vec2::operator -=(const float& other) {
    x -= other;
    y -= other;
    return *this;
}

/**
 * Component-wise multiplication assignment operator
 */
vec2 vec2::operator *=(const vec2& other) {
    x *= other.x;
    y *= other.y;
    return *this;
}

/**
 * Component-wise multiplication assignment operator
 */
vec2 vec2::operator *=(const float& other) {
    x *= other;
    y *= other;
    return *this;
}

/**
 * Component-wise division assignment operator
 */
vec2 vec2::operator /=(const vec2& other) {
    x /= other.x;
    y /= other.y;
    return *this;
}

/**
 * Component-wise division assignment operator
 */
vec2 vec2::operator /=(const float& other) {
    x /= other;
    y /= other;
    return *this;
}

/**
 * Component-wise increment operator
 */
vec2 vec2::operator ++() {
    x++;
    y++;
    return *this;
}

/**
 * Component-wise decrement operator
 */
vec2 vec2::operator --() {
    x--;
    y--;
    return *this;
}

#pragma endregion overloads

#pragma region vector operations

/**
 * dot product of two vectors
 */
float vec2::dot(const vec2& a, const vec2& b) {
    return a.x*b.x + a.y*b.y;
}

/**
 * cross product of two vectors
 * returns the determinant of the 2x2 matrix formed by the vectors
 */
float vec2::cross(const vec2& a, const vec2& b){
    return a.x*b.y - a.y*b.x;
}

/**
 * angle between two vectors
 */
double vec2::angleBetween(const vec2& a, const vec2& b) {
    return acos( dot(a,b) / sqrt(a.lengthSquared()*b.lengthSquared()) );
}

/**
 * reflects incident vector, I, over surface with normal, N
 */
vec2 vec2::reflect(const vec2& I, const vec2& N) {
    return I - 2.0f*N*dot(N, I)/dot(N,N);
}

/**
 * returns a vector in the same direction as the input vector, but with a length of 1
 */
vec2 vec2::normalize(const vec2& vec) {
    return vec/vec.length();
}

/**
 * returns a vector in the same direction as this vector, but with a length of 1
 */
vec2 vec2::normalized() const {
    return *this/length();
}

/**
 * returns the squared distance between two vectors
 */
float vec2::distanceSquared(const vec2& a, const vec2& b) {
    return (b - a).lengthSquared();
}

/**
 * returns the distance between two vectors
 */
float vec2::distance(const vec2& a, const vec2& b) {
    return (b - a).length();
}

/**
 * Returns the length squared of the vector
 * equivalent to dot product with itself
 */
float vec2::lengthSquared() const {
    return dot(*this, *this);
}

/**
 * Returns the length squared of the vector
 * equivalent to dot product with itself
 */
float vec2::lengthSquared(const vec2& a) {
    return dot(a, a);
}

/**
 * Returns the length of the vector
 */
float vec2::length() const {
    return sqrtf(lengthSquared());
}

/**
 * Returns the length of the vector
 */
float vec2::length(const vec2& a) {
    return sqrtf(a.lengthSquared());
}

/**
 * Returns a tangent vector of the same length to the current vector
 * the expression used is (-y,x)
 */
vec2 vec2::tangent() const {
    return vec2(-y, x);
}

/**
 * Returns a tangent vector of the same length to the current vector
 * the expression used is (-y,x)
 */
vec2 vec2::tangent(const vec2& vec) {
    return vec2(-vec.y, vec.x);
}

#pragma endregion vector operations

}