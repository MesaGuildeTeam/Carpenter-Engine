#include "vec2b.hpp"
#include <cmath>
#include <stdexcept>

/**
 * converts a vector to a string
 */
std::string std::to_string(const Engine::vec2b& vec) {
    return "[" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + "]";
}

namespace Engine {

#pragma region constants

/**
 * vector of all falses
 */
const vec2b vec2b::zero = vec2b(false);
/**
 * vector of all trues
 */
const vec2b vec2b::one = vec2b(true);

#pragma endregion constants

#pragma region constructors

/**
 * default constructor, fills the vector with false
 */
vec2b::vec2b() {
    x = false;
    y = false;
}

#pragma endregion constructors

#pragma region conversions

/**
 * casts a vector to a bool
 * true if all components are non-zero
 * to check if any components are non-zero, compare with vec4b::zero rather than casting
 */
vec2b::operator bool() const {
    return x && y;
}

/**
 * casts a float vector to a boolean vector
 */
vec2b::vec2b(const vec2& vec){
    x = vec.x > 0.0f;
    y = vec.y > 0.0f;
}

#pragma endregion conversions

#pragma region accessors

/**
 * Array accessor
 * Returns the component at index i, 0-indexed
 */
bool& vec2b::operator [](unsigned int i){
    return data[i];
}

/**
 * Array accessor
 * Returns the component at index i, 0-indexed
 */
const bool& vec2b::operator [](unsigned int i) const {
    return data[i];
}

#pragma endregion accessors

#pragma region iteration

/**
 * Iterator to the first component
 */
auto vec2b::begin() noexcept {
    return data.begin();
}

/**
 * Iterator to the end of the components
 */
auto vec2b::end() noexcept {
    return data.end();
}

/**
 * Iterator to the first component
 */
auto vec2b::begin() const noexcept {
    return data.begin();
}

/**
 * Iterator to the end of the components
 */
auto vec2b::end() const noexcept {
    return data.end();
}

/**
 * Iterator to the first component
 */
auto vec2b::cbegin() const noexcept {
    return data.cbegin();
}

/**
 * Iterator to the end of the components
 */
auto vec2b::cend() const noexcept { 
    return data.cend();
}

/**
 * Reverse iterator to the first component
 */
auto vec2b::rbegin() noexcept {
    return data.rbegin();
}

/**
 * Reverse iterator to the end of the components
 */
auto vec2b::rend() noexcept {
    return data.rend();
}

/**
 * Reverse iterator to the first component
 */
auto vec2b::rbegin() const noexcept {
    return data.rbegin();
}

/**
 * Reverse iterator to the end of the components
 */
auto vec2b::rend() const noexcept {
    return data.rend();
}

/**
 * Reverse iterator to the first component
 */
auto vec2b::crbegin() const noexcept {
    return data.crbegin();
}

/**
 * Reverse iterator to the end of the components
 */
auto vec2b::crend() const noexcept { 
    return data.crend();
}

#pragma endregion iteration

#pragma region overloads

/**
 * stream insertion operator
 */
std::ostream& operator <<(std::ostream& os, const vec2b& vec) {
    os << "[" << vec.x << ", " << vec.y << "]";
    return os;
}

/**
 * Copy assignment operator
 */
vec2b& vec2b::operator =(const vec2b& other) {
    x = other.x;
    y = other.y;
    return *this;
}

/**
 * Component-wise and operator
 */
vec2b operator &&(const vec2b& a, const vec2b& b) {
    return vec2b(a.x && b.x, a.y && b.y);
}

/**
 * Component-wise and operator
 */
vec2b operator &&(const bool& a, const vec2b& b) {
    return vec2b(a && b.x, a && b.y);
}

/**
 * Component-wise and operator
 */
vec2b operator &&(const vec2b& a, const bool& b) {
    return vec2b(a.x && b, a.y && b);
}

/**
 * Component-wise or operator
 */
vec2b operator ||(const vec2b& a, const vec2b& b) {
    return vec2b(a.x || b.x, a.y || b.y);
}

/**
 * Component-wise or operator
 */
vec2b operator ||(const bool& a, const vec2b& b) {
    return vec2b(a || b.x, a || b.y);
}

/**
 * Component-wise or operator
 */
vec2b operator ||(const vec2b& a, const bool& b) {
    return vec2b(a.x || b, a.y || b);
}

/**
 * Component-wise not operator
 */
vec2b vec2b::operator !() const {
    return vec2b(!x, !y);
}

/**
 * Component-wise equality operator
 */
vec2b operator ==(const vec2b& a, const vec2b& b) {
    return vec2b(a.x == b.x, a.y == b.y);
}

/**
 * Component-wise inequality operator
 */
vec2b operator !=(const vec2b& a, const vec2b& b) {
    return vec2b(a.x != b.x, a.y != b.y);
}

#pragma endregion overloads

#pragma region vector operations

/**
 * returns if any component is true
 */
bool vec2b::any() const {
    return x || y;
}

/**
 * returns if any component is true
 */
bool any(const vec2b& vec) {
    return vec.x || vec.y;
}

/**
 * returns if all components are true
 */
bool vec2b::all() const {
    return x && y;
}

/**
 * returns if all components are true
 */
bool all(const vec2b& vec) {
    return vec.x && vec.y;
}

/**
 * returns the number of true components
*/
unsigned int vec2b::count() const {
    return (unsigned int)x + (unsigned int)y;
}

/**
 * returns the number of true components
*/
unsigned int count(const vec2b& vec) {
    return (unsigned int)vec.x + (unsigned int)vec.y;
}

#pragma endregion vector operations

}