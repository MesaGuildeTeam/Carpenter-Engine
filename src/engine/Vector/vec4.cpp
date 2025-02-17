#include "vec4.hpp"
#include <cmath>
#include <stdexcept>


namespace Engine {

#pragma region constants


const vec4 vec4::zero = vec4(0);

const vec4 vec4::one = vec4(1);

const vec4 vec4::up = vec4(1,0,0,0);

const vec4 vec4::down = vec4(-1,0,0,0);

const vec4 vec4::left = vec4(0,1,0,0);

const vec4 vec4::right = vec4(0,-1,0,0);

const vec4 vec4::forward = vec4(0,0,1,0);

const vec4 vec4::back = vec4(0,0,-1,0);

const vec4 vec4::ana = vec4(0,0,0,1);

const vec4 vec4::kata = vec4(0,0,0,-1);

#pragma endregion constants

#pragma region constructors


vec4::vec4(){
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    w = 0.0f;
}

vec4::vec4(const vec4& vec) {
    data = vec.data;
}

#pragma endregion constructors

#pragma region conversions


vec4::operator bool() const {
    return x && y && z && w;
}


vec4::vec4(const bvec4& vec){
    x = vec.x;
    y = vec.y;
    z = vec.z;
    w = vec.w;
}

#pragma endregion conversions

#pragma region accessors


float& vec4::operator [](unsigned int i) {
    if (i >= 4) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}


const float& vec4::operator [](unsigned int i) const {
    if (i >= 4) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

#pragma endregion accessors

#pragma region iteration


vec4::iterator vec4::begin() noexcept {
    return data.begin();
}


vec4::iterator vec4::end() noexcept {
    return data.end();
}


vec4::const_iterator vec4::begin() const noexcept {
    return data.begin();
}


vec4::const_iterator vec4::end() const noexcept {
    return data.end();
}


vec4::const_iterator vec4::cbegin() const noexcept {
    return data.cbegin();
}


vec4::const_iterator vec4::cend() const noexcept {
    return data.cend();
}


vec4::reverse_iterator vec4::rbegin() noexcept {
    return data.rbegin();
}


vec4::reverse_iterator vec4::rend() noexcept {
    return data.rend();
}


vec4::const_reverse_iterator vec4::rbegin() const noexcept {
    return data.rbegin();
}


vec4::const_reverse_iterator vec4::rend() const noexcept {
    return data.rend();
}


vec4::const_reverse_iterator vec4::crbegin() const noexcept {
    return data.crbegin();
}


vec4::const_reverse_iterator vec4::crend() const noexcept {
    return data.crend();
}

#pragma endregion iteration

#pragma region overloads


vec4& vec4::operator =(const vec4& other) {
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
}


vec4 operator +(const vec4& a, const vec4& b) {
    return vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}


vec4 operator +(const float& a, const vec4& b) {
    return vec4(a + b.x, a + b.y, a + b.z, a + b.w);
}


vec4 operator +(const vec4& a, const float& b) {
    return vec4(a.x + b, a.y + b, a.z + b, a.w + b);
}


vec4 operator -(const vec4& a, const vec4& b) {
    return vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}


vec4 operator -(const float& a, const vec4& b) {
    return vec4(a - b.x, a - b.y, a - b.z, a - b.w);
}


vec4 operator -(const vec4& a, const float& b) {
    return vec4(a.x - b, a.y - b, a.z - b, a.w - b);
}


vec4 vec4::operator -() const {
    return vec4(-x, -y, -z, -w);
}


vec4 operator *(const vec4& a, const vec4& b) {
    return vec4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}


vec4 operator *(const float& a, const vec4& b) {
    return vec4(a * b.x, a * b.y, a * b.z, a * b.w);
}


vec4 operator *(const vec4& a, const float& b) {
    return vec4(a.x * b, a.y * b, a.z * b, a.w * b);
}


vec4 operator /(const vec4& a, const vec4& b) {
    return vec4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}


vec4 operator /(const float& a, const vec4& b) {
    return vec4(a / b.x, a / b.y, a / b.z, a / b.w);
}


vec4 operator /(const vec4& a, const float& b) {
    return vec4(a.x / b, a.y / b, a.z / b, a.w / b);
}


bvec4 vec4::operator ==(const vec4& other) const {
    return bvec4(x == other.x, y == other.y, z == other.z, w == other.w);
}


bvec4 vec4::operator !=(const vec4& other) const {
    return bvec4(x != other.x, y != other.y, z != other.z, w != other.w);
}


bvec4 vec4::operator <(const vec4& other) const {
    return bvec4(x < other.x, y < other.y, z < other.z, w < other.w);
}


bvec4 vec4::operator >(const vec4& other) const {
    return bvec4(x > other.x, y > other.y, z > other.z, w > other.w);
}


bvec4 vec4::operator <=(const vec4& other) const {
    return bvec4(x <= other.x, y <= other.y, z <= other.z, w <= other.w);
}


bvec4 vec4::operator >=(const vec4& other) const {
    return bvec4(x >= other.x, y >= other.y, z >= other.z, w >= other.w);   
}


vec4& vec4::operator +=(const vec4& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
}


vec4& vec4::operator +=(const float& other) {
    x += other;
    y += other;
    z += other;
    w += other;
    return *this;
}


vec4& vec4::operator -=(const vec4& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return *this;
}


vec4& vec4::operator -=(const float& other) {
    x -= other;
    y -= other;
    z -= other;
    w -= other;
    return *this;
}


vec4& vec4::operator *=(const vec4& other) {
    x *= other.x;
    y *= other.y;
    z *= other.z;
    w *= other.w;
    return *this;
}


vec4& vec4::operator *=(const float& other) {
    x *= other;
    y *= other;
    z *= other;
    w *= other;
    return *this;
}


vec4& vec4::operator /=(const vec4& other) {
    x /= other.x;
    y /= other.y;
    z /= other.z;
    w /= other.w;
    return *this;
}


vec4& vec4::operator /=(const float& other) {
    x /= other;
    y /= other;
    z /= other;
    w /= other;
    return *this;
}


vec4& vec4::operator ++() {
    x++;
    y++;
    z++;
    w++;
    return *this;
}


vec4& vec4::operator --() {
    x--;
    y--;
    z--;
    w--;
    return *this;
}

#pragma endregion overloads

#pragma region vector operations


vec4 vec4::normalized() const {
    return *this/length();
}


float vec4::lengthSquared() const {
    return dot(*this, *this);
}


float vec4::length() const {
    return sqrtf(lengthSquared());
}


float dot(const vec4& a, const vec4& b) {
    return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
}


double angleBetween(const vec4& a, const vec4& b) {
    return acos( dot(a,b) / sqrt(a.lengthSquared()*b.lengthSquared()) );
}


vec4 reflect(const vec4& I, const vec4& N) {
    return I - 2.0f*N*dot(N, I)/dot(N,N);
}


float distanceSquared(const vec4& a, const vec4& b) {
    return (b - a).lengthSquared();
}


float distance(const vec4& a, const vec4& b) {
    return (b - a).length();
}


std::string to_string(const vec4& vec) {
    return "[" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z) + ", " + std::to_string(vec.w) + "]";
}

#pragma endregion vector operations

}