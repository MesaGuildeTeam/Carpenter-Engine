#ifndef ENGINE_VEC4
#define ENGINE_VEC4


#include "Vector.hpp"
#include "vec4b.hpp"

namespace Engine {

/**
 * 4d vector of float
 * Aka `vec4f`
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

    /**
     * dimension of vector
     */
    static constexpr unsigned int dimension = 4;

    #pragma endregion constants

    #pragma region constructors

    /**
     * default constructor, fills the vector with 0
     */
    vec4();

    /**
     * fill constructor, fills the vector with the provided scalar value
     */
    template <typename T>
    requires std::is_convertible_v<T, float>
    explicit vec4(const T a){
        data.fill(float(a));
    }

    /**
     * concatenation constructor
     * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
     */
    template <typename ... Vectors>
    requires ((is_vec_v<Vectors> || std::is_convertible_v<Vectors, float>) && ... ) && ((dimension_of_v<Vectors> + ...) == dimension)
    vec4(Vectors... vecs) {
        unsigned int i = 0;
        ([&] {
            if constexpr (is_vec_v<Vectors>) {
                for (unsigned int i = 0; i < Vectors::dimension; i++) {
                    data[i] = float(vecs[i]);
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
     * true if all components are non-zero
     * to check if any components are non-zero, compare with vec4::zero rather than casting
     */
    operator bool() const;

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
     * stream insertion operator
     */
    friend std::ostream& operator <<(std::ostream& os, const vec4& vec);

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
    vec4b operator ==(const vec4& other) const;

    /**
     * Component-wise inequality operator
     */
    vec4b operator !=(const vec4& other) const;

    /**
     * Component-wise less than operator
     */
    vec4b operator <(const vec4& other) const;

    /**
     * Component-wise greater than operator
     */
    vec4b operator >(const vec4& other) const;

    /**
     * Component-wise less than or equal to operator
     */
    vec4b operator <=(const vec4& other) const;

    /**
     * Component-wise greater than or equal to operator
     */
    vec4b operator >=(const vec4& other) const;

    /**
     * Component-wise addition assignment operator
     */
    vec4 operator +=(const vec4& other);

    /**
     * Component-wise addition assignment operator
     */
    vec4 operator +=(const float& other);

    /**
     * Component-wise subtraction assignment operator
     */
    vec4 operator -=(const vec4& other);

    /**
     * Component-wise subtraction assignment operator
     */
    vec4 operator -=(const float& other);

    /**
     * Component-wise multiplication assignment operator
     */
    vec4 operator *=(const vec4& other);

    /**
     * Component-wise multiplication assignment operator
     */
    vec4 operator *=(const float& other);

    /**
     * Component-wise division assignment operator
     */
    vec4 operator /=(const vec4& other);

    /**
     * Component-wise division assignment operator
     */
    vec4 operator /=(const float& other);

    /**
     * Component-wise increment operator
     */
    vec4 operator ++();

    /**
     * Component-wise decrement operator
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
     * reflects incident vector, I, over surface with normal, N
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

}

namespace std {

/**
 * converts a vector to a string
 */
std::string to_string(const Engine::vec4& vec);

}

#endif
