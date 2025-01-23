#include "vec3b.hpp"
#include <cmath>
#include <stdexcept>

/**
 * converts a vector to a string
 */
std::string std::to_string(const Engine::vec3b& vec) {
    return "[" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z) + "]";
}

namespace Engine {

#pragma region constants

/**
 * vector of all falses
 */
const vec3b vec3b::zero = vec3b(false);
/**
 * vector of all trues
 */
const vec3b vec3b::one = vec3b(true);

#pragma endregion constants

#pragma region constructors

/**
 * default constructor, fills the vector with false
 */
vec3b::vec3b() {
    x = false;
    y = false;
    z = false;
}

#pragma endregion constructors

#pragma region conversions

/**
 * casts a vector to a bool
 * true if all components are non-zero
 * to check if any components are non-zero, compare with vec4b::zero rather than casting
 */
vec3b::operator bool() const {
    return x && y && z;
}

/**
 * casts a float vector to a boolean vector
 */
vec3b::vec3b(const vec3& vec){
    x = vec.x > 0.0f;
    y = vec.y > 0.0f;
    z = vec.z > 0.0f;
}

#pragma endregion conversions

#pragma region accessors

/**
 * Array accessor
 * Returns the component at index i, 0-indexed
 */
bool& vec3b::operator [](unsigned int i){
    return data[i];
}

/**
 * Array accessor
 * Returns the component at index i, 0-indexed
 */
const bool& vec3b::operator [](unsigned int i) const {
    return data[i];
}

#pragma endregion accessors

#pragma region iteration

/**
 * Iterator to the first component
 */
auto vec3b::begin() noexcept {
    return data.begin();
}

/**
 * Iterator to the end of the components
 */
auto vec3b::end() noexcept {
    return data.end();
}

/**
 * Iterator to the first component
 */
auto vec3b::begin() const noexcept {
    return data.begin();
}

/**
 * Iterator to the end of the components
 */
auto vec3b::end() const noexcept {
    return data.end();
}

/**
 * Iterator to the first component
 */
auto vec3b::cbegin() const noexcept {
    return data.cbegin();
}

/**
 * Iterator to the end of the components
 */
auto vec3b::cend() const noexcept { 
    return data.cend();
}

/**
 * Reverse iterator to the first component
 */
auto vec3b::rbegin() noexcept {
    return data.rbegin();
}

/**
 * Reverse iterator to the end of the components
 */
auto vec3b::rend() noexcept {
    return data.rend();
}

/**
 * Reverse iterator to the first component
 */
auto vec3b::rbegin() const noexcept {
    return data.rbegin();
}

/**
 * Reverse iterator to the end of the components
 */
auto vec3b::rend() const noexcept {
    return data.rend();
}

/**
 * Reverse iterator to the first component
 */
auto vec3b::crbegin() const noexcept {
    return data.crbegin();
}

/**
 * Reverse iterator to the end of the components
 */
auto vec3b::crend() const noexcept { 
    return data.crend();
}

#pragma endregion iteration

#pragma region overloads

/**
 * stream insertion operator
 */
std::ostream& operator <<(std::ostream& os, const vec3b& vec) {
    os << "[" << vec.x << ", " << vec.y << ", " << vec.z << "]";
    return os;
}

/**
 * Copy assignment operator
 */
vec3b& vec3b::operator =(const vec3b& other) {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}

/**
 * Component-wise and operator
 */
vec3b operator &&(const vec3b& a, const vec3b& b) {
    return vec3b(a.x && b.x, a.y && b.y, a.z && b.z);
}

/**
 * Component-wise and operator
 */
vec3b operator &&(const bool& a, const vec3b& b) {
    return vec3b(a && b.x, a && b.y, a && b.z);
}

/**
 * Component-wise and operator
 */
vec3b operator &&(const vec3b& a, const bool& b) {
    return vec3b(a.x && b, a.y && b, a.z && b);
}

/**
 * Component-wise or operator
 */
vec3b operator ||(const vec3b& a, const vec3b& b) {
    return vec3b(a.x || b.x, a.y || b.y, a.z || b.z);
}

/**
 * Component-wise or operator
 */
vec3b operator ||(const bool& a, const vec3b& b) {
    return vec3b(a || b.x, a || b.y, a || b.z);
}

/**
 * Component-wise or operator
 */
vec3b operator ||(const vec3b& a, const bool& b) {
    return vec3b(a.x || b, a.y || b, a.z || b);
}

/**
 * Component-wise not operator
 */
vec3b vec3b::operator !() const {
    return vec3b(!x, !y, !z);
}

/**
 * Component-wise equality operator
 */
vec3b operator ==(const vec3b& a, const vec3b& b) {
    return vec3b(a.x == b.x, a.y == b.y, a.z == b.z);
}

/**
 * Component-wise inequality operator
 */
vec3b operator !=(const vec3b& a, const vec3b& b) {
    return vec3b(a.x != b.x, a.y != b.y, a.z != b.z);
}

#pragma endregion overloads

#pragma region vector operations

/**
 * returns if any component is true
 */
bool vec3b::any() const {
    return x || y || z;
}

/**
 * returns if any component is true
 */
bool any(const vec3b& vec) {
    return vec.x || vec.y || vec.z;
}

/**
 * returns if all components are true
 */
bool vec3b::all() const {
    return x && y && z;
}

/**
 * returns if all components are true
 */
bool all(const vec3b& vec) {
    return vec.x && vec.y && vec.z;
}

/**
 * returns the number of true components
*/
unsigned int vec3b::count() const {
    return (unsigned int)x + (unsigned int)y + (unsigned int)z;
}

/**
 * returns the number of true components
*/
unsigned int count(const vec3b& vec) {
    return (unsigned int)vec.x + (unsigned int)vec.y + (unsigned int)vec.z;
}

#pragma endregion vector operations

}