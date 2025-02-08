#include "bvec4.hpp"
#include <cmath>
#include <stdexcept>


namespace Engine {

#pragma region constants


const bvec4 bvec4::zero = bvec4(false);

const bvec4 bvec4::one = bvec4(true);

#pragma endregion constants

#pragma region constructors


bvec4::bvec4() {
    x = false;
    y = false;
    z = false;
    w = false;
}

bvec4::bvec4(const bvec4& vec) {
    data = vec.data;
}

#pragma endregion constructors

#pragma region conversions


bvec4::operator bool() const {
    return x && y && z && w;
}


bvec4::bvec4(const vec4& vec){
    x = vec.x > 0.0f;
    y = vec.y > 0.0f;
    z = vec.z > 0.0f;
    w = vec.w > 0.0f;
}

#pragma endregion conversions

#pragma region accessors


bool& bvec4::operator [](unsigned int i){
    return data[i];
}


const bool& bvec4::operator [](unsigned int i) const {
    return data[i];
}

#pragma endregion accessors

#pragma region iteration


auto bvec4::begin() noexcept {
    return data.begin();
}


auto bvec4::end() noexcept {
    return data.end();
}


auto bvec4::begin() const noexcept {
    return data.begin();
}


auto bvec4::end() const noexcept {
    return data.end();
}


auto bvec4::cbegin() const noexcept {
    return data.cbegin();
}


auto bvec4::cend() const noexcept { 
    return data.cend();
}


auto bvec4::rbegin() noexcept {
    return data.rbegin();
}


auto bvec4::rend() noexcept {
    return data.rend();
}


auto bvec4::rbegin() const noexcept {
    return data.rbegin();
}


auto bvec4::rend() const noexcept {
    return data.rend();
}


auto bvec4::crbegin() const noexcept {
    return data.crbegin();
}


auto bvec4::crend() const noexcept { 
    return data.crend();
}

#pragma endregion iteration

#pragma region overloads


bvec4& bvec4::operator =(const bvec4& other) {
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
}


bvec4 operator &&(const bvec4& a, const bvec4& b) {
    return bvec4(a.x && b.x, a.y && b.y, a.z && b.z, a.w && b.w);
}


bvec4 operator &&(const bool& a, const bvec4& b) {
    return bvec4(a && b.x, a && b.y, a && b.z, a && b.w);
}


bvec4 operator &&(const bvec4& a, const bool& b) {
    return bvec4(a.x && b, a.y && b, a.z && b, a.w && b);
}


bvec4 operator ||(const bvec4& a, const bvec4& b) {
    return bvec4(a.x || b.x, a.y || b.y, a.z || b.z, a.w || b.w);
}


bvec4 operator ||(const bool& a, const bvec4& b) {
    return bvec4(a || b.x, a || b.y, a || b.z, a || b.w);
}


bvec4 operator ||(const bvec4& a, const bool& b) {
    return bvec4(a.x || b, a.y || b, a.z || b, a.w || b);
}


bvec4 bvec4::operator !() const {
    return bvec4(!x, !y, !z, !w);
}


bvec4 operator ==(const bvec4& a, const bvec4& b) {
    return bvec4(a.x == b.x, a.y == b.y, a.z == b.z, a.w == b.w);
}


bvec4 operator !=(const bvec4& a, const bvec4& b) {
    return bvec4(a.x != b.x, a.y != b.y, a.z != b.z, a.w != b.w);
}

#pragma endregion overloads

#pragma region vector operations


bool bvec4::any() const {
    return x || y || z || w;
}


bool bvec4::all() const {
    return x && y && z && w;
}

/**
 * returns the number of true components
*/
unsigned int bvec4::count() const {
    return (unsigned int)x + (unsigned int)y + (unsigned int)z + (unsigned int)w;
}


std::string to_string(const bvec4& vec) {
    return "[" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z) + ", " + std::to_string(vec.w) + "]";
}

#pragma endregion vector operations

}