#include "vec3b.hpp"
#include <cmath>
#include <stdexcept>


std::string std::to_string(const Engine::vec3b& vec) {
    return "[" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z) + "]";
}

namespace Engine {

#pragma region constants


const vec3b vec3b::zero = vec3b(false);

const vec3b vec3b::one = vec3b(true);

#pragma endregion constants

#pragma region constructors


vec3b::vec3b() {
    x = false;
    y = false;
    z = false;
}

#pragma endregion constructors

#pragma region conversions


vec3b::operator bool() const {
    return x && y && z;
}


vec3b::vec3b(const vec3& vec){
    x = vec.x > 0.0f;
    y = vec.y > 0.0f;
    z = vec.z > 0.0f;
}

#pragma endregion conversions

#pragma region accessors


bool& vec3b::operator [](unsigned int i){
    return data[i];
}


const bool& vec3b::operator [](unsigned int i) const {
    return data[i];
}

#pragma endregion accessors

#pragma region iteration


auto vec3b::begin() noexcept {
    return data.begin();
}


auto vec3b::end() noexcept {
    return data.end();
}


auto vec3b::begin() const noexcept {
    return data.begin();
}


auto vec3b::end() const noexcept {
    return data.end();
}


auto vec3b::cbegin() const noexcept {
    return data.cbegin();
}


auto vec3b::cend() const noexcept { 
    return data.cend();
}


auto vec3b::rbegin() noexcept {
    return data.rbegin();
}


auto vec3b::rend() noexcept {
    return data.rend();
}


auto vec3b::rbegin() const noexcept {
    return data.rbegin();
}


auto vec3b::rend() const noexcept {
    return data.rend();
}


auto vec3b::crbegin() const noexcept {
    return data.crbegin();
}


auto vec3b::crend() const noexcept { 
    return data.crend();
}

#pragma endregion iteration

#pragma region overloads


std::ostream& operator <<(std::ostream& os, const vec3b& vec) {
    os << "[" << vec.x << ", " << vec.y << ", " << vec.z << "]";
    return os;
}


vec3b& vec3b::operator =(const vec3b& other) {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}


vec3b operator &&(const vec3b& a, const vec3b& b) {
    return vec3b(a.x && b.x, a.y && b.y, a.z && b.z);
}


vec3b operator &&(const bool& a, const vec3b& b) {
    return vec3b(a && b.x, a && b.y, a && b.z);
}


vec3b operator &&(const vec3b& a, const bool& b) {
    return vec3b(a.x && b, a.y && b, a.z && b);
}


vec3b operator ||(const vec3b& a, const vec3b& b) {
    return vec3b(a.x || b.x, a.y || b.y, a.z || b.z);
}


vec3b operator ||(const bool& a, const vec3b& b) {
    return vec3b(a || b.x, a || b.y, a || b.z);
}


vec3b operator ||(const vec3b& a, const bool& b) {
    return vec3b(a.x || b, a.y || b, a.z || b);
}


vec3b vec3b::operator !() const {
    return vec3b(!x, !y, !z);
}


vec3b operator ==(const vec3b& a, const vec3b& b) {
    return vec3b(a.x == b.x, a.y == b.y, a.z == b.z);
}


vec3b operator !=(const vec3b& a, const vec3b& b) {
    return vec3b(a.x != b.x, a.y != b.y, a.z != b.z);
}

#pragma endregion overloads

#pragma region vector operations


bool vec3b::any() const {
    return x || y || z;
}


bool any(const vec3b& vec) {
    return vec.x || vec.y || vec.z;
}


bool vec3b::all() const {
    return x && y && z;
}


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