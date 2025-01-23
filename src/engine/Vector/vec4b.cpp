#include "vec4b.hpp"
#include <cmath>
#include <stdexcept>

/**
 * converts a vector to a string
 */
std::string std::to_string(const Engine::vec4b& vec) {
    return "[" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z) + ", " + std::to_string(vec.w) + "]";
}

namespace Engine {

#pragma region constants

/**
 * vector of all falses
 */
const vec4b vec4b::zero = vec4b(false);
/**
 * vector of all trues
 */
const vec4b vec4b::one = vec4b(true);

#pragma endregion constants

#pragma region constructors

/**
 * default constructor, fills the vector with false
 */
vec4b::vec4b() {
    x = false;
    y = false;
    z = false;
    w = false;
}

#pragma endregion constructors

#pragma region conversions

/**
 * casts a vector to a bool
 * true if all components are non-zero
 * to check if any components are non-zero, compare with vec4b::zero rather than casting
 */
vec4b::operator bool() const {
    return x && y && z && w;
}

/**
 * casts a float vector to a boolean vector
 */
vec4b::vec4b(const vec4& vec){
    x = vec.x > 0.0f;
    y = vec.y > 0.0f;
    z = vec.z > 0.0f;
    w = vec.w > 0.0f;
}

#pragma endregion conversions

#pragma region accessors

/**
 * Array accessor
 * Returns the component at index i, 0-indexed
 */
bool& vec4b::operator [](unsigned int i){
    return data[i];
}

/**
 * Array accessor
 * Returns the component at index i, 0-indexed
 */
const bool& vec4b::operator [](unsigned int i) const {
    return data[i];
}

#pragma endregion accessors

#pragma region iteration

/**
 * Iterator to the first component
 */
auto vec4b::begin() noexcept {
    return data.begin();
}

/**
 * Iterator to the end of the components
 */
auto vec4b::end() noexcept {
    return data.end();
}

/**
 * Iterator to the first component
 */
auto vec4b::begin() const noexcept {
    return data.begin();
}

/**
 * Iterator to the end of the components
 */
auto vec4b::end() const noexcept {
    return data.end();
}

/**
 * Iterator to the first component
 */
auto vec4b::cbegin() const noexcept {
    return data.cbegin();
}

/**
 * Iterator to the end of the components
 */
auto vec4b::cend() const noexcept { 
    return data.cend();
}

/**
 * Reverse iterator to the first component
 */
auto vec4b::rbegin() noexcept {
    return data.rbegin();
}

/**
 * Reverse iterator to the end of the components
 */
auto vec4b::rend() noexcept {
    return data.rend();
}

/**
 * Reverse iterator to the first component
 */
auto vec4b::rbegin() const noexcept {
    return data.rbegin();
}

/**
 * Reverse iterator to the end of the components
 */
auto vec4b::rend() const noexcept {
    return data.rend();
}

/**
 * Reverse iterator to the first component
 */
auto vec4b::crbegin() const noexcept {
    return data.crbegin();
}

/**
 * Reverse iterator to the end of the components
 */
auto vec4b::crend() const noexcept { 
    return data.crend();
}

#pragma endregion iteration

#pragma region overloads

/**
 * stream insertion operator
 */
std::ostream& operator <<(std::ostream& os, const vec4b& vec) {
    os << "[" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << "]";
    return os;
}

/**
 * Copy assignment operator
 */
vec4b& vec4b::operator =(const vec4b& other) {
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
}

/**
 * Component-wise and operator
 */
vec4b operator &&(const vec4b& a, const vec4b& b) {
    return vec4b(a.x && b.x, a.y && b.y, a.z && b.z, a.w && b.w);
}

/**
 * Component-wise and operator
 */
vec4b operator &&(const bool& a, const vec4b& b) {
    return vec4b(a && b.x, a && b.y, a && b.z, a && b.w);
}

/**
 * Component-wise and operator
 */
vec4b operator &&(const vec4b& a, const bool& b) {
    return vec4b(a.x && b, a.y && b, a.z && b, a.w && b);
}

/**
 * Component-wise or operator
 */
vec4b operator ||(const vec4b& a, const vec4b& b) {
    return vec4b(a.x || b.x, a.y || b.y, a.z || b.z, a.w || b.w);
}

/**
 * Component-wise or operator
 */
vec4b operator ||(const bool& a, const vec4b& b) {
    return vec4b(a || b.x, a || b.y, a || b.z, a || b.w);
}

/**
 * Component-wise or operator
 */
vec4b operator ||(const vec4b& a, const bool& b) {
    return vec4b(a.x || b, a.y || b, a.z || b, a.w || b);
}

/**
 * Component-wise not operator
 */
vec4b vec4b::operator !() const {
    return vec4b(!x, !y, !z, !w);
}

/**
 * Component-wise equality operator
 */
vec4b operator ==(const vec4b& a, const vec4b& b) {
    return vec4b(a.x == b.x, a.y == b.y, a.z == b.z, a.w == b.w);
}

/**
 * Component-wise inequality operator
 */
vec4b operator !=(const vec4b& a, const vec4b& b) {
    return vec4b(a.x != b.x, a.y != b.y, a.z != b.z, a.w != b.w);
}

#pragma endregion overloads

#pragma region vector operations

/**
 * returns if any component is true
 */
bool vec4b::any() const {
    return x || y || z || w;
}

/**
 * returns if any component is true
 */
bool any(const vec4b& vec) {
    return vec.x || vec.y || vec.z || vec.w;
}

/**
 * returns if all components are true
 */
bool vec4b::all() const {
    return x && y && z && w;
}

/**
 * returns if all components are true
 */
bool all(const vec4b& vec) {
    return vec.x && vec.y && vec.z && vec.w;
}

/**
 * returns the number of true components
*/
unsigned int vec4b::count() const {
    return (unsigned int)x + (unsigned int)y + (unsigned int)z + (unsigned int)w;
}

/**
 * returns the number of true components
*/
unsigned int count(const vec4b& vec) {
    return (unsigned int)vec.x + (unsigned int)vec.y + (unsigned int)vec.z + (unsigned int)vec.w;
}

#pragma endregion vector operations

}