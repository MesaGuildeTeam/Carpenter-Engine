#include "bvec3.hpp"
#include <cmath>
#include <stdexcept>


namespace Engine {

#pragma region constants


const bvec3 bvec3::zero = bvec3(false);

const bvec3 bvec3::one = bvec3(true);

#pragma endregion constants

#pragma region constructors


bvec3::bvec3() {
    x = false;
    y = false;
    z = false;
}


bvec3::bvec3(const bvec3& vec) {
    data = vec.data;
}

#pragma endregion constructors

#pragma region conversions


bvec3::operator bool() const {
    return x && y && z;
}


bvec3::bvec3(const vec3& vec){
    x = vec.x > 0.0f;
    y = vec.y > 0.0f;
    z = vec.z > 0.0f;
}

#pragma endregion conversions

#pragma region accessors


bool& bvec3::operator [](unsigned int i){
    return data[i];
}


const bool& bvec3::operator [](unsigned int i) const {
    return data[i];
}

#pragma endregion accessors

#pragma region iteration


auto bvec3::begin() noexcept {
    return data.begin();
}


auto bvec3::end() noexcept {
    return data.end();
}


auto bvec3::begin() const noexcept {
    return data.begin();
}


auto bvec3::end() const noexcept {
    return data.end();
}


auto bvec3::cbegin() const noexcept {
    return data.cbegin();
}


auto bvec3::cend() const noexcept { 
    return data.cend();
}


auto bvec3::rbegin() noexcept {
    return data.rbegin();
}


auto bvec3::rend() noexcept {
    return data.rend();
}


auto bvec3::rbegin() const noexcept {
    return data.rbegin();
}


auto bvec3::rend() const noexcept {
    return data.rend();
}


auto bvec3::crbegin() const noexcept {
    return data.crbegin();
}


auto bvec3::crend() const noexcept { 
    return data.crend();
}

#pragma endregion iteration

#pragma region overloads


bvec3& bvec3::operator =(const bvec3& other) {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}


bvec3 operator &&(const bvec3& a, const bvec3& b) {
    return bvec3(a.x && b.x, a.y && b.y, a.z && b.z);
}


bvec3 operator &&(const bool& a, const bvec3& b) {
    return bvec3(a && b.x, a && b.y, a && b.z);
}


bvec3 operator &&(const bvec3& a, const bool& b) {
    return bvec3(a.x && b, a.y && b, a.z && b);
}


bvec3 operator ||(const bvec3& a, const bvec3& b) {
    return bvec3(a.x || b.x, a.y || b.y, a.z || b.z);
}


bvec3 operator ||(const bool& a, const bvec3& b) {
    return bvec3(a || b.x, a || b.y, a || b.z);
}


bvec3 operator ||(const bvec3& a, const bool& b) {
    return bvec3(a.x || b, a.y || b, a.z || b);
}


bvec3 bvec3::operator !() const {
    return bvec3(!x, !y, !z);
}


bvec3 operator ==(const bvec3& a, const bvec3& b) {
    return bvec3(a.x == b.x, a.y == b.y, a.z == b.z);
}


bvec3 operator !=(const bvec3& a, const bvec3& b) {
    return bvec3(a.x != b.x, a.y != b.y, a.z != b.z);
}

#pragma endregion overloads

#pragma region vector operations


bool bvec3::any() const {
    return x || y || z;
}


bool bvec3::all() const {
    return x && y && z;
}


unsigned int bvec3::count() const {
    return (unsigned int)x + (unsigned int)y + (unsigned int)z;
}


std::string to_string(const bvec3& vec) {
    return "[" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z) + "]";
}

#pragma endregion vector operations

}