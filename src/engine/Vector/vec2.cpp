#include "vec2.hpp"
#include <cmath>
#include <stdexcept>


namespace Engine {

#pragma region constants


const vec2 vec2::zero = vec2(0);

const vec2 vec2::one = vec2(1);

const vec2 vec2::right = vec2(1,0);

const vec2 vec2::left = vec2(-1,0);

const vec2 vec2::up = vec2(0,1);

const vec2 vec2::down = vec2(0,-1);

#pragma endregion constants

#pragma region constructors


vec2::vec2(){
    x = 0.0f;
    y = 0.0f;
}

#pragma endregion constructors

#pragma region conversions


vec2::operator bool() const {
    return x && y;
}


vec2::vec2(const bvec2& vec){
    x = vec.x;
    y = vec.y;
}

#pragma endregion conversions

#pragma region accessors


float& vec2::operator [](unsigned int i) {
    if (i >= 2) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}


const float& vec2::operator [](unsigned int i) const {
    if (i >= 2) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

#pragma endregion accessors

#pragma region iteration


auto vec2::begin() noexcept {
    return data.begin();
}


auto vec2::end() noexcept {
    return data.end();
}


auto vec2::begin() const noexcept {
    return data.begin();
}


auto vec2::end() const noexcept {
    return data.end();
}


auto vec2::cbegin() const noexcept {
    return data.cbegin();
}


auto vec2::cend() const noexcept {
    return data.cend();
}


auto vec2::rbegin() noexcept {
    return data.rbegin();
}


auto vec2::rend() noexcept {
    return data.rend();
}


auto vec2::rbegin() const noexcept {
    return data.rbegin();
}


auto vec2::rend() const noexcept {
    return data.rend();
}


auto vec2::crbegin() const noexcept {
    return data.crbegin();
}


auto vec2::crend() const noexcept {
    return data.crend();
}

#pragma endregion iteration

#pragma region overloads

vec2& vec2::operator =(const vec2& other) {
    x = other.x;
    y = other.y;
    return *this;
}


vec2 operator +(const vec2& a, const vec2& b) {
    return vec2(a.x + b.x, a.y + b.y);
}


vec2 operator +(const float& a, const vec2& b) {
    return vec2(a + b.x, a + b.y);
}


vec2 operator +(const vec2& a, const float& b) {
    return vec2(a.x + b, a.y + b);
}


vec2 operator -(const vec2& a, const vec2& b) {
    return vec2(a.x - b.x, a.y - b.y);
}


vec2 operator -(const float& a, const vec2& b) {
    return vec2(a - b.x, a - b.y);
}


vec2 operator -(const vec2& a, const float& b) {
    return vec2(a.x - b, a.y - b);
}


vec2 vec2::operator -() const {
    return vec2(-x, -y);
}


vec2 operator *(const vec2& a, const vec2& b) {
    return vec2(a.x * b.x, a.y * b.y);
}


vec2 operator *(const float& a, const vec2& b) {
    return vec2(a * b.x, a * b.y);
}


vec2 operator *(const vec2& a, const float& b) {
    return vec2(a.x * b, a.y * b);
}


vec2 operator /(const vec2& a, const vec2& b) {
    return vec2(a.x / b.x, a.y / b.y);
}


vec2 operator /(const float& a, const vec2& b) {
    return vec2(a / b.x, a / b.y);
}


vec2 operator /(const vec2& a, const float& b) {
    return vec2(a.x / b, a.y / b);
}


bvec2 vec2::operator ==(const vec2& other) const {
    return bvec2(x == other.x, y == other.y);
}


bvec2 vec2::operator !=(const vec2& other) const {
    return bvec2(x != other.x, y != other.y);
}


bvec2 vec2::operator <(const vec2& other) const {
    return bvec2(x < other.x, y < other.y);
}


bvec2 vec2::operator >(const vec2& other) const {
    return bvec2(x > other.x, y > other.y);
}


bvec2 vec2::operator <=(const vec2& other) const {
    return bvec2(x <= other.x, y <= other.y);
}


bvec2 vec2::operator >=(const vec2& other) const {
    return bvec2(x >= other.x, y >= other.y);
}


vec2 vec2::operator +=(const vec2& other) {
    x += other.x;
    y += other.y;
    return *this;
}


vec2 vec2::operator +=(const float& other) {
    x += other;
    y += other;
    return *this;
}


vec2 vec2::operator -=(const vec2& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}


vec2 vec2::operator -=(const float& other) {
    x -= other;
    y -= other;
    return *this;
}


vec2 vec2::operator *=(const vec2& other) {
    x *= other.x;
    y *= other.y;
    return *this;
}


vec2 vec2::operator *=(const float& other) {
    x *= other;
    y *= other;
    return *this;
}


vec2 vec2::operator /=(const vec2& other) {
    x /= other.x;
    y /= other.y;
    return *this;
}


vec2 vec2::operator /=(const float& other) {
    x /= other;
    y /= other;
    return *this;
}


vec2 vec2::operator ++() {
    x++;
    y++;
    return *this;
}


vec2 vec2::operator --() {
    x--;
    y--;
    return *this;
}

#pragma endregion overloads

#pragma region vector operations


vec2 vec2::normalized() const {
    return *this/length();
}


float vec2::lengthSquared() const {
    return dot(*this, *this);
}


float vec2::length() const {
    return sqrtf(lengthSquared());
}


vec2 vec2::tangent() const {
    return vec2(-y, x);
}


float dot(const vec2& a, const vec2& b) {
    return a.x*b.x + a.y*b.y;
}


double angleBetween(const vec2& a, const vec2& b) {
    return acos( dot(a,b) / sqrt(a.lengthSquared()*b.lengthSquared()) );
}


vec2 reflect(const vec2& I, const vec2& N) {
    return I - 2.0f*N*dot(N, I)/dot(N,N);
}


float distanceSquared(const vec2& a, const vec2& b) {
    return (b - a).lengthSquared();
}


float distance(const vec2& a, const vec2& b) {
    return (b - a).length();
}

std::string to_string(const vec2& vec) {
    return "[" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + "]";
}

#pragma endregion vector operations

}