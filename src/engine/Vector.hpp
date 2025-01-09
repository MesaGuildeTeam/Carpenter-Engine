#include <array>
#include <string>
#include <iostream>

namespace std {
    std::string to_string(const vec4& vec);
}

class vec4 {
    private:
    // components
    std::array<float,4> data;

    public:

    #pragma region constants
    /**
     * vector of all zeros
     */
    static const vec4 zero;
    /**
     * vector of all ones
     */
    static const vec4 one;
    /**
     * positive x unit vector
     */
    static const vec4 up;
    /**
     * negative x unit vector
     */
    static const vec4 down;
    /**
     * positive y unit vector
     */
    static const vec4 left;
    /**
     * negative y unit vector
     */
    static const vec4 right;
    /**
     * positive z unit vector
     */
    static const vec4 forward;
    /**
     * negative z unit vector
     */
    static const vec4 back;
    /**
     * positive w unit vector
     */
    static const vec4 ana;
    /**
     * negative w unit vector
     */
    static const vec4 kata;

    #pragma endregion constants

    #pragma region constructors

    /**
     * default constructor, fills the vector with the default value of the base type (0 for most things)
     */
    vec4(){
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
        w = 0.0f;
    }

    /**
     * fill constructor, fills the vector with the provided scalar value
     */
    vec4(const float& a){
        x = a;
        y = a;
        z = a;
        w = a;
    }

    /**
     * concatenation constructor
     * creates a vector from a list of vectors of a convertible type and of total dimensions summing to the target dimension
     */
    vec4(const vec4& a) {
        x = a.x;
        y = a.y;
        z = a.z;
        w = a.w;
    }

    vec4(const vec3& a, const float& b) {
        x = a.x;
        y = a.y;
        z = a.z;
        w = b;
    }

    vec4(const float& a, const vec3& b) {
        x = a;
        y = b.x;
        z = b.y;
        w = b.z;
    }

    vec4(const vec2& a, const vec2& b) {
        x = a.x;
        y = a.y;
        z = b.x;
        w = b.y;
    }

    vec4(const vec2& a, const float& b, const float& c) {
        x = a.x;
        y = a.y;
        z = b;
        w = c;
    }

    vec4(const float& a, const vec2& b, const float& c) {
        x = a;
        y = b.x;
        z = b.y;
        w = c;
    }

    vec4(const float& a, const float& b, const vec2& c) {
        x = a;
        y = b;
        z = c.x;
        w = c.y;
    }

    vec4(const float& a, const float& b, const float& c, const float& d) {
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
     * to check if any components are non-zero, compare with vec4.zero rather than casting
     */
    explicit operator bool() const {
        return x && y && z && w;
    }

    /**
     * casts a boolean vector to a float vector
     */
    vec4(const bvec4& vec){
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
    float& operator [](unsigned int i) {
        if (i >= 4) {
            throw std::out_of_range("Index out of range");
        }
        return data[i];
    }

    /**
     * Array accessor
     * Returns the component at index i, 0-indexed
     */
    const float& operator [](unsigned int i) const {
        if (i >= 4) {
            throw std::out_of_range("Index out of range");
        }
        return data[i];
    }

    // position
    /**
     * The 1st component of the vector
     * equivalent to vec[0]
     */
    float& x = data[0];
    /**
     * The 2nd component of the vector
     * equivalent to vec[1]
     */
    float& y = data[1];
    /**
     * The 3rd component of the vector
     * equivalent to vec[2]
     */
    float& z = data[2];
    /**
     * The 4th component of the vector
     * equivalent to vec[3]
     */
    float& w = data[3];

    // color
    /**
     * The 1st component of the vector
     * equivalent to vec[0]
     */
    float& r = data[0];
    /**
     * The 2nd component of the vector
     * equivalent to vec[1]
     */
    float& g = data[1];
    /**
     * The 3rd component of the vector
     * equivalent to vec[2]
     */
    float& b = data[2];
    /**
     * The 4th component of the vector
     * equivalent to vec[3]
     */
    float& a = data[3];

    // texture coordinate
    /**
     * The 1st component of the vector
     * equivalent to vec[0]
     */
    float& u = data[0];
    /**
     * The 2nd component of the vector
     * equivalent to vec[1]
     */
    float& v = data[1];

    #pragma endregion accessors

    #pragma region iteration

    /**
     * iterator to the first component
     */
    auto begin() noexcept {
        return data.begin();
    }

    /**
     * iterator to the end of the components
     */
    auto end() noexcept {
        return data.end();
    }

    /**
     * iterator to the first component
     */
    auto begin() const noexcept {
        return data.begin();
    }

    /**
     * iterator to the end of the components
     */
    auto end() const noexcept {
        return data.end();
    }

    /**
     * iterator to the first component
     */
    auto cbegin() const noexcept {
        return data.cbegin();
    }

    /**
     * iterator to the end of the components
     */
    auto cend() const noexcept {
        return data.cend();
    }

    /**
     * reverse iterator to the first component
     */
    auto rbegin() noexcept {
        return data.rbegin();
    }

    /**
     * reverse iterator to the end of the components
     */
    auto rend() noexcept {
        return data.rend();
    }

    /**
     * reverse iterator to the first component
     */
    auto rbegin() const noexcept {
        return data.rbegin();
    }

    /**
     * reverse iterator to the end of the components
     */
    auto rend() const noexcept {
        return data.rend();
    }

    /**
     * reverse iterator to the first component
     */
    auto crbegin() const noexcept {
        return data.crbegin();
    }

    /**
     * reverse iterator to the end of the components
     */
    auto crend() const noexcept {
        return data.crend();
    }

    #pragma endregion iteration
    
    #pragma region overloads
    
    /**
     * stream insertion operator
     */
    friend std::ostream& operator <<(std::ostream& os, const vec4& vec) {
        os << std::to_string(vec);
        return os;
    }

    /**
     * Copy assignment operator
     */
    vec4& operator =(const vec4& other) {
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;
        return *this;
    }

    /**
     * component-wise addition operator
     */
    friend vec4 operator +(const vec4& a, const vec4& b) {
        return vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
    }

    /**
     * component-wise addition operator
     */
    friend vec4 operator +(const float& a, const vec4& b) {
        return vec4(a + b.x, a + b.y, a + b.z, a + b.w);
    }

    /**
     * component-wise addition operator
     */
    friend vec4 operator +(const vec4& a, const float& b) {
        return vec4(a.x + b, a.y + b, a.z + b, a.w + b);
    }

    /**
     * component-wise subtraction operator
     */
    friend vec4 operator -(const vec4& a, const vec4& b) {
        return vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
    }

    /**
     * component-wise subtraction operator
     */
    friend vec4 operator -(const float& a, const vec4& b) {
        return vec4(a - b.x, a - b.y, a - b.z, a - b.w);
    }

    /**
     * component-wise subtraction operator
     */
    friend vec4 operator -(const vec4& a, const float& b) {
        return vec4(a.x - b, a.y - b, a.z - b, a.w - b);
    }

    /**
     * component-wise negation operator
     */
    vec4 operator -() const {
        return vec4(-x, -y, -z, -w);
    }

    /**
     * component-wise multiplication operator
     */
    friend vec4 operator *(const vec4& a, const vec4& b) {
        return vec4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
    }

    /**
     * component-wise multiplication operator
     */
    friend vec4 operator *(const float& a, const vec4& b) {
        return vec4(a * b.x, a * b.y, a * b.z, a * b.w);
    }

    /**
     * component-wise multiplication operator
     */
    friend vec4 operator *(const vec4& a, const float& b) {
        return vec4(a.x * b, a.y * b, a.z * b, a.w * b);
    }

    /**
     * component-wise division operator
     */
    friend vec4 operator /(const vec4& a, const vec4& b) {
        return vec4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
    }

    /**
     * component-wise division operator
     */
    friend vec4 operator /(const float& a, const vec4& b) {
        return vec4(a / b.x, a / b.y, a / b.z, a / b.w);
    }

    /**
     * component-wise division operator
     */
    friend vec4 operator /(const vec4& a, const float& b) {
        return vec4(a.x / b, a.y / b, a.z / b, a.w / b);
    }

    /**
     * component-wise equality operator
     */
    bvec4 operator ==(const vec4& other) const {
        return bvec4(x == other.x, y == other.y, z == other.z, w == other.w);
    }

    /**
     * component-wise inequality operator
     */
    bvec4 operator !=(const vec4& other) const {
        return bvec4(x != other.x, y != other.y, z != other.z, w != other.w);
    }

    /**
     * component-wise less than operator
     */
    bvec4 operator <(const vec4& other) const {
        return bvec4(x < other.x, y < other.y, z < other.z, w < other.w);
    }

    /**
     * component-wise greater than operator
     */
    bvec4 operator >(const vec4& other) const {
        return bvec4(x > other.x, y > other.y, z > other.z, w > other.w);
    }

    /**
     * component-wise less than or equal to operator
     */
    bvec4 operator <=(const vec4& other) const {
        return bvec4(x <= other.x, y <= other.y, z <= other.z, w <= other.w);
    }

    /**
     * component-wise greater than or equal to operator
     */
    bvec4 operator >=(const vec4& other) const {
        return bvec4(x >= other.x, y >= other.y, z >= other.z, w >= other.w);   
    }

    /**
     * component-wise addition assignment operator
     */
    vec4 operator +=(const vec4& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }

    /**
     * component-wise addition assignment operator
     */
    vec4 operator +=(const float& other) {
        x += other;
        y += other;
        z += other;
        w += other;
        return *this;
    }

    /**
     * component-wise subtraction assignment operator
     */
    vec4 operator -=(const vec4& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;
    }

    /**
     * component-wise subtraction assignment operator
     */
    vec4 operator -=(const float& other) {
        x -= other;
        y -= other;
        z -= other;
        w -= other;
        return *this;
    }

    /**
     * component-wise multiplication assignment operator
     */
    vec4 operator *=(const vec4& other) {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        w *= other.w;
        return *this;
    }

    /**
     * component-wise multiplication assignment operator
     */
    vec4 operator *=(const float& other) {
        x *= other;
        y *= other;
        z *= other;
        w *= other;
        return *this;
    }

    /**
     * component-wise division assignment operator
     */
    vec4 operator /=(const vec4& other) {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        w /= other.w;
        return *this;
    }

    /**
     * component-wise division assignment operator
     */
    vec4 operator /=(const float& other) {
        x /= other;
        y /= other;
        z /= other;
        w /= other;
        return *this;
    }

    /**
     * component-wise increment operator
     */
    vec4 operator ++() {
        x++;
        y++;
        z++;
        w++;
        return *this;
    }

    /**
     * component-wise decrement operator
     */
    vec4 operator --() {
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
    static float dot(const vec4& a, const vec4& b) {
        return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
    }

    /**
     * angle between two vectors
     */
    static double angleBetween(const vec4& a, const vec4& b) {
        return acos( dot(a,b) / sqrt(a.lengthSquared()*b.lengthSquared()) );
    }

    /**
     * reflects incident vector, I, over normal, N
     * see https://registry.khronos.org/OpenGL-Refpages/gl4/html/reflect.xhtml
     */
    static vec4 reflect(const vec4& I, const vec4& N) {
        return I - 2.0*dot(N, I)*N;
    }

    /**
     * returns a vector in the same direction as the input vector, but with a length of 1
     */
    static vec4 normalize(const vec4& vec) {
        return vec/vec.length();
    }

    /**
     * returns a vector in the same direction as this vector, but with a length of 1
     */
    vec4 normalized() const {
        return *this/length();
    }

    /**
     * returns the distance between two vectors
     */
    static float distanceSquared(const vec4& a, const vec4& b) {
        return (b - a).lengthSquared();
    }

    /**
     * returns the distance between two vectors
     */
    static float distance(const vec4& a, const vec4& b) {
        return (b - a).length();
    }

    /**
     * Returns the length squared of the vector
     * equivalent to dot product with itself
     */
    float lengthSquared() const {
        return dot(*this, *this);
    }

    /**
     * Returns the length squared of the vector
     * equivalent to dot product with itself
     */
    static float lengthSquared(const vec4& a) {
        return dot(a, a);
    }

    /**
     * Returns the length of the vector
     */
    float length() const {
        return sqrtf(lengthSquared());
    }

    /**
     * Returns the length of the vector
     */
    static float length(const vec4& a) {
        return sqrtf(a.lengthSquared());
    }

    #pragma endregion vector operations
};

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