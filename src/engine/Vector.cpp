#include "Vector.hpp"
#include <cmath>
#include <stdexcept>

#pragma region vec4

/**
 * converts a vector to a string
 */
std::string std::to_string(const Engine::vec4& vec) {
    return "[" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z) + ", " + std::to_string(vec.w) + "]";
}

namespace Engine {

#pragma region constants

/**
 * vector of all zeros
 */
const vec4 vec4::zero = vec4(0);
/**
 * vector of all ones
 */
const vec4 vec4::one = vec4(1);
/**
 * positive x unit vector
 */
const vec4 vec4::up = vec4(1,0,0,0);
/**
 * negative x unit vector
 */
const vec4 vec4::down = vec4(-1,0,0,0);
/**
 * positive y unit vector
 */
const vec4 vec4::left = vec4(0,1,0,0);
/**
 * negative y unit vector
 */
const vec4 vec4::right = vec4(0,-1,0,0);
/**
 * positive z unit vector
 */
const vec4 vec4::forward = vec4(0,0,1,0);
/**
 * negative z unit vector
 */
const vec4 vec4::back = vec4(0,0,-1,0);
/**
 * positive w unit vector
 */
const vec4 vec4::ana = vec4(0,0,0,1);
/**
 * negative w unit vector
 */
const vec4 vec4::kata = vec4(0,0,0,-1);

#pragma endregion constants

#pragma region constructors

/**
 * default constructor, fills the vector with 0
 */
vec4::vec4(){
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    w = 0.0f;
}

/**
 * fill constructor, fills the vector with the provided scalar value
 */
vec4::vec4(const float& a){
    x = a;
    y = a;
    z = a;
    w = a;
}

/**
 * concatenation constructor
 * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
 */
vec4::vec4(const vec4& a) {
    x = a.x;
    y = a.y;
    z = a.z;
    w = a.w;
}

/**
 * concatenation constructor
 * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
 */
vec4::vec4(const vec3& a, const float& b) {
    x = a.x;
    y = a.y;
    z = a.z;
    w = b;
}

/**
 * concatenation constructor
 * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
 */
vec4::vec4(const float& a, const vec3& b) {
    x = a;
    y = b.x;
    z = b.y;
    w = b.z;
}

/**
 * concatenation constructor
 * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
 */
vec4::vec4(const vec2& a, const vec2& b) {
    x = a.x;
    y = a.y;
    z = b.x;
    w = b.y;
}

/**
 * concatenation constructor
 * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
 */
vec4::vec4(const vec2& a, const float& b, const float& c) {
    x = a.x;
    y = a.y;
    z = b;
    w = c;
}

/**
 * concatenation constructor
 * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
 */
vec4::vec4(const float& a, const vec2& b, const float& c) {
    x = a;
    y = b.x;
    z = b.y;
    w = c;
}

/**
 * concatenation constructor
 * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
 */
vec4::vec4(const float& a, const float& b, const vec2& c) {
    x = a;
    y = b;
    z = c.x;
    w = c.y;
}

/**
 * concatenation constructor
 * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
 */
vec4::vec4(const float& a, const float& b, const float& c, const float& d) {
    x = a;
    y = b;
    z = c;
    w = d;
}

#pragma endregion constructors

#pragma region conversions

/**
 * casts a vector to a bool
 * true if all components are non-zero
 * to check if any components are non-zero, compare with vec4::zero rather than casting
 */
explicit vec4::operator bool() const {
    return x && y && z && w;
}

/**
 * casts a boolean vector to a float vector
 */
vec4::vec4(const bvec4& vec){
    x = vec.x;
    y = vec.y;
    z = vec.z;
    w = vec.w;
}

#pragma endregion conversions

#pragma region accessors

/**
 * Array accessor
 * Returns the component at index i, 0-indexed
 */
float& vec4::operator [](unsigned int i) {
    if (i >= 4) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

/**
 * Array accessor
 * Returns the component at index i, 0-indexed
 */
const float& vec4::operator [](unsigned int i) const {
    if (i >= 4) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

#pragma endregion accessors

#pragma region iteration

/**
 * iterator to the first component
 */
auto vec4::begin() noexcept {
    return data.begin();
}

/**
 * iterator to the end of the components
 */
auto vec4::end() noexcept {
    return data.end();
}

/**
 * iterator to the first component
 */
auto vec4::begin() const noexcept {
    return data.begin();
}

/**
 * iterator to the end of the components
 */
auto vec4::end() const noexcept {
    return data.end();
}

/**
 * iterator to the first component
 */
auto vec4::cbegin() const noexcept {
    return data.cbegin();
}

/**
 * iterator to the end of the components
 */
auto vec4::cend() const noexcept {
    return data.cend();
}

/**
 * reverse iterator to the first component
 */
auto vec4::rbegin() noexcept {
    return data.rbegin();
}

/**
 * reverse iterator to the end of the components
 */
auto vec4::rend() noexcept {
    return data.rend();
}

/**
 * reverse iterator to the first component
 */
auto vec4::rbegin() const noexcept {
    return data.rbegin();
}

/**
 * reverse iterator to the end of the components
 */
auto vec4::rend() const noexcept {
    return data.rend();
}

/**
 * reverse iterator to the first component
 */
auto vec4::crbegin() const noexcept {
    return data.crbegin();
}

/**
 * reverse iterator to the end of the components
 */
auto vec4::crend() const noexcept {
    return data.crend();
}

#pragma endregion iteration

#pragma region overloads

/**
 * stream insertion operator
 */
std::ostream& operator <<(std::ostream& os, const vec4& vec) {
    os << std::to_string(vec);
    return os;
}

/**
 * Copy assignment operator
 */
vec4& vec4::operator =(const vec4& other) {
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
}

/**
 * component-wise addition operator
 */
vec4 operator +(const vec4& a, const vec4& b) {
    return vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

/**
 * component-wise addition operator
 */
vec4 operator +(const float& a, const vec4& b) {
    return vec4(a + b.x, a + b.y, a + b.z, a + b.w);
}

/**
 * component-wise addition operator
 */
vec4 operator +(const vec4& a, const float& b) {
    return vec4(a.x + b, a.y + b, a.z + b, a.w + b);
}

/**
 * component-wise subtraction operator
 */
vec4 operator -(const vec4& a, const vec4& b) {
    return vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

/**
 * component-wise subtraction operator
 */
vec4 operator -(const float& a, const vec4& b) {
    return vec4(a - b.x, a - b.y, a - b.z, a - b.w);
}

/**
 * component-wise subtraction operator
 */
vec4 operator -(const vec4& a, const float& b) {
    return vec4(a.x - b, a.y - b, a.z - b, a.w - b);
}

/**
 * component-wise negation operator
 */
vec4 vec4::operator -() const {
    return vec4(-x, -y, -z, -w);
}

/**
 * component-wise multiplication operator
 */
vec4 operator *(const vec4& a, const vec4& b) {
    return vec4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

/**
 * component-wise multiplication operator
 */
vec4 operator *(const float& a, const vec4& b) {
    return vec4(a * b.x, a * b.y, a * b.z, a * b.w);
}

/**
 * component-wise multiplication operator
 */
vec4 operator *(const vec4& a, const float& b) {
    return vec4(a.x * b, a.y * b, a.z * b, a.w * b);
}

/**
 * component-wise division operator
 */
vec4 operator /(const vec4& a, const vec4& b) {
    return vec4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}

/**
 * component-wise division operator
 */
vec4 operator /(const float& a, const vec4& b) {
    return vec4(a / b.x, a / b.y, a / b.z, a / b.w);
}

/**
 * component-wise division operator
 */
vec4 operator /(const vec4& a, const float& b) {
    return vec4(a.x / b, a.y / b, a.z / b, a.w / b);
}

/**
 * component-wise equality operator
 */
bvec4 vec4::operator ==(const vec4& other) const {
    return bvec4(x == other.x, y == other.y, z == other.z, w == other.w);
}

/**
 * component-wise inequality operator
 */
bvec4 vec4::operator !=(const vec4& other) const {
    return bvec4(x != other.x, y != other.y, z != other.z, w != other.w);
}

/**
 * component-wise less than operator
 */
bvec4 vec4::operator <(const vec4& other) const {
    return bvec4(x < other.x, y < other.y, z < other.z, w < other.w);
}

/**
 * component-wise greater than operator
 */
bvec4 vec4::operator >(const vec4& other) const {
    return bvec4(x > other.x, y > other.y, z > other.z, w > other.w);
}

/**
 * component-wise less than or equal to operator
 */
bvec4 vec4::operator <=(const vec4& other) const {
    return bvec4(x <= other.x, y <= other.y, z <= other.z, w <= other.w);
}

/**
 * component-wise greater than or equal to operator
 */
bvec4 vec4::operator >=(const vec4& other) const {
    return bvec4(x >= other.x, y >= other.y, z >= other.z, w >= other.w);   
}

/**
 * component-wise addition assignment operator
 */
vec4 vec4::operator +=(const vec4& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
}

/**
 * component-wise addition assignment operator
 */
vec4 vec4::operator +=(const float& other) {
    x += other;
    y += other;
    z += other;
    w += other;
    return *this;
}

/**
 * component-wise subtraction assignment operator
 */
vec4 vec4::operator -=(const vec4& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return *this;
}

/**
 * component-wise subtraction assignment operator
 */
vec4 vec4::operator -=(const float& other) {
    x -= other;
    y -= other;
    z -= other;
    w -= other;
    return *this;
}

/**
 * component-wise multiplication assignment operator
 */
vec4 vec4::operator *=(const vec4& other) {
    x *= other.x;
    y *= other.y;
    z *= other.z;
    w *= other.w;
    return *this;
}

/**
 * component-wise multiplication assignment operator
 */
vec4 vec4::operator *=(const float& other) {
    x *= other;
    y *= other;
    z *= other;
    w *= other;
    return *this;
}

/**
 * component-wise division assignment operator
 */
vec4 vec4::operator /=(const vec4& other) {
    x /= other.x;
    y /= other.y;
    z /= other.z;
    w /= other.w;
    return *this;
}

/**
 * component-wise division assignment operator
 */
vec4 vec4::operator /=(const float& other) {
    x /= other;
    y /= other;
    z /= other;
    w /= other;
    return *this;
}

/**
 * component-wise increment operator
 */
vec4 vec4::operator ++() {
    x++;
    y++;
    z++;
    w++;
    return *this;
}

/**
 * component-wise decrement operator
 */
vec4 vec4::operator --() {
    x--;
    y--;
    z--;
    w--;
    return *this;
}

#pragma endregion overloads

#pragma region vector operations

/**
 * dot product of two vectors
 */
float vec4::dot(const vec4& a, const vec4& b) {
    return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
}

/**
 * angle between two vectors
 */
double vec4::angleBetween(const vec4& a, const vec4& b) {
    return acos( dot(a,b) / sqrt(a.lengthSquared()*b.lengthSquared()) );
}

/**
 * reflects incident vector, I, over normal, N
 * see https://registry.khronos.org/OpenGL-Refpages/gl4/html/reflect.xhtml
 */
vec4 vec4::reflect(const vec4& I, const vec4& N) {
    return I - 2.0*dot(N, I)*N;
}

/**
 * returns a vector in the same direction as the input vector, but with a length of 1
 */
vec4 vec4::normalize(const vec4& vec) {
    return vec/vec.length();
}

/**
 * returns a vector in the same direction as this vector, but with a length of 1
 */
vec4 vec4::normalized() const {
    return *this/length();
}

/**
 * returns the squared distance between two vectors
 */
float vec4::distanceSquared(const vec4& a, const vec4& b) {
    return (b - a).lengthSquared();
}

/**
 * returns the distance between two vectors
 */
float vec4::distance(const vec4& a, const vec4& b) {
    return (b - a).length();
}

/**
 * Returns the length squared of the vector
 * equivalent to dot product with itself
 */
float vec4::lengthSquared() const {
    return dot(*this, *this);
}

/**
 * Returns the length squared of the vector
 * equivalent to dot product with itself
 */
float vec4::lengthSquared(const vec4& a) {
    return dot(a, a);
}

/**
 * Returns the length of the vector
 */
float vec4::length() const {
    return sqrtf(lengthSquared());
}

/**
 * Returns the length of the vector
 */
float vec4::length(const vec4& a) {
    return sqrtf(a.lengthSquared());
}

#pragma endregion vector operations

}

#pragma endregion vec4


#pragma region vec3

/**
 * converts a vector to a string
 */
std::string std::to_string(const Engine::vec3& vec) {
    return "[" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z) + "]";
}

namespace Engine {

#pragma region constants

/**
 * vector of all zeros
 */
const vec3 vec3::zero = vec3(0);
/**
 * vector of all ones
 */
const vec3 vec3::one = vec3(1);
/**
 * positive x unit vector
 */
const vec3 vec3::right = vec3(1,0,0);
/**
 * negative x unit vector
 */
const vec3 vec3::left = vec3(-1,0,0);
/**
 * positive y unit vector
 */
const vec3 vec3::up = vec3(0,1,0);
/**
 * negative y unit vector
 */
const vec3 vec3::down = vec3(0,-1,0);
/**
 * positive z unit vector
 */
const vec3 vec3::forward = vec3(0,0,1);
/**
 * negative z unit vector
 */
const vec3 vec3::back = vec3(0,0,-1);

#pragma endregion constants

#pragma region constructors

/**
 * default constructor, fills the vector with 0
 */
vec3::vec3(){
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

/**
 * fill constructor, fills the vector with the provided scalar value
 */
vec3::vec3(const float& a){
    x = a;
    y = a;
    z = a;
}

/**
 * concatenation constructor
 * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
 */
vec3::vec3(const vec3& a) {
    x = a.x;
    y = a.y;
    z = a.z;
}

/**
 * concatenation constructor
 * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
 */
vec3::vec3(const vec2& a, const float& b) {
    x = a.x;
    y = a.y;
    z = b;
}

/**
 * concatenation constructor
 * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
 */
vec3::vec3(const float& a, const vec2& b) {
    x = a;
    y = b.x;
    z = b.y;
}

/**
 * concatenation constructor
 * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
 */
vec3::vec3(const float& a, const float& b, const float& c) {
    x = a;
    y = b;
    z = c;
}

#pragma endregion constructors

#pragma region conversions

/**
 * casts a vector to a bool
 * true if all components are non-zero
 * to check if any components are non-zero, compare with vec3::zero rather than casting
 */
explicit vec3::operator bool() const {
    return x && y && z;
}

/**
 * casts a boolean vector to a float vector
 */
vec3::vec3(const bvec3& vec){
    x = vec.x;
    y = vec.y;
    z = vec.z;
}

#pragma endregion conversions

#pragma region accessors

/**
 * Array accessor
 * Returns the component at index i, 0-indexed
 */
float& vec3::operator [](unsigned int i) {
    if (i >= 3) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

/**
 * Array accessor
 * Returns the component at index i, 0-indexed
 */
const float& vec3::operator [](unsigned int i) const {
    if (i >= 3) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

#pragma endregion accessors

#pragma region iteration

/**
 * iterator to the first component
 */
auto vec3::begin() noexcept {
    return data.begin();
}

/**
 * iterator to the end of the components
 */
auto vec3::end() noexcept {
    return data.end();
}

/**
 * iterator to the first component
 */
auto vec3::begin() const noexcept {
    return data.begin();
}

/**
 * iterator to the end of the components
 */
auto vec3::end() const noexcept {
    return data.end();
}

/**
 * iterator to the first component
 */
auto vec3::cbegin() const noexcept {
    return data.cbegin();
}

/**
 * iterator to the end of the components
 */
auto vec3::cend() const noexcept {
    return data.cend();
}

/**
 * reverse iterator to the first component
 */
auto vec3::rbegin() noexcept {
    return data.rbegin();
}

/**
 * reverse iterator to the end of the components
 */
auto vec3::rend() noexcept {
    return data.rend();
}

/**
 * reverse iterator to the first component
 */
auto vec3::rbegin() const noexcept {
    return data.rbegin();
}

/**
 * reverse iterator to the end of the components
 */
auto vec3::rend() const noexcept {
    return data.rend();
}

/**
 * reverse iterator to the first component
 */
auto vec3::crbegin() const noexcept {
    return data.crbegin();
}

/**
 * reverse iterator to the end of the components
 */
auto vec3::crend() const noexcept {
    return data.crend();
}

#pragma endregion iteration

#pragma region overloads

/**
 * stream insertion operator
 */
std::ostream& operator <<(std::ostream& os, const vec3& vec) {
    os << std::to_string(vec);
    return os;
}

/**
 * Copy assignment operator
 */
vec3& vec3::operator =(const vec3& other) {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}

/**
 * component-wise addition operator
 */
vec3 operator +(const vec3& a, const vec3& b) {
    return vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

/**
 * component-wise addition operator
 */
vec3 operator +(const float& a, const vec3& b) {
    return vec3(a + b.x, a + b.y, a + b.z);
}

/**
 * component-wise addition operator
 */
vec3 operator +(const vec3& a, const float& b) {
    return vec3(a.x + b, a.y + b, a.z + b);
}

/**
 * component-wise subtraction operator
 */
vec3 operator -(const vec3& a, const vec3& b) {
    return vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

/**
 * component-wise subtraction operator
 */
vec3 operator -(const float& a, const vec3& b) {
    return vec3(a - b.x, a - b.y, a - b.z);
}

/**
 * component-wise subtraction operator
 */
vec3 operator -(const vec3& a, const float& b) {
    return vec3(a.x - b, a.y - b, a.z - b);
}

/**
 * component-wise negation operator
 */
vec3 vec3::operator -() const {
    return vec3(-x, -y, -z);
}

/**
 * component-wise multiplication operator
 */
vec3 operator *(const vec3& a, const vec3& b) {
    return vec3(a.x * b.x, a.y * b.y, a.z * b.z);
}

/**
 * component-wise multiplication operator
 */
vec3 operator *(const float& a, const vec3& b) {
    return vec3(a * b.x, a * b.y, a * b.z);
}

/**
 * component-wise multiplication operator
 */
vec3 operator *(const vec3& a, const float& b) {
    return vec3(a.x * b, a.y * b, a.z * b);
}

/**
 * component-wise division operator
 */
vec3 operator /(const vec3& a, const vec3& b) {
    return vec3(a.x / b.x, a.y / b.y, a.z / b.z);
}

/**
 * component-wise division operator
 */
vec3 operator /(const float& a, const vec3& b) {
    return vec3(a / b.x, a / b.y, a / b.z);
}

/**
 * component-wise division operator
 */
vec3 operator /(const vec3& a, const float& b) {
    return vec3(a.x / b, a.y / b, a.z / b);
}

/**
 * component-wise equality operator
 */
bvec3 vec3::operator ==(const vec3& other) const {
    return bvec3(x == other.x, y == other.y, z == other.z);
}

/**
 * component-wise inequality operator
 */
bvec3 vec3::operator !=(const vec3& other) const {
    return bvec3(x != other.x, y != other.y, z != other.z);
}

/**
 * component-wise less than operator
 */
bvec3 vec3::operator <(const vec3& other) const {
    return bvec3(x < other.x, y < other.y, z < other.z);
}

/**
 * component-wise greater than operator
 */
bvec3 vec3::operator >(const vec3& other) const {
    return bvec3(x > other.x, y > other.y, z > other.z);
}

/**
 * component-wise less than or equal to operator
 */
bvec3 vec3::operator <=(const vec3& other) const {
    return bvec3(x <= other.x, y <= other.y, z <= other.z);
}

/**
 * component-wise greater than or equal to operator
 */
bvec3 vec3::operator >=(const vec3& other) const {
    return bvec3(x >= other.x, y >= other.y, z >= other.z);
}

/**
 * component-wise addition assignment operator
 */
vec3 vec3::operator +=(const vec3& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

/**
 * component-wise addition assignment operator
 */
vec3 vec3::operator +=(const float& other) {
    x += other;
    y += other;
    z += other;
    return *this;
}

/**
 * component-wise subtraction assignment operator
 */
vec3 vec3::operator -=(const vec3& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

/**
 * component-wise subtraction assignment operator
 */
vec3 vec3::operator -=(const float& other) {
    x -= other;
    y -= other;
    z -= other;
    return *this;
}

/**
 * component-wise multiplication assignment operator
 */
vec3 vec3::operator *=(const vec3& other) {
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
}

/**
 * component-wise multiplication assignment operator
 */
vec3 vec3::operator *=(const float& other) {
    x *= other;
    y *= other;
    z *= other;
    return *this;
}

/**
 * component-wise division assignment operator
 */
vec3 vec3::operator /=(const vec3& other) {
    x /= other.x;
    y /= other.y;
    z /= other.z;
    return *this;
}

/**
 * component-wise division assignment operator
 */
vec3 vec3::operator /=(const float& other) {
    x /= other;
    y /= other;
    z /= other;
    return *this;
}

/**
 * component-wise increment operator
 */
vec3 vec3::operator ++() {
    x++;
    y++;
    z++;
    return *this;
}

/**
 * component-wise decrement operator
 */
vec3 vec3::operator --() {
    x--;
    y--;
    z--;
    return *this;
}

#pragma endregion overloads

#pragma region vector operations

/**
 * dot product of two vectors
 */
float vec3::dot(const vec3& a, const vec3& b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

/**
 * cross product of two vectors
 */
vec3 vec3::cross(const vec3& a, const vec3& b) {
    return vec3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}

/**
 * angle between two vectors
 */
double vec3::angleBetween(const vec3& a, const vec3& b) {
    return acos( dot(a,b) / sqrt(a.lengthSquared()*b.lengthSquared()) );
}

/**
 * reflects incident vector, I, over normal, N
 * see https://registry.khronos.org/OpenGL-Refpages/gl4/html/reflect.xhtml
 */
vec3 vec3::reflect(const vec3& I, const vec3& N) {
    return I - 2.0*dot(N, I)*N;
}

/**
 * returns a vector in the same direction as the input vector, but with a length of 1
 */
vec3 vec3::normalize(const vec3& vec) {
    return vec/vec.length();
}

/**
 * returns a vector in the same direction as this vector, but with a length of 1
 */
vec3 vec3::normalized() const {
    return *this/length();
}

/**
 * returns the squared distance between two vectors
 */
float vec3::distanceSquared(const vec3& a, const vec3& b) {
    return (b - a).lengthSquared();
}

/**
 * returns the distance between two vectors
 */
float vec3::distance(const vec3& a, const vec3& b) {
    return (b - a).length();
}

/**
 * Returns the length squared of the vector
 * equivalent to dot product with itself
 */
float vec3::lengthSquared() const {
    return dot(*this, *this);
}

/**
 * Returns the length squared of the vector
 * equivalent to dot product with itself
 */
float vec3::lengthSquared(const vec3& a) {
    return dot(a, a);
}

/**
 * Returns the length of the vector
 */
float vec3::length() const {
    return sqrtf(lengthSquared());
}

/**
 * Returns the length of the vector
 */
float vec3::length(const vec3& a) {
    return sqrtf(a.lengthSquared());
}

/**
 * Returns a tangent vector of the same length to the current vector
 * the expression used is (-y,x,0) if |x| <= |z|, else (0,-z,y)
 */
vec3 vec3::tangent() const {
    if (fabs(x) <= fabs(z)) {
        return vec3(-y, x, 0);
    } else {
        return vec3(0, -z, y);
    }
}

/**
 * Returns a tangent vector of the same length to the current vector
 * the expression used is (-y,x,0) if |x| <= |z|, else (0,-z,y)
 */
vec3 vec3::tangent(const vec3& vec) {
    if (fabs(vec.x) <= fabs(vec.z)) {
        return vec3(-vec.y, vec.x, 0);
    } else {
        return vec3(0, -vec.z, vec.y);
    }
}

#pragma endregion vector operations

}

#pragma endregion vec3


#pragma region vec2

/**
 * converts a vector to a string
 */
std::string std::to_string(const Engine::vec2& vec) {
    return "[" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + "]";
}

namespace Engine {

#pragma region constants

/**
 * vector of all zeros
 */
const vec2 vec2::zero = vec2(0);
/**
 * vector of all ones
 */
const vec2 vec2::one = vec2(1);
/**
 * positive x unit vector
 */
const vec2 vec2::right = vec2(1,0);
/**
 * negative x unit vector
 */
const vec2 vec2::left = vec2(-1,0);
/**
 * positive y unit vector
 */
const vec2 vec2::up = vec2(0,1);
/**
 * negative y unit vector
 */
const vec2 vec2::down = vec2(0,-1);

#pragma endregion constants

#pragma region constructors

/**
 * default constructor, fills the vector with 0
 */
vec2::vec2(){
    x = 0.0f;
    y = 0.0f;
}

/**
 * fill constructor, fills the vector with the provided scalar value
 */
vec2::vec2(const float& a){
    x = a;
    y = a;
}

/**
 * concatenation constructor
 * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
 */
vec2::vec2(const vec2& a) {
    x = a.x;
    y = a.y;
}

/**
 * concatenation constructor
 * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
 */
vec2::vec2(const float& a, const float& b) {
    x = a;
    y = b;
}

#pragma endregion constructors

#pragma region conversions

/**
 * casts a vector to a bool
 * true if all components are non-zero
 * to check if any components are non-zero, compare with vec2::zero rather than casting
 */
explicit vec2::operator bool() const {
    return x && y;
}

/**
 * casts a boolean vector to a float vector
 */
vec2::vec2(const bvec2& vec){
    x = vec.x;
    y = vec.y;
}

#pragma endregion conversions

#pragma region accessors

/**
 * Array accessor
 * Returns the component at index i, 0-indexed
 */
float& vec2::operator [](unsigned int i) {
    if (i >= 2) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

/**
 * Array accessor
 * Returns the component at index i, 0-indexed
 */
const float& vec2::operator [](unsigned int i) const {
    if (i >= 2) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

#pragma endregion accessors

#pragma region iteration

/**
 * iterator to the first component
 */
auto vec2::begin() noexcept {
    return data.begin();
}

/**
 * iterator to the end of the components
 */
auto vec2::end() noexcept {
    return data.end();
}

/**
 * iterator to the first component
 */
auto vec2::begin() const noexcept {
    return data.begin();
}

/**
 * iterator to the end of the components
 */
auto vec2::end() const noexcept {
    return data.end();
}

/**
 * iterator to the first component
 */
auto vec2::cbegin() const noexcept {
    return data.cbegin();
}

/**
 * iterator to the end of the components
 */
auto vec2::cend() const noexcept {
    return data.cend();
}

/**
 * reverse iterator to the first component
 */
auto vec2::rbegin() noexcept {
    return data.rbegin();
}

/**
 * reverse iterator to the end of the components
 */
auto vec2::rend() noexcept {
    return data.rend();
}

/**
 * reverse iterator to the first component
 */
auto vec2::rbegin() const noexcept {
    return data.rbegin();
}

/**
 * reverse iterator to the end of the components
 */
auto vec2::rend() const noexcept {
    return data.rend();
}

/**
 * reverse iterator to the first component
 */
auto vec2::crbegin() const noexcept {
    return data.crbegin();
}

/**
 * reverse iterator to the end of the components
 */
auto vec2::crend() const noexcept {
    return data.crend();
}

#pragma endregion iteration

#pragma region overloads

/**
 * stream insertion operator
 */
std::ostream& operator <<(std::ostream& os, const vec2& vec) {
    os << std::to_string(vec);
    return os;
}

/**
 * Copy assignment operator
 */
vec2& vec2::operator =(const vec2& other) {
    x = other.x;
    y = other.y;
    return *this;
}

/**
 * component-wise addition operator
 */
vec2 operator +(const vec2& a, const vec2& b) {
    return vec2(a.x + b.x, a.y + b.y);
}

/**
 * component-wise addition operator
 */
vec2 operator +(const float& a, const vec2& b) {
    return vec2(a + b.x, a + b.y);
}

/**
 * component-wise addition operator
 */
vec2 operator +(const vec2& a, const float& b) {
    return vec2(a.x + b, a.y + b);
}

/**
 * component-wise subtraction operator
 */
vec2 operator -(const vec2& a, const vec2& b) {
    return vec2(a.x - b.x, a.y - b.y);
}

/**
 * component-wise subtraction operator
 */
vec2 operator -(const float& a, const vec2& b) {
    return vec2(a - b.x, a - b.y);
}

/**
 * component-wise subtraction operator
 */
vec2 operator -(const vec2& a, const float& b) {
    return vec2(a.x - b, a.y - b);
}

/**
 * component-wise negation operator
 */
vec2 vec2::operator -() const {
    return vec2(-x, -y);
}

/**
 * component-wise multiplication operator
 */
vec2 operator *(const vec2& a, const vec2& b) {
    return vec2(a.x * b.x, a.y * b.y);
}

/**
 * component-wise multiplication operator
 */
vec2 operator *(const float& a, const vec2& b) {
    return vec2(a * b.x, a * b.y);
}

/**
 * component-wise multiplication operator
 */
vec2 operator *(const vec2& a, const float& b) {
    return vec2(a.x * b, a.y * b);
}

/**
 * component-wise division operator
 */
vec2 operator /(const vec2& a, const vec2& b) {
    return vec2(a.x / b.x, a.y / b.y);
}

/**
 * component-wise division operator
 */
vec2 operator /(const float& a, const vec2& b) {
    return vec2(a / b.x, a / b.y);
}

/**
 * component-wise division operator
 */
vec2 operator /(const vec2& a, const float& b) {
    return vec2(a.x / b, a.y / b);
}

/**
 * component-wise equality operator
 */
bvec2 vec2::operator ==(const vec2& other) const {
    return bvec2(x == other.x, y == other.y);
}

/**
 * component-wise inequality operator
 */
bvec2 vec2::operator !=(const vec2& other) const {
    return bvec2(x != other.x, y != other.y);
}

/**
 * component-wise less than operator
 */
bvec2 vec2::operator <(const vec2& other) const {
    return bvec2(x < other.x, y < other.y);
}

/**
 * component-wise greater than operator
 */
bvec2 vec2::operator >(const vec2& other) const {
    return bvec2(x > other.x, y > other.y);
}

/**
 * component-wise less than or equal to operator
 */
bvec2 vec2::operator <=(const vec2& other) const {
    return bvec2(x <= other.x, y <= other.y);
}

/**
 * component-wise greater than or equal to operator
 */
bvec2 vec2::operator >=(const vec2& other) const {
    return bvec2(x >= other.x, y >= other.y);
}

/**
 * component-wise addition assignment operator
 */
vec2 vec2::operator +=(const vec2& other) {
    x += other.x;
    y += other.y;
    return *this;
}

/**
 * component-wise addition assignment operator
 */
vec2 vec2::operator +=(const float& other) {
    x += other;
    y += other;
    return *this;
}

/**
 * component-wise subtraction assignment operator
 */
vec2 vec2::operator -=(const vec2& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

/**
 * component-wise subtraction assignment operator
 */
vec2 vec2::operator -=(const float& other) {
    x -= other;
    y -= other;
    return *this;
}

/**
 * component-wise multiplication assignment operator
 */
vec2 vec2::operator *=(const vec2& other) {
    x *= other.x;
    y *= other.y;
    return *this;
}

/**
 * component-wise multiplication assignment operator
 */
vec2 vec2::operator *=(const float& other) {
    x *= other;
    y *= other;
    return *this;
}

/**
 * component-wise division assignment operator
 */
vec2 vec2::operator /=(const vec2& other) {
    x /= other.x;
    y /= other.y;
    return *this;
}

/**
 * component-wise division assignment operator
 */
vec2 vec2::operator /=(const float& other) {
    x /= other;
    y /= other;
    return *this;
}

/**
 * component-wise increment operator
 */
vec2 vec2::operator ++() {
    x++;
    y++;
    return *this;
}

/**
 * component-wise decrement operator
 */
vec2 vec2::operator --() {
    x--;
    y--;
    return *this;
}

#pragma endregion overloads

#pragma region vector operations

/**
 * dot product of two vectors
 */
float vec2::dot(const vec2& a, const vec2& b) {
    return a.x*b.x + a.y*b.y;
}

/**
 * cross product of two vectors
 * returns the determinant of the 2x2 matrix formed by the vectors
 */
static float cross(const vec2& a, const vec2& b){
    return a.x*b.y - a.y*b.x;
}

/**
 * angle between two vectors
 */
double vec2::angleBetween(const vec2& a, const vec2& b) {
    return acos( dot(a,b) / sqrt(a.lengthSquared()*b.lengthSquared()) );
}

/**
 * reflects incident vector, I, over normal, N
 * see https://registry.khronos.org/OpenGL-Refpages/gl4/html/reflect.xhtml
 */
vec2 vec2::reflect(const vec2& I, const vec2& N) {
    return I - 2.0*dot(N, I)*N;
}

/**
 * returns a vector in the same direction as the input vector, but with a length of 1
 */
vec2 vec2::normalize(const vec2& vec) {
    return vec/vec.length();
}

/**
 * returns a vector in the same direction as this vector, but with a length of 1
 */
vec2 vec2::normalized() const {
    return *this/length();
}

/**
 * returns the squared distance between two vectors
 */
float vec2::distanceSquared(const vec2& a, const vec2& b) {
    return (b - a).lengthSquared();
}

/**
 * returns the distance between two vectors
 */
float vec2::distance(const vec2& a, const vec2& b) {
    return (b - a).length();
}

/**
 * Returns the length squared of the vector
 * equivalent to dot product with itself
 */
float vec2::lengthSquared() const {
    return dot(*this, *this);
}

/**
 * Returns the length squared of the vector
 * equivalent to dot product with itself
 */
float vec2::lengthSquared(const vec2& a) {
    return dot(a, a);
}

/**
 * Returns the length of the vector
 */
float vec2::length() const {
    return sqrtf(lengthSquared());
}

/**
 * Returns the length of the vector
 */
float vec2::length(const vec2& a) {
    return sqrtf(a.lengthSquared());
}

/**
 * Returns a tangent vector of the same length to the current vector
 * the expression used is (-y,x)
 */
vec2 vec2::tangent() const {
    return vec2(-y, x);
}

/**
 * Returns a tangent vector of the same length to the current vector
 * the expression used is (-y,x)
 */
vec2 vec2::tangent(const vec2& vec) {
    return vec2(-vec.y, vec.x);
}

#pragma endregion vector operations

}

#pragma endregion vec2
