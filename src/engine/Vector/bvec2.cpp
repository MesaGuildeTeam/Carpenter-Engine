#include "bvec2.hpp"
#include <cmath>
#include <stdexcept>


namespace Engine {

#pragma region constants


const bvec2 bvec2::zero = bvec2(false);

const bvec2 bvec2::one = bvec2(true);

#pragma endregion constants

#pragma region constructors


bvec2::bvec2() {
    x = false;
    y = false;
}

bvec2::bvec2(const bvec2& vec) {
    data = vec.data;
}

#pragma endregion constructors

#pragma region conversions


bvec2::operator bool() const {
    return x && y;
}


bvec2::bvec2(const vec2& vec){
    x = vec.x > 0.0f;
    y = vec.y > 0.0f;
}

#pragma endregion conversions

#pragma region accessors


bool& bvec2::operator [](unsigned int i){
    return data[i];
}


const bool& bvec2::operator [](unsigned int i) const {
    return data[i];
}

#pragma endregion accessors

#pragma region iteration


bvec2::iterator bvec2::begin() noexcept {
    return data.begin();
}


bvec2::iterator bvec2::end() noexcept {
    return data.end();
}


bvec2::const_iterator bvec2::begin() const noexcept {
    return data.begin();
}


bvec2::const_iterator bvec2::end() const noexcept {
    return data.end();
}


bvec2::const_iterator bvec2::cbegin() const noexcept {
    return data.cbegin();
}


bvec2::const_iterator bvec2::cend() const noexcept {
    return data.cend();
}


bvec2::reverse_iterator bvec2::rbegin() noexcept {
    return data.rbegin();
}


bvec2::reverse_iterator bvec2::rend() noexcept {
    return data.rend();
}


bvec2::const_reverse_iterator bvec2::rbegin() const noexcept {
    return data.rbegin();
}


bvec2::const_reverse_iterator bvec2::rend() const noexcept {
    return data.rend();
}


bvec2::const_reverse_iterator bvec2::crbegin() const noexcept {
    return data.crbegin();
}


bvec2::const_reverse_iterator bvec2::crend() const noexcept {
    return data.crend();
}

#pragma endregion iteration

#pragma region overloads


bvec2& bvec2::operator =(const bvec2& other) {
    x = other.x;
    y = other.y;
    return *this;
}


bvec2 operator &&(const bvec2& a, const bvec2& b) {
    return bvec2(a.x && b.x, a.y && b.y);
}


bvec2 operator &&(const bool& a, const bvec2& b) {
    return bvec2(a && b.x, a && b.y);
}


bvec2 operator &&(const bvec2& a, const bool& b) {
    return bvec2(a.x && b, a.y && b);
}


bvec2 operator ||(const bvec2& a, const bvec2& b) {
    return bvec2(a.x || b.x, a.y || b.y);
}


bvec2 operator ||(const bool& a, const bvec2& b) {
    return bvec2(a || b.x, a || b.y);
}


bvec2 operator ||(const bvec2& a, const bool& b) {
    return bvec2(a.x || b, a.y || b);
}


bvec2 bvec2::operator !() const {
    return bvec2(!x, !y);
}


bvec2 operator ==(const bvec2& a, const bvec2& b) {
    return bvec2(a.x == b.x, a.y == b.y);
}


bvec2 operator !=(const bvec2& a, const bvec2& b) {
    return bvec2(a.x != b.x, a.y != b.y);
}

#pragma endregion overloads

#pragma region vector operations


bool bvec2::any() const {
    return x || y;
}


bool bvec2::all() const {
    return x && y;
}


unsigned int bvec2::count() const {
    return (unsigned int)x + (unsigned int)y;
}


std::string to_string(const bvec2& vec) {
    return "[" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + "]";
}

#pragma endregion vector operations

}