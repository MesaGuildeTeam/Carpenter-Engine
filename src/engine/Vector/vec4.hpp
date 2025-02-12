#ifndef ENGINE_VEC4
#define ENGINE_VEC4


#include "Vector.hpp"
#include "bvec4.hpp"

namespace Engine {

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
     * Vector of all zeros
     */
    static const vec4 zero;
    /**
     * Vector of all ones
     */
    static const vec4 one;
    /**
     * Positive x unit vector
     */
    static const vec4 up;
    /**
     * Negative x unit vector
     */
    static const vec4 down;
    /**
     * Positive y unit vector
     */
    static const vec4 left;
    /**
     * Negative y unit vector
     */
    static const vec4 right;
    /**
     * Positive z unit vector
     */
    static const vec4 forward;
    /**
     * Negative z unit vector
     */
    static const vec4 back;
    /**
     * Positive w unit vector
     */
    static const vec4 ana;
    /**
     * Negative w unit vector
     */
    static const vec4 kata;

    /**
     * Dimension of vector
     */
    static constexpr unsigned int dimension = 4;

    #pragma endregion constants

    #pragma region constructors

    /**
     * Default constructor, fills the vector with 0
     */
    vec4();

    /**
     * Fill constructor, fills the vector with the provided scalar value
     * @param a scalar to fill with
     */
    template <typename T>
    requires std::is_convertible_v<T, float>
    explicit vec4(const T a){
        data.fill(float(a));
    }

    /**
     * Copy constructor
     * @param vec vector to copy
     */
    vec4(const vec4& vec);

    /**
     * Concatenation constructor
     * Creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
     * @param vecs list of vectors or scalars
     * @note `vec4(vec2(1,2), 3, 4) == vec4(1, 2, 3, 4)`
     */
    template <typename ... Vectors>
    requires ((is_vec_v<Vectors> || std::is_convertible_v<Vectors, float>) && ... ) && ((dimension_of_v<Vectors> + ...) == dimension)
    vec4(const Vectors... vecs) {
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
     * @note To check if **any** components are non-zero, use `vec != vec2::zero`
     */
    operator bool() const;

    /**
     * Casts a boolean vector to a float vector
     * @param vec boolean vector
     */
    vec4(const bvec4& vec);

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
    /**
     * The 4th component of the vector
     * @note Equivalent to `vec[3]`
     */
    float& w = data[3];

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
    /**
     * The 4th component of the vector
     * @note Equivalent to `vec[3]`
     */
    float& a = data[3];

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
    vec4& operator =(const vec4& other);

    /**
     * Component-wise addition operator
     */
    friend vec4 operator +(const vec4& a, const vec4& b);

    /**
     * Component-wise addition operator
     */
    friend vec4 operator +(const float& a, const vec4& b);

    /**
     * Component-wise addition operator
     */
    friend vec4 operator +(const vec4& a, const float& b);

    /**
     * Component-wise subtraction operator
     */
    friend vec4 operator -(const vec4& a, const vec4& b);

    /**
     * Component-wise subtraction operator
     */
    friend vec4 operator -(const float& a, const vec4& b);

    /**
     * Component-wise subtraction operator
     */
    friend vec4 operator -(const vec4& a, const float& b);

    /**
     * Component-wise negation operator
     */
    vec4 operator -() const;

    /**
     * Component-wise multiplication operator
     */
    friend vec4 operator *(const vec4& a, const vec4& b);

    /**
     * Component-wise multiplication operator
     */
    friend vec4 operator *(const float& a, const vec4& b);

    /**
     * Component-wise multiplication operator
     */
    friend vec4 operator *(const vec4& a, const float& b);

    /**
     * Component-wise division operator
     */
    friend vec4 operator /(const vec4& a, const vec4& b);

    /**
     * Component-wise division operator
     */
    friend vec4 operator /(const float& a, const vec4& b);

    /**
     * Component-wise division operator
     */
    friend vec4 operator /(const vec4& a, const float& b);

    /**
     * Component-wise equality operator
     */
    bvec4 operator ==(const vec4& other) const;

    /**
     * Component-wise inequality operator
     */
    bvec4 operator !=(const vec4& other) const;

    /**
     * Component-wise less than operator
     */
    bvec4 operator <(const vec4& other) const;

    /**
     * Component-wise greater than operator
     */
    bvec4 operator >(const vec4& other) const;

    /**
     * Component-wise less than or equal to operator
     */
    bvec4 operator <=(const vec4& other) const;

    /**
     * Component-wise greater than or equal to operator
     */
    bvec4 operator >=(const vec4& other) const;

    /**
     * Component-wise addition assignment operator
     */
    vec4& operator +=(const vec4& other);

    /**
     * Component-wise addition assignment operator
     */
    vec4& operator +=(const float& other);

    /**
     * Component-wise subtraction assignment operator
     */
    vec4& operator -=(const vec4& other);

    /**
     * Component-wise subtraction assignment operator
     */
    vec4& operator -=(const float& other);

    /**
     * Component-wise multiplication assignment operator
     */
    vec4& operator *=(const vec4& other);

    /**
     * Component-wise multiplication assignment operator
     */
    vec4& operator *=(const float& other);

    /**
     * Component-wise division assignment operator
     */
    vec4& operator /=(const vec4& other);

    /**
     * Component-wise division assignment operator
     */
    vec4& operator /=(const float& other);

    /**
     * Component-wise increment operator
     */
    vec4& operator ++();

    /**
     * Component-wise decrement operator
     */
    vec4& operator --();

    #pragma endregion overloads

    #pragma region vector operations

    /**
     * Returns a vector in the same direction as this vector, but with a length of 1
     * @return Normalized vector
     */
    vec4 normalized() const;

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

    #pragma endregion vector operations
};

/**
 * Dot product of two vectors
 * @param a first vector
 * @param b second vector
 * @return Dot product of the two vectors
 */
float dot(const vec4& a, const vec4& b);

/**
 * Angle between two vectors
 * @param a first vector
 * @param b second vector
 * @return Angle between the two vectors in radians
 */
double angleBetween(const vec4& a, const vec4& b);

/**
 * Reflects incident vector, `I`, over surface with normal, `N`
 * @param I incident vector
 * @param N surface normal
 * @return Reflected vector
 * @note Input does not need to be normalized
 */
vec4 reflect(const vec4& I, const vec4& N);

/**
 * Returns the squared distance between two vectors
 * @param a first vector
 * @param b second vector
 * @return Squared distance from `a` to `b`
 * @note This is faster than `vec2::distance(a, b)` by one square root operation
 */
float distanceSquared(const vec4& a, const vec4& b);

/**
 * Returns the distance between two vectors
 * @param a first vector
 * @param b second vector
 * @return Distance from `a` to `b`
 */
float distance(const vec4& a, const vec4& b);

/**
 * Converts a vector to a string
 * @note Format is `[x, y, ...]`
 */
std::string to_string(const vec4& vec);

}

#endif
