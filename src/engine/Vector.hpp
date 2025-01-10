#ifndef ENGINE_VECTOR
#define ENGINE_VECTOR

#include <array>
#include <string>
#include <iostream>

namespace Engine {

class vec4;
class vec3;
class vec2;
class vec4b;
class vec3b;
class vec2b;

/**
 * 4d vector of float
 */
typedef vec4 vec4f;
/**
 * 3d vector of float
 */
typedef vec3 vec3f;
/**
 * 2d vector of float
 */
typedef vec2 vec2f;

/**
 * 4d vector of float
 */
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
     * default constructor, fills the vector with 0
     */
    vec4();

    /**
     * fill constructor, fills the vector with the provided scalar value
     */
    vec4(const float& a);

    /**
     * concatenation constructor
     * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
     */
    vec4(const vec4& a);

    /**
     * concatenation constructor
     * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
     */
    vec4(const vec3& a, const float& b);

    /**
     * concatenation constructor
     * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
     */
    vec4(const float& a, const vec3& b);

    /**
     * concatenation constructor
     * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
     */
    vec4(const vec2& a, const vec2& b);

    /**
     * concatenation constructor
     * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
     */
    vec4(const vec2& a, const float& b, const float& c);

    /**
     * concatenation constructor
     * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
     */
    vec4(const float& a, const vec2& b, const float& c);

    /**
     * concatenation constructor
     * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
     */
    vec4(const float& a, const float& b, const vec2& c);

    /**
     * concatenation constructor
     * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
     */
    vec4(const float& a, const float& b, const float& c, const float& d);

    #pragma endregion constructors

    #pragma region conversions

    /**
     * casts a vector to a bool
     * true if all components are non-zero
     * to check if any components are non-zero, compare with vec4::zero rather than casting
     */
    explicit operator bool() const;

    /**
     * casts a boolean vector to a float vector
     */
    vec4(const vec4b& vec);

    #pragma endregion conversions

    #pragma region accessors

    /**
     * Array accessor
     * Returns the component at index i, 0-indexed
     */
    float& operator [](unsigned int i);

    /**
     * Array accessor
     * Returns the component at index i, 0-indexed
     */
    const float& operator [](unsigned int i) const;

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
    auto begin() noexcept;

    /**
     * iterator to the end of the components
     */
    auto end() noexcept;

    /**
     * iterator to the first component
     */
    auto begin() const noexcept;

    /**
     * iterator to the end of the components
     */
    auto end() const noexcept;

    /**
     * iterator to the first component
     */
    auto cbegin() const noexcept;

    /**
     * iterator to the end of the components
     */
    auto cend() const noexcept;

    /**
     * reverse iterator to the first component
     */
    auto rbegin() noexcept;

    /**
     * reverse iterator to the end of the components
     */
    auto rend() noexcept;

    /**
     * reverse iterator to the first component
     */
    auto rbegin() const noexcept;

    /**
     * reverse iterator to the end of the components
     */
    auto rend() const noexcept;

    /**
     * reverse iterator to the first component
     */
    auto crbegin() const noexcept;

    /**
     * reverse iterator to the end of the components
     */
    auto crend() const noexcept;

    #pragma endregion iteration
    
    #pragma region overloads
    
    /**
     * stream insertion operator
     */
    friend std::ostream& operator <<(std::ostream& os, const vec4& vec);

    /**
     * Copy assignment operator
     */
    vec4& operator =(const vec4& other);

    /**
     * component-wise addition operator
     */
    friend vec4 operator +(const vec4& a, const vec4& b);

    /**
     * component-wise addition operator
     */
    friend vec4 operator +(const float& a, const vec4& b);

    /**
     * component-wise addition operator
     */
    friend vec4 operator +(const vec4& a, const float& b);

    /**
     * component-wise subtraction operator
     */
    friend vec4 operator -(const vec4& a, const vec4& b);

    /**
     * component-wise subtraction operator
     */
    friend vec4 operator -(const float& a, const vec4& b);

    /**
     * component-wise subtraction operator
     */
    friend vec4 operator -(const vec4& a, const float& b);

    /**
     * component-wise negation operator
     */
    vec4 operator -() const;

    /**
     * component-wise multiplication operator
     */
    friend vec4 operator *(const vec4& a, const vec4& b);

    /**
     * component-wise multiplication operator
     */
    friend vec4 operator *(const float& a, const vec4& b);

    /**
     * component-wise multiplication operator
     */
    friend vec4 operator *(const vec4& a, const float& b);

    /**
     * component-wise division operator
     */
    friend vec4 operator /(const vec4& a, const vec4& b);

    /**
     * component-wise division operator
     */
    friend vec4 operator /(const float& a, const vec4& b);

    /**
     * component-wise division operator
     */
    friend vec4 operator /(const vec4& a, const float& b);

    /**
     * component-wise equality operator
     */
    vec4b operator ==(const vec4& other) const;

    /**
     * component-wise inequality operator
     */
    vec4b operator !=(const vec4& other) const;

    /**
     * component-wise less than operator
     */
    vec4b operator <(const vec4& other) const;

    /**
     * component-wise greater than operator
     */
    vec4b operator >(const vec4& other) const;

    /**
     * component-wise less than or equal to operator
     */
    vec4b operator <=(const vec4& other) const;

    /**
     * component-wise greater than or equal to operator
     */
    vec4b operator >=(const vec4& other) const;

    /**
     * component-wise addition assignment operator
     */
    vec4 operator +=(const vec4& other);

    /**
     * component-wise addition assignment operator
     */
    vec4 operator +=(const float& other);

    /**
     * component-wise subtraction assignment operator
     */
    vec4 operator -=(const vec4& other);

    /**
     * component-wise subtraction assignment operator
     */
    vec4 operator -=(const float& other);

    /**
     * component-wise multiplication assignment operator
     */
    vec4 operator *=(const vec4& other);

    /**
     * component-wise multiplication assignment operator
     */
    vec4 operator *=(const float& other);

    /**
     * component-wise division assignment operator
     */
    vec4 operator /=(const vec4& other);

    /**
     * component-wise division assignment operator
     */
    vec4 operator /=(const float& other);

    /**
     * component-wise increment operator
     */
    vec4 operator ++();

    /**
     * component-wise decrement operator
     */
    vec4 operator --();

    #pragma endregion overloads

    #pragma region vector operations
    
    /**
     * dot product of two vectors
     */
    static float dot(const vec4& a, const vec4& b);

    /**
     * angle between two vectors
     */
    static double angleBetween(const vec4& a, const vec4& b);

    /**
     * reflects incident vector, I, over normal, N
     * see https://registry.khronos.org/OpenGL-Refpages/gl4/html/reflect.xhtml
     */
    static vec4 reflect(const vec4& I, const vec4& N);

    /**
     * returns a vector in the same direction as the input vector, but with a length of 1
     */
    static vec4 normalize(const vec4& vec);

    /**
     * returns a vector in the same direction as this vector, but with a length of 1
     */
    vec4 normalized() const;

    /**
     * returns the squared distance between two vectors
     */
    static float distanceSquared(const vec4& a, const vec4& b);

    /**
     * returns the distance between two vectors
     */
    static float distance(const vec4& a, const vec4& b);

    /**
     * Returns the length squared of the vector
     * equivalent to dot product with itself
     */
    float lengthSquared() const;

    /**
     * Returns the length squared of the vector
     * equivalent to dot product with itself
     */
    static float lengthSquared(const vec4& a);

    /**
     * Returns the length of the vector
     */
    float length() const;

    /**
     * Returns the length of the vector
     */
    static float length(const vec4& a);

    #pragma endregion vector operations
};

/**
 * 3d vector of float
 */
class vec3 {
    private:
    // components
    std::array<float,3> data;

    public:

    #pragma region constants
    /**
     * vector of all zeros
     */
    static const vec3 zero;
    /**
     * vector of all ones
     */
    static const vec3 one;
    /**
     * positive x unit vector
     */
    static const vec3 right;
    /**
     * negative x unit vector
     */
    static const vec3 left;
    /**
     * positive y unit vector
     */
    static const vec3 up;
    /**
     * negative y unit vector
     */
    static const vec3 down;
    /**
     * positive z unit vector
     */
    static const vec3 forward;
    /**
     * negative z unit vector
     */
    static const vec3 back;

    #pragma endregion constants

    #pragma region constructors

    /**
     * default constructor, fills the vector with 0
     */
    vec3();

    /**
     * fill constructor, fills the vector with the provided scalar value
     */
    vec3(const float& a);

    /**
     * concatenation constructor
     * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
     */
    vec3(const vec3& a);

    /**
     * concatenation constructor
     * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
     */
    vec3(const vec2& a, const float& b);

    /**
     * concatenation constructor
     * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
     */
    vec3(const float& a, const vec2& b);

    /**
     * concatenation constructor
     * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
     */
    vec3(const float& a, const float& b, const float& c);

    #pragma endregion constructors

    #pragma region conversions

    /**
     * casts a vector to a bool
     * true if all components are non-zero
     * to check if any components are non-zero, compare with vec3::zero rather than casting
     */
    explicit operator bool() const;

    /**
     * casts a boolean vector to a float vector
     */
    vec3(const vec3b& vec);

    #pragma endregion conversions

    #pragma region accessors

    /**
     * Array accessor
     * Returns the component at index i, 0-indexed
     */
    float& operator [](unsigned int i);

    /**
     * Array accessor
     * Returns the component at index i, 0-indexed
     */
    const float& operator [](unsigned int i) const;

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
    auto begin() noexcept;

    /**
     * iterator to the end of the components
     */
    auto end() noexcept;

    /**
     * iterator to the first component
     */
    auto begin() const noexcept;

    /**
     * iterator to the end of the components
     */
    auto end() const noexcept;

    /**
     * iterator to the first component
     */
    auto cbegin() const noexcept;

    /**
     * iterator to the end of the components
     */
    auto cend() const noexcept;

    /**
     * reverse iterator to the first component
     */
    auto rbegin() noexcept;

    /**
     * reverse iterator to the end of the components
     */
    auto rend() noexcept;

    /**
     * reverse iterator to the first component
     */
    auto rbegin() const noexcept;

    /**
     * reverse iterator to the end of the components
     */
    auto rend() const noexcept;

    /**
     * reverse iterator to the first component
     */
    auto crbegin() const noexcept;

    /**
     * reverse iterator to the end of the components
     */
    auto crend() const noexcept;

    #pragma endregion iteration
    
    #pragma region overloads

    /**
     * stream insertion operator
     */
    friend std::ostream& operator <<(std::ostream& os, const vec3& vec);

    /**
     * Copy assignment operator
     */
    vec3& operator =(const vec3& other);

    /**
     * component-wise addition operator
     */
    friend vec3 operator +(const vec3& a, const vec3& b);

    /**
     * component-wise addition operator
     */
    friend vec3 operator +(const float& a, const vec3& b);

    /**
     * component-wise addition operator
     */
    friend vec3 operator +(const vec3& a, const float& b);

    /**
     * component-wise subtraction operator
     */
    friend vec3 operator -(const vec3& a, const vec3& b);

    /**
     * component-wise subtraction operator
     */
    friend vec3 operator -(const float& a, const vec3& b);

    /**
     * component-wise subtraction operator
     */
    friend vec3 operator -(const vec3& a, const float& b);

    /**
     * component-wise negation operator
     */
    vec3 operator -() const;

    /**
     * component-wise multiplication operator
     */
    friend vec3 operator *(const vec3& a, const vec3& b);

    /**
     * component-wise multiplication operator
     */
    friend vec3 operator *(const float& a, const vec3& b);

    /**
     * component-wise multiplication operator
     */
    friend vec3 operator *(const vec3& a, const float& b);

    /**
     * component-wise division operator
     */
    friend vec3 operator /(const vec3& a, const vec3& b);

    /**
     * component-wise division operator
     */
    friend vec3 operator /(const float& a, const vec3& b);

    /**
     * component-wise division operator
     */
    friend vec3 operator /(const vec3& a, const float& b);

    /**
     * component-wise equality operator
     */
    vec3b operator ==(const vec3& other) const;

    /**
     * component-wise inequality operator
     */
    vec3b operator !=(const vec3& other) const;
    
    /**
     * component-wise less than operator
     */
    vec3b operator <(const vec3& other) const;

    /**
     * component-wise greater than operator
     */
    vec3b operator >(const vec3& other) const;

    /**
     * component-wise less than or equal to operator
     */
    vec3b operator <=(const vec3& other) const;

    /**
     * component-wise greater than or equal to operator
     */
    vec3b operator >=(const vec3& other) const;

    /**
     * component-wise addition assignment operator
     */
    vec3 operator +=(const vec3& other);

    /**
     * component-wise addition assignment operator
     */
    vec3 operator +=(const float& other);

    /**
     * component-wise subtraction assignment operator
     */
    vec3 operator -=(const vec3& other);

    /**
     * component-wise subtraction assignment operator
     */
    vec3 operator -=(const float& other);

    /**
     * component-wise multiplication assignment operator
     */
    vec3 operator *=(const vec3& other);

    /**
     * component-wise multiplication assignment operator
     */
    vec3 operator *=(const float& other);

    /**
     * component-wise division assignment operator
     */
    vec3 operator /=(const vec3& other);

    /**
     * component-wise division assignment operator
     */
    vec3 operator /=(const float& other);

    /**
     * component-wise increment operator
     */
    vec3 operator ++();

    /**
     * component-wise decrement operator
     */
    vec3 operator --();

    #pragma endregion overloads

    #pragma region vector operations

    /**
     * dot product of two vectors
     */
    static float dot(const vec3& a, const vec3& b);

    /**
     * cross product of two vectors
     * returns a vector tangent to both input vectors
     */
    static vec3 cross(const vec3& a, const vec3& b);

    /**
     * angle between two vectors
     */
    static double angleBetween(const vec3& a, const vec3& b);

    /**
     * reflects incident vector, I, over normal, N
     * see https://registry.khronos.org/OpenGL-Refpages/gl4/html/reflect.xhtml
     */
    static vec3 reflect(const vec3& I, const vec3& N);

    /**
     * returns a vector in the same direction as the input vector, but with a length of 1
     */
    static vec3 normalize(const vec3& vec);

    /**
     * returns a vector in the same direction as this vector, but with a length of 1
     */
    vec3 normalized() const;

    /**
     * returns the squared distance between two vectors
     */
    static float distanceSquared(const vec3& a, const vec3& b);

    /**
     * returns the distance between two vectors
     */
    static float distance(const vec3& a, const vec3& b);

    /**
     * Returns the length squared of the vector
     * equivalent to dot product with itself
     */
    float lengthSquared() const;

    /**
     * Returns the length squared of the vector
     * equivalent to dot product with itself
     */
    static float lengthSquared(const vec3& a);

    /**
     * Returns the length of the vector
     */
    float length() const;

    /**
     * Returns the length of the vector
     */
    static float length(const vec3& a);

    /**
     * Returns a tangent vector of the same length to the current vector
     * the eexpression used is (-y,x,0) if |x| <= |z|, else (0,-z,y)
     */
    vec3 tangent() const;

    /**
     * Returns a tangent vector of the same length to the current vector
     * the eexpression used is (-y,x,0) if |x| <= |z|, else (0,-z,y)
     */
    static vec3 tangent(const vec3& vec);

    #pragma endregion vector operations
};

/**
 * 2d vector of float
 */
class vec2 {
    private:
    // components
    std::array<float,2> data;

    public:

    #pragma region constants

    /**
     * vector of all zeros
     */
    static const vec2 zero;
    /**
     * vector of all ones
     */
    static const vec2 one;
    /**
     * positive x unit vector
     */
    static const vec2 right;
    /**
     * negative x unit vector
     */
    static const vec2 left;
    /**
     * positive y unit vector
     */
    static const vec2 up;
    /**
     * negative y unit vector
     */
    static const vec2 down;

    #pragma endregion constants

    #pragma region constructors

    /**
     * default constructor, fills the vector with 0
     */
    vec2();

    /**
     * fill constructor, fills the vector with the provided scalar value
     */
    vec2(const float& a);

    /**
     * concatenation constructor
     * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
     */
    vec2(const vec2& a);
    
    /**
     * concatenation constructor
     * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
     */
    vec2(const float& a, const float& b);

    #pragma endregion constructors

    #pragma region conversions

    /**
     * casts a vector to a bool
     * true if all components are non-zero
     * to check if any components are non-zero, compare with vec2::zero rather than casting
     */
    explicit operator bool() const;

    /**
     * casts a boolean vector to a float vector
     */
    vec2(const vec2b& vec);

    #pragma endregion conversions

    #pragma region accessors

    /**
     * Array accessor
     * Returns the component at index i, 0-indexed
     */
    float& operator [](unsigned int i);

    /**
     * Array accessor
     * Returns the component at index i, 0-indexed
     */
    const float& operator [](unsigned int i) const;

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
    auto begin() noexcept;

    /**
     * iterator to the end of the components
     */
    auto end() noexcept;

    /**
     * iterator to the first component
     */
    auto begin() const noexcept;

    /**
     * iterator to the end of the components
     */
    auto end() const noexcept;

    /**
     * iterator to the first component
     */
    auto cbegin() const noexcept;

    /**
     * iterator to the end of the components
     */
    auto cend() const noexcept;

    /**
     * reverse iterator to the first component
     */
    auto rbegin() noexcept;

    /**
     * reverse iterator to the end of the components
     */
    auto rend() noexcept;

    /**
     * reverse iterator to the first component
     */
    auto rbegin() const noexcept;

    /**
     * reverse iterator to the end of the components
     */
    auto rend() const noexcept;

    /**
     * reverse iterator to the first component
     */
    auto crbegin() const noexcept;

    /**
     * reverse iterator to the end of the components
     */
    auto crend() const noexcept;

    #pragma endregion iteration

    #pragma region overloads

    /**
     * stream insertion operator
     */
    friend std::ostream& operator <<(std::ostream& os, const vec2& vec);

    /**
     * Copy assignment operator
     */
    vec2& operator =(const vec2& other);

    /**
     * component-wise addition operator
     */
    friend vec2 operator +(const vec2& a, const vec2& b);

    /**
     * component-wise addition operator
     */
    friend vec2 operator +(const float& a, const vec2& b);

    /**
     * component-wise addition operator
     */
    friend vec2 operator +(const vec2& a, const float& b);

    /**
     * component-wise subtraction operator
     */
    friend vec2 operator -(const vec2& a, const vec2& b);

    /**
     * component-wise subtraction operator
     */
    friend vec2 operator -(const float& a, const vec2& b);

    /**
     * component-wise subtraction operator
     */
    friend vec2 operator -(const vec2& a, const float& b);

    /**
     * component-wise negation operator
     */
    vec2 operator -() const;

    /**
     * component-wise multiplication operator
     */
    friend vec2 operator *(const vec2& a, const vec2& b);

    /**
     * component-wise multiplication operator
     */
    friend vec2 operator *(const float& a, const vec2& b);

    /**
     * component-wise multiplication operator
     */
    friend vec2 operator *(const vec2& a, const float& b);

    /**
     * component-wise division operator
     */
    friend vec2 operator /(const vec2& a, const vec2& b);

    /**
     * component-wise division operator
     */
    friend vec2 operator /(const float& a, const vec2& b);

    /**
     * component-wise division operator
     */
    friend vec2 operator /(const vec2& a, const float& b);

    /**
     * component-wise equality operator
     */
    vec2b operator ==(const vec2& other) const;

    /**
     * component-wise inequality operator
     */
    vec2b operator !=(const vec2& other) const;

    /**
     * component-wise less than operator
     */
    vec2b operator <(const vec2& other) const;

    /**
     * component-wise greater than operator
     */
    vec2b operator >(const vec2& other) const;

    /**
     * component-wise less than or equal to operator
     */
    vec2b operator <=(const vec2& other) const;

    /**
     * component-wise greater than or equal to operator
     */
    vec2b operator >=(const vec2& other) const;

    /**
     * component-wise addition assignment operator
     */
    vec2 operator +=(const vec2& other);

    /**
     * component-wise addition assignment operator
     */
    vec2 operator +=(const float& other);

    /**
     * component-wise subtraction assignment operator
     */
    vec2 operator -=(const vec2& other);

    /**
     * component-wise subtraction assignment operator
     */
    vec2 operator -=(const float& other);

    /**
     * component-wise multiplication assignment operator
     */
    vec2 operator *=(const vec2& other);

    /**
     * component-wise multiplication assignment operator
     */
    vec2 operator *=(const float& other);

    /**
     * component-wise division assignment operator
     */
    vec2 operator /=(const vec2& other);

    /**
     * component-wise division assignment operator
     */
    vec2 operator /=(const float& other);

    /**
     * component-wise increment operator
     */
    vec2 operator ++();

    /**
     * component-wise decrement operator
     */
    vec2 operator --();

    #pragma endregion overloads

    #pragma region vector operations

    /**
     * dot product of two vectors
     */
    static float dot(const vec2& a, const vec2& b);

    /**
     * cross product of two vectors
     * returns the determinant of the 2x2 matrix formed by the vectors
     */
    static float cross(const vec2& a, const vec2& b);

    /**
     * angle between two vectors
     */
    static double angleBetween(const vec2& a, const vec2& b);

    /**
     * reflects incident vector, I, over normal, N
     * see https://registry.khronos.org/OpenGL-Refpages/gl4/html/reflect.xhtml
     */
    static vec2 reflect(const vec2& I, const vec2& N);

    /**
     * returns a vector in the same direction as the input vector, but with a length of 1
     */
    static vec2 normalize(const vec2& vec);

    /**
     * returns a vector in the same direction as this vector, but with a length of 1
     */
    vec2 normalized() const;

    /**
     * returns the squared distance between two vectors
     */
    static float distanceSquared(const vec2& a, const vec2& b);

    /**
     * returns the distance between two vectors
     */
    static float distance(const vec2& a, const vec2& b);

    /**
     * Returns the length squared of the vector
     * equivalent to dot product with itself
     */
    float lengthSquared() const;

    /**
     * Returns the length squared of the vector
     * equivalent to dot product with itself
     */
    static float lengthSquared(const vec2& a);

    /**
     * Returns the length of the vector
     */
    float length() const;

    /**
     * Returns the length of the vector
     */
    static float length(const vec2& a);

    /**
     * Returns a tangent vector of the same length to the current vector
     * the expression used is (-y,x)
     */
    vec2 tangent() const;

    /**
     * Returns a tangent vector of the same length to the current vector
     * the expression used is (-y,x)
     */
    static vec2 tangent(const vec2& vec);

    #pragma endregion vector operations
};

/**
 * 4d vector of bool
 */
class vec4b {
    private:
    // components
    std::array<bool,4> data;

    public:

    #pragma region constants

    /**
     * vector of all falses
     */
    static const vec4b zero;
    /**
     * vector of all trues
     */
    static const vec4b one;

    #pragma endregion constants

    #pragma region constructors

    /**
     * default constructor, fills the vector with false
     */
    vec4b();

    /**
     * fill constructor, fills the vector with the provided scalar value
     */
    vec4b(const bool& a);

    /**
     * concatenation constructor
     * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
     */
    vec4b(const vec4b& a);

    /**
     * concatenation constructor
     * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
     */
    vec4b(const vec3b& a, const bool& b);

    /**
     * concatenation constructor
     * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
     */
    vec4b(const bool& a, const vec3b& b);

    /**
     * concatenation constructor
     * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
     */
    vec4b(const vec2b& a, const vec2b& b);

    /**
     * concatenation constructor
     * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
     */
    vec4b(const vec2b& a, const bool& b, const bool& c);

    /**
     * concatenation constructor
     * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
     */
    vec4b(const bool& a, const vec2b& b, const bool& c);

    /**
     * concatenation constructor
     * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
     */
    vec4b(const bool& a, const bool& b, const vec2b& c);

    /**
     * concatenation constructor
     * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
     */
    vec4b(const bool& a, const bool& b, const bool& c, const bool& d);

    #pragma endregion constructors

    #pragma region conversions

    /**
     * casts a vector to a bool
     * true if all components are non-zero
     * to check if any components are non-zero, compare with vec4b::zero rather than casting
     */
    explicit operator bool() const;

    /**
     * casts a float vector to a boolean vector
     */
    vec4b(const vec4& vec);

    #pragma endregion conversions

    #pragma region accessors

    /**
     * Array accessor
     * Returns the component at index i, 0-indexed
     */
    bool& operator [](unsigned int i);

    /**
     * Array accessor
     * Returns the component at index i, 0-indexed
     */
    const bool& operator [](unsigned int i) const;

    // position
    /**
     * The 1st component of the vector
     * equivalent to vec[0]
     */
    bool& x = data[0];
    /**
     * The 2nd component of the vector
     * equivalent to vec[1]
     */
    bool& y = data[1];
    /**
     * The 3rd component of the vector
     * equivalent to vec[2]
     */
    bool& z = data[2];
    /**
     * The 4th component of the vector
     * equivalent to vec[3]
     */
    bool& w = data[3];

    // color
    /**
     * The 1st component of the vector
     * equivalent to vec[0]
     */
    bool& r = data[0];
    /**
     * The 2nd component of the vector
     * equivalent to vec[1]
     */
    bool& g = data[1];
    /**
     * The 3rd component of the vector
     * equivalent to vec[2]
     */
    bool& b = data[2];
    /**
     * The 4th component of the vector
     * equivalent to vec[3]
     */
    bool& a = data[3];

    // texture coordinate
    /**
     * The 1st component of the vector
     * equivalent to vec[0]
     */
    bool& u = data[0];
    /**
     * The 2nd component of the vector
     * equivalent to vec[1]
     */
    bool& v = data[1];

    #pragma endregion accessors

    #pragma region iteration

    /**
     * iterator to the first component
     */
    auto begin() noexcept;

    /**
     * iterator to the end of the components
     */
    auto end() noexcept;

    /**
     * iterator to the first component
     */
    auto begin() const noexcept;

    /**
     * iterator to the end of the components
     */
    auto end() const noexcept;

    /**
     * iterator to the first component
     */
    auto cbegin() const noexcept;

    /**
     * iterator to the end of the components
     */
    auto cend() const noexcept;

    /**
     * reverse iterator to the first component
     */
    auto rbegin() noexcept;

    /**
     * reverse iterator to the end of the components
     */
    auto rend() noexcept;

    /**
     * reverse iterator to the first component
     */
    auto rbegin() const noexcept;

    /**
     * reverse iterator to the end of the components
     */
    auto rend() const noexcept;

    /**
     * reverse iterator to the first component
     */
    auto crbegin() const noexcept;

    /**
     * reverse iterator to the end of the components
     */
    auto crend() const noexcept;

    #pragma endregion iteration

    #pragma region overloads

    /**
     * stream insertion operator
     */
    friend std::ostream& operator <<(std::ostream& os, const vec4b& vec);

    /**
     * Copy assignment operator
     */
    vec4b& operator =(const vec4b& other);

    /**
     * component-wise and operator
     */
    friend vec4b operator &&(const vec4b& a, const vec4b& b);

    /**
     * component-wise and operator
     */
    friend vec4b operator &&(const bool& a, const vec4b& b);

    /**
     * component-wise and operator
     */
    friend vec4b operator &&(const vec4b& a, const bool& b);

    /**
     * component-wise or operator
     */
    friend vec4b operator ||(const vec4b& a, const vec4b& b);

    /**
     * component-wise or operator
     */
    friend vec4b operator ||(const bool& a, const vec4b& b);

    /**
     * component-wise or operator
     */
    friend vec4b operator ||(const vec4b& a, const bool& b);

    /**
     * component-wise not operator
     */
    vec4b operator !() const;

    /**
     * component-wise equality operator
     */
    friend vec4b operator ==(const vec4b& a, const vec4b& b);

    /**
     * component-wise inequality operator
     */
    friend vec4b operator !=(const vec4b& a, const vec4b& b);

    #pragma endregion overloads

    #pragma region vector operations

    /**
     * returns if any component is true
     */
    bool any() const;

    /**
     * returns if any component is true
     */
    friend bool any(const vec4b& vec);

    /**
     * returns if all components are true
     */
    bool all() const;

    /**
     * returns if all components are true
     */
    friend bool all(const vec4b& vec);

    /**
     * returns the number of true components
    */
    unsigned int count() const;

    /**
     * returns the number of true components
    */
   friend unsigned int count(const vec4b& vec);

    #pragma endregion vector operations
};

/**
 * 3d vector of bool
 */
class vec3b {
    private:
    // components
    std::array<bool,3> data;

    public:

    #pragma region constants

    /**
     * vector of all falses
     */
    static const vec3b zero;
    /**
     * vector of all trues
     */
    static const vec3b one;

    #pragma endregion constants

    #pragma region constructors

    /**
     * default constructor, fills the vector with false
     */
    vec3b();

    /**
     * fill constructor, fills the vector with the provided scalar value
     */
    vec3b(const bool& a);

    /**
     * concatenation constructor
     * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
     */
    vec3b(const vec3b& a);

    /**
     * concatenation constructor
     * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
     */
    vec3b(const bool& a, const vec2b& b);

    /**
     * concatenation constructor
     * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
     */
    vec3b(const vec2b& a, const bool& b);

    /**
     * concatenation constructor
     * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
     */
    vec3b(const bool& a, const bool& b, const bool& c);

    #pragma endregion constructors

    #pragma region conversions

    /**
     * casts a vector to a bool
     * true if all components are non-zero
     * to check if any components are non-zero, compare with vec4b::zero rather than casting
     */
    explicit operator bool() const;

    /**
     * casts a float vector to a boolean vector
     */
    vec3b(const vec3& vec);

    #pragma endregion conversions

    #pragma region accessors

    /**
     * Array accessor
     * Returns the component at index i, 0-indexed
     */
    bool& operator [](unsigned int i);

    /**
     * Array accessor
     * Returns the component at index i, 0-indexed
     */
    const bool& operator [](unsigned int i) const;

    // position
    /**
     * The 1st component of the vector
     * equivalent to vec[0]
     */
    bool& x = data[0];
    /**
     * The 2nd component of the vector
     * equivalent to vec[1]
     */
    bool& y = data[1];
    /**
     * The 3rd component of the vector
     * equivalent to vec[2]
     */
    bool& z = data[2];

    // color
    /**
     * The 1st component of the vector
     * equivalent to vec[0]
     */
    bool& r = data[0];
    /**
     * The 2nd component of the vector
     * equivalent to vec[1]
     */
    bool& g = data[1];
    /**
     * The 3rd component of the vector
     * equivalent to vec[2]
     */
    bool& b = data[2];

    // texture coordinate
    /**
     * The 1st component of the vector
     * equivalent to vec[0]
     */
    bool& u = data[0];
    /**
     * The 2nd component of the vector
     * equivalent to vec[1]
     */
    bool& v = data[1];

    #pragma endregion accessors

    #pragma region iteration

    /**
     * iterator to the first component
     */
    auto begin() noexcept;

    /**
     * iterator to the end of the components
     */
    auto end() noexcept;

    /**
     * iterator to the first component
     */
    auto begin() const noexcept;

    /**
     * iterator to the end of the components
     */
    auto end() const noexcept;

    /**
     * iterator to the first component
     */
    auto cbegin() const noexcept;

    /**
     * iterator to the end of the components
     */
    auto cend() const noexcept;

    /**
     * reverse iterator to the first component
     */
    auto rbegin() noexcept;

    /**
     * reverse iterator to the end of the components
     */
    auto rend() noexcept;

    /**
     * reverse iterator to the first component
     */
    auto rbegin() const noexcept;

    /**
     * reverse iterator to the end of the components
     */
    auto rend() const noexcept;

    /**
     * reverse iterator to the first component
     */
    auto crbegin() const noexcept;

    /**
     * reverse iterator to the end of the components
     */
    auto crend() const noexcept;

    #pragma endregion iteration

    #pragma region overloads

    /**
     * stream insertion operator
     */
    friend std::ostream& operator <<(std::ostream& os, const vec3b& vec);

    /**
     * Copy assignment operator
     */
    vec3b& operator =(const vec3b& other);

    /**
     * component-wise and operator
     */
    friend vec3b operator &&(const vec3b& a, const vec3b& b);

    /**
     * component-wise and operator
     */
    friend vec3b operator &&(const bool& a, const vec3b& b);

    /**
     * component-wise and operator
     */
    friend vec3b operator &&(const vec3b& a, const bool& b);

    /**
     * component-wise or operator
     */
    friend vec3b operator ||(const vec3b& a, const vec3b& b);

    /**
     * component-wise or operator
     */
    friend vec3b operator ||(const bool& a, const vec3b& b);

    /**
     * component-wise or operator
     */
    friend vec3b operator ||(const vec3b& a, const bool& b);

    /**
     * component-wise not operator
     */
    vec3b operator !() const;

    /**
     * component-wise equality operator
     */
    friend vec3b operator ==(const vec3b& a, const vec3b& b);

    /**
     * component-wise inequality operator
     */
    friend vec3b operator !=(const vec3b& a, const vec3b& b);

    #pragma endregion overloads

    #pragma region vector operations

    /**
     * returns if any component is true
     */
    bool any() const;

    /**
     * returns if any component is true
     */
    friend bool any(const vec3b& vec);

    /**
     * returns if all components are true
     */
    bool all() const;

    /**
     * returns if all components are true
     */
    friend bool all(const vec3b& vec);

    /**
     * returns the number of true components
    */
    unsigned int count() const;

    /**
     * returns the number of true components
    */
   friend unsigned int count(const vec3b& vec);

    #pragma endregion vector operations
};

/**
 * 2d vector of bool
 */
class vec2b {
    private:
    // components
    std::array<bool,2> data;

    public:

    #pragma region constants

    /**
     * vector of all falses
     */
    static const vec2b zero;
    /**
     * vector of all trues
     */
    static const vec2b one;

    #pragma endregion constants

    #pragma region constructors

    /**
     * default constructor, fills the vector with false
     */
    vec2b();

    /**
     * fill constructor, fills the vector with the provided scalar value
     */
    vec2b(const bool& a);

    /**
     * concatenation constructor
     * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
     */
    vec2b(const vec2b& a);

    /**
     * concatenation constructor
     * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
     */
    vec2b(const bool& a, const bool& b);

    #pragma endregion constructors

    #pragma region conversions

    /**
     * casts a vector to a bool
     * true if all components are non-zero
     * to check if any components are non-zero, compare with vec4b::zero rather than casting
     */
    explicit operator bool() const;

    /**
     * casts a float vector to a boolean vector
     */
    vec2b(const vec2& vec);

    #pragma endregion conversions

    #pragma region accessors

    /**
     * Array accessor
     * Returns the component at index i, 0-indexed
     */
    bool& operator [](unsigned int i);

    /**
     * Array accessor
     * Returns the component at index i, 0-indexed
     */
    const bool& operator [](unsigned int i) const;

    // position
    /**
     * The 1st component of the vector
     * equivalent to vec[0]
     */
    bool& x = data[0];
    /**
     * The 2nd component of the vector
     * equivalent to vec[1]
     */
    bool& y = data[1];

    // color
    /**
     * The 1st component of the vector
     * equivalent to vec[0]
     */
    bool& r = data[0];
    /**
     * The 2nd component of the vector
     * equivalent to vec[1]
     */
    bool& g = data[1];

    // texture coordinate
    /**
     * The 1st component of the vector
     * equivalent to vec[0]
     */
    bool& u = data[0];
    /**
     * The 2nd component of the vector
     * equivalent to vec[1]
     */
    bool& v = data[1];

    #pragma endregion accessors

    #pragma region iteration

    /**
     * iterator to the first component
     */
    auto begin() noexcept;

    /**
     * iterator to the end of the components
     */
    auto end() noexcept;

    /**
     * iterator to the first component
     */
    auto begin() const noexcept;

    /**
     * iterator to the end of the components
     */
    auto end() const noexcept;

    /**
     * iterator to the first component
     */
    auto cbegin() const noexcept;

    /**
     * iterator to the end of the components
     */
    auto cend() const noexcept;

    /**
     * reverse iterator to the first component
     */
    auto rbegin() noexcept;

    /**
     * reverse iterator to the end of the components
     */
    auto rend() noexcept;

    /**
     * reverse iterator to the first component
     */
    auto rbegin() const noexcept;

    /**
     * reverse iterator to the end of the components
     */
    auto rend() const noexcept;

    /**
     * reverse iterator to the first component
     */
    auto crbegin() const noexcept;

    /**
     * reverse iterator to the end of the components
     */
    auto crend() const noexcept;

    #pragma endregion iteration

    #pragma region overloads

    /**
     * stream insertion operator
     */
    friend std::ostream& operator <<(std::ostream& os, const vec2b& vec);

    /**
     * Copy assignment operator
     */
    vec2b& operator =(const vec2b& other);

    /**
     * component-wise and operator
     */
    friend vec2b operator &&(const vec2b& a, const vec2b& b);

    /**
     * component-wise and operator
     */
    friend vec2b operator &&(const bool& a, const vec2b& b);

    /**
     * component-wise and operator
     */
    friend vec2b operator &&(const vec2b& a, const bool& b);

    /**
     * component-wise or operator
     */
    friend vec2b operator ||(const vec2b& a, const vec2b& b);

    /**
     * component-wise or operator
     */
    friend vec2b operator ||(const bool& a, const vec2b& b);

    /**
     * component-wise or operator
     */
    friend vec2b operator ||(const vec2b& a, const bool& b);

    /**
     * component-wise not operator
     */
    vec2b operator !() const;

    /**
     * component-wise equality operator
     */
    friend vec2b operator ==(const vec2b& a, const vec2b& b);

    /**
     * component-wise inequality operator
     */
    friend vec2b operator !=(const vec2b& a, const vec2b& b);

    #pragma endregion overloads

    #pragma region vector operations

    /**
     * returns if any component is true
     */
    bool any() const;

    /**
     * returns if any component is true
     */
    friend bool any(const vec2b& vec);

    /**
     * returns if all components are true
     */
    bool all() const;

    /**
     * returns if all components are true
     */
    friend bool all(const vec2b& vec);

    /**
     * returns the number of true components
    */
    unsigned int count() const;

    /**
     * returns the number of true components
    */
   friend unsigned int count(const vec2b& vec);

    #pragma endregion vector operations
};

}

namespace std {
    /**
     * converts a vector to a string
     */
    std::string to_string(const Engine::vec4& vec);
    /**
     * converts a vector to a string
     */
    std::string to_string(const Engine::vec3& vec);
    /**
     * converts a vector to a string
     */
    std::string to_string(const Engine::vec2& vec);
    /**
     * converts a vector to a string
     */
    std::string to_string(const Engine::vec4b& vec);
    /**
     * converts a vector to a string
     */
    std::string to_string(const Engine::vec3b& vec);
    /**
     * converts a vector to a string
     */
    std::string to_string(const Engine::vec2b& vec);
}

#endif
