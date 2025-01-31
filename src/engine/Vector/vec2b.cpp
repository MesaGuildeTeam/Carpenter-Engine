#include "vec2b.hpp"
#include <cmath>
#include <stdexcept>


namespace Engine {

#pragma region constants


const vec2b vec2b::zero = vec2b(false);

const vec2b vec2b::one = vec2b(true);

#pragma endregion constants

#pragma region constructors


vec2b::vec2b() {
    x = false;
    y = false;
}

#pragma endregion constructors

#pragma region conversions


vec2b::operator bool() const {
    return x && y;
}


vec2b::vec2b(const vec2& vec){
    x = vec.x > 0.0f;
    y = vec.y > 0.0f;
}

#pragma endregion conversions

#pragma region accessors


bool& vec2b::operator [](unsigned int i){
    return data[i];
}


const bool& vec2b::operator [](unsigned int i) const {
    return data[i];
}

#pragma endregion accessors

#pragma region iteration


auto vec2b::begin() noexcept {
    return data.begin();
}


auto vec2b::end() noexcept {
    return data.end();
}


auto vec2b::begin() const noexcept {
    return data.begin();
}


auto vec2b::end() const noexcept {
    return data.end();
}


auto vec2b::cbegin() const noexcept {
    return data.cbegin();
}


auto vec2b::cend() const noexcept { 
    return data.cend();
}


auto vec2b::rbegin() noexcept {
    return data.rbegin();
}


auto vec2b::rend() noexcept {
    return data.rend();
}


auto vec2b::rbegin() const noexcept {
    return data.rbegin();
}


auto vec2b::rend() const noexcept {
    return data.rend();
}


auto vec2b::crbegin() const noexcept {
    return data.crbegin();
}


auto vec2b::crend() const noexcept { 
    return data.crend();
}

#pragma endregion iteration

#pragma region overloads


vec2b& vec2b::operator =(const vec2b& other) {
    x = other.x;
    y = other.y;
    return *this;
}


vec2b operator &&(const vec2b& a, const vec2b& b) {
    return vec2b(a.x && b.x, a.y && b.y);
}


vec2b operator &&(const bool& a, const vec2b& b) {
    return vec2b(a && b.x, a && b.y);
}


vec2b operator &&(const vec2b& a, const bool& b) {
    return vec2b(a.x && b, a.y && b);
}


vec2b operator ||(const vec2b& a, const vec2b& b) {
    return vec2b(a.x || b.x, a.y || b.y);
}


vec2b operator ||(const bool& a, const vec2b& b) {
    return vec2b(a || b.x, a || b.y);
}


vec2b operator ||(const vec2b& a, const bool& b) {
    return vec2b(a.x || b, a.y || b);
}


vec2b vec2b::operator !() const {
    return vec2b(!x, !y);
}


vec2b operator ==(const vec2b& a, const vec2b& b) {
    return vec2b(a.x == b.x, a.y == b.y);
}


vec2b operator !=(const vec2b& a, const vec2b& b) {
    return vec2b(a.x != b.x, a.y != b.y);
}

#pragma endregion overloads

#pragma region vector operations


bool vec2b::any() const {
    return x || y;
}


bool vec2b::all() const {
    return x && y;
}


unsigned int vec2b::count() const {
    return (unsigned int)x + (unsigned int)y;
}


std::string to_string(const vec2b& vec) {
    return "[" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + "]";
}

#pragma endregion vector operations

}