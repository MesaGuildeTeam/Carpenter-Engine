#ifndef ENGINE_VEC3
#define ENGINE_VEC3


#include "Vector.hpp"
#include "bvec3.hpp"

namespace Engine {

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
     * Vector of all zeros
     */
    static const vec3 zero;
    /**
     * Vector of all ones
     */
    static const vec3 one;
    /**
     * Positive x unit vector
     */
    static const vec3 right;
    /**
     * Negative x unit vector
     */
    static const vec3 left;
    /**
     * Positive y unit vector
     */
    static const vec3 up;
    /**
     * Negative y unit vector
     */
    static const vec3 down;
    /**
     * Positive z unit vector
     */
    static const vec3 forward;
    /**
     * Negative z unit vector
     */
    static const vec3 back;

    /**
     * Dimension of vector
     */
    static constexpr unsigned int dimension = 3;

    #pragma endregion constants

    #pragma region constructors

    /**
     * Default constructor, fills the vector with 0
     */
    vec3();

    /**
     * Fill constructor, fills the vector with the provided scalar value
     * @param a scalar to fill with
     */
    template <typename T>
    requires std::is_convertible_v<T, float>
    explicit vec3(const T a){
        data.fill(float(a));
    }

    /**
     * Copy constructor
     * @param vec vector to copy
     */
    vec3(const vec3& vec);

    /**
     * Concatenation constructor
     * Creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
     * @param vecs list of vectors or scalars
     * @note `vec4(vec2(1,2), 3, 4) == vec4(1, 2, 3, 4)`
     */
    template <typename ... Vectors>
    requires ((is_vec_v<Vectors> || std::is_convertible_v<Vectors, float>) && ... ) && ((dimension_of_v<Vectors> + ...) == dimension)
    vec3(const Vectors... vecs) {
        unsigned int i = 0;
        ([&] {
            if constexpr (is_vec_v<Vectors>) {
                for (unsigned int j = 0; j < Vectors::dimension; j++) {
                    data[i] = float(vecs[j]);
                    i++;
                }
            } else {
                data[i] = float(vecs);
                i++;
            }
        }(), ...);
    }


    #pragma endregion constructors

    #pragma region conversions

    /**
     * casts a vector to a bool
     * True if **all** components are non-zero
     * @note To check if **any** components are non-zero, use `vec != vec3::zero`
     */
    operator bool() const;

    /**
     * Casts a boolean vector to a float vector
     * @param vec boolean vector
     */
    vec3(const bvec3& vec);

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
     * @note Equivalent to `vec[0]`
     */
    float& x = data[0];
    /**
     * The 2nd component of the vector
     * @note Equivalent to `vec[1]`
     */
    float& y = data[1];
    /**
     * The 3rd component of the vector
     * @note Equivalent to `vec[2]`
     */
    float& z = data[2];

    // color
    /**
     * The 1st component of the vector
     * @note Equivalent to `vec[0]`
     */
    float& r = data[0];
    /**
     * The 2nd component of the vector
     * @note Equivalent to `vec[1]`
     */
    float& g = data[1];
    /**
     * The 3rd component of the vector
     * @note Equivalent to `vec[2]`
     */
    float& b = data[2];

    // texture coordinate
    /**
     * The 1st component of the vector
     * @note Equivalent to `vec[0]`
     */
    float& u = data[0];
    /**
     * The 2nd component of the vector
     * @note Equivalent to `vec[1]`
     */
    float& v = data[1];

    #pragma endregion accessors

    #pragma region iteration

    /**
     * Iterator to the first component
     * @see [std::array::begin](https://en.cppreference.com/w/cpp/container/array/begin)
     */
    auto begin() noexcept;

    /**
     * Iterator to the end of the components
     * @see [std::array::end](https://en.cppreference.com/w/cpp/container/array/end)
     */
    auto end() noexcept;

    /**
     * Iterator to the first component
     * @see [std::array::begin](https://en.cppreference.com/w/cpp/container/array/begin)
     */
    auto begin() const noexcept;

    /**
     * Iterator to the end of the components
     * @see [std::array::end](https://en.cppreference.com/w/cpp/container/array/end)
     */
    auto end() const noexcept;

    /**
     * Iterator to the first component
     * @see [std::array::cbegin](https://en.cppreference.com/w/cpp/container/array/cbegin)
     */
    auto cbegin() const noexcept;

    /**
     * Iterator to the end of the components
     * @see [std::array::cend](https://en.cppreference.com/w/cpp/container/array/cend)
     */
    auto cend() const noexcept;

    /**
     * Reverse iterator to the first component
     * @see [std::array::rbegin](https://en.cppreference.com/w/cpp/container/array/rbegin)
     */
    auto rbegin() noexcept;

    /**
     * Reverse iterator to the end of the components
     * @see [std::array::rend](https://en.cppreference.com/w/cpp/container/array/rend)
     */
    auto rend() noexcept;

    /**
     * Reverse iterator to the first component
     * @see [std::array::rbegin](https://en.cppreference.com/w/cpp/container/array/rbegin)
     */
    auto rbegin() const noexcept;

    /**
     * Reverse iterator to the end of the components
     * @see [std::array::rend](https://en.cppreference.com/w/cpp/container/array/rend)
     */
    auto rend() const noexcept;

    /**
     * Reverse iterator to the first component
     * @see [std::array::crbegin](https://en.cppreference.com/w/cpp/container/array/crbegin)
     */
    auto crbegin() const noexcept;

    /**
     * Reverse iterator to the end of the components
     * @see [std::array::crend](https://en.cppreference.com/w/cpp/container/array/crend)
     */
    auto crend() const noexcept;

    #pragma endregion iteration
    
    #pragma region overloads

    /**
     * Copy assignment operator
     */
    vec3& operator =(const vec3& other);

    /**
     * Component-wise addition operator
     */
    friend vec3 operator +(const vec3& a, const vec3& b);

    /**
     * Component-wise addition operator
     */
    friend vec3 operator +(const float& a, const vec3& b);

    /**
     * Component-wise addition operator
     */
    friend vec3 operator +(const vec3& a, const float& b);

    /**
     * Component-wise subtraction operator
     */
    friend vec3 operator -(const vec3& a, const vec3& b);

    /**
     * Component-wise subtraction operator
     */
    friend vec3 operator -(const float& a, const vec3& b);

    /**
     * Component-wise subtraction operator
     */
    friend vec3 operator -(const vec3& a, const float& b);

    /**
     * Component-wise negation operator
     */
    vec3 operator -() const;

    /**
     * Component-wise multiplication operator
     */
    friend vec3 operator *(const vec3& a, const vec3& b);

    /**
     * Component-wise multiplication operator
     */
    friend vec3 operator *(const float& a, const vec3& b);

    /**
     * Component-wise multiplication operator
     */
    friend vec3 operator *(const vec3& a, const float& b);

    /**
     * Component-wise division operator
     */
    friend vec3 operator /(const vec3& a, const vec3& b);

    /**
     * Component-wise division operator
     */
    friend vec3 operator /(const float& a, const vec3& b);

    /**
     * Component-wise division operator
     */
    friend vec3 operator /(const vec3& a, const float& b);

    /**
     * Component-wise equality operator
     */
    bvec3 operator ==(const vec3& other) const;

    /**
     * Component-wise inequality operator
     */
    bvec3 operator !=(const vec3& other) const;
    
    /**
     * Component-wise less than operator
     */
    bvec3 operator <(const vec3& other) const;

    /**
     * Component-wise greater than operator
     */
    bvec3 operator >(const vec3& other) const;

    /**
     * Component-wise less than or equal to operator
     */
    bvec3 operator <=(const vec3& other) const;

    /**
     * Component-wise greater than or equal to operator
     */
    bvec3 operator >=(const vec3& other) const;

    /**
     * Component-wise addition assignment operator
     */
    vec3& operator +=(const vec3& other);

    /**
     * Component-wise addition assignment operator
     */
    vec3& operator +=(const float& other);

    /**
     * Component-wise subtraction assignment operator
     */
    vec3& operator -=(const vec3& other);

    /**
     * Component-wise subtraction assignment operator
     */
    vec3& operator -=(const float& other);

    /**
     * Component-wise multiplication assignment operator
     */
    vec3& operator *=(const vec3& other);

    /**
     * Component-wise multiplication assignment operator
     */
    vec3& operator *=(const float& other);

    /**
     * Component-wise division assignment operator
     */
    vec3& operator /=(const vec3& other);

    /**
     * Component-wise division assignment operator
     */
    vec3& operator /=(const float& other);

    /**
     * Component-wise increment operator
     */
    vec3& operator ++();

    /**
     * Component-wise decrement operator
     */
    vec3& operator --();

    #pragma endregion overloads

    #pragma region vector operations

    /**
     * Returns a vector in the same direction as this vector, but with a length of 1
     * @return Normalized vector
     */
    vec3 normalized() const;

    /**
     * Returns the length squared of the vector
     * @note This is faster than `a.length()` by one square root operation
     */
    float lengthSquared() const;

    /**
     * Returns the length of the vector
     * @param a vector to get the length of
     * @return Length of the vector
     */
    float length() const;

    /**
     * Returns a tangent vector of the same length to the current vector
     * the eexpression used is (-y,x,0) if |x| <= |z|, else (0,-z,y)
     */
    vec3 tangent() const;

    #pragma endregion vector operations
};

/**
 * Dot product of two vectors
 * @param a first vector
 * @param b second vector
 * @return Dot product of the two vectors
 */
float dot(const vec3& a, const vec3& b);

/**
 * Cross product of two vectors
 * @param a first vector
 * @param b second vector
 * @return The cross product of the two vectors (a vector orthogonal to both vectors)
 */
vec3 cross(const vec3& a, const vec3& b);

/**
 * Angle between two vectors
 * @param a first vector
 * @param b second vector
 * @return Angle between the two vectors in radians
 */
double angleBetween(const vec3& a, const vec3& b);

/**
 * Reflects incident vector, `I`, over surface with normal, `N`
 * @param I incident vector
 * @param N surface normal
 * @return Reflected vector
 * @note Input does not need to be normalized
 */
vec3 reflect(const vec3& I, const vec3& N);


/**
 * Returns the squared distance between two vectors
 * @param a first vector
 * @param b second vector
 * @return Squared distance from `a` to `b`
 * @note This is faster than `vec2::distance(a, b)` by one square root operation
 */
float distanceSquared(const vec3& a, const vec3& b);

/**
 * Returns the distance between two vectors
 * @param a first vector
 * @param b second vector
 * @return Distance from `a` to `b`
 */
float distance(const vec3& a, const vec3& b);

/**
 * Converts a vector to a string
 * @note Format is `[x, y, ...]`
 */
std::string to_string(const vec3& vec);

}

#endif
