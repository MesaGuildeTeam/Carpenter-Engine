#ifndef ENGINE_VEC3
#define ENGINE_VEC3


#include "Vector.hpp"
#include "vec3b.hpp"

namespace Engine {

/**
 * 3d vector of float
 * Aka `vec3f`
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

    /**
     * dimension of vector
     */
    static constexpr unsigned int dimension = 3;

    #pragma endregion constants

    #pragma region constructors

    /**
     * default constructor, fills the vector with 0
     */
    vec3();

    /**
     * fill constructor, fills the vector with the provided scalar value
     */
    template <typename T>
    requires std::is_convertible_v<T, float>
    explicit vec3(const T a){
        data.fill(float(a));
    }

    /**
     * concatenation constructor
     * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
     */
    template <typename ... Vectors>
    requires ((is_vec_v<Vectors> || std::is_convertible_v<Vectors, float>) && ... ) && ((dimension_of_v<Vectors> + ...) == dimension)
    vec3(const Vectors... vecs) {
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
     * to check if any components are non-zero, compare with vec3::zero rather than casting
     */
    operator bool() const;

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
     * stream insertion operator
     */
    friend std::ostream& operator <<(std::ostream& os, const vec3& vec);

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
    vec3b operator ==(const vec3& other) const;

    /**
     * Component-wise inequality operator
     */
    vec3b operator !=(const vec3& other) const;
    
    /**
     * Component-wise less than operator
     */
    vec3b operator <(const vec3& other) const;

    /**
     * Component-wise greater than operator
     */
    vec3b operator >(const vec3& other) const;

    /**
     * Component-wise less than or equal to operator
     */
    vec3b operator <=(const vec3& other) const;

    /**
     * Component-wise greater than or equal to operator
     */
    vec3b operator >=(const vec3& other) const;

    /**
     * Component-wise addition assignment operator
     */
    vec3 operator +=(const vec3& other);

    /**
     * Component-wise addition assignment operator
     */
    vec3 operator +=(const float& other);

    /**
     * Component-wise subtraction assignment operator
     */
    vec3 operator -=(const vec3& other);

    /**
     * Component-wise subtraction assignment operator
     */
    vec3 operator -=(const float& other);

    /**
     * Component-wise multiplication assignment operator
     */
    vec3 operator *=(const vec3& other);

    /**
     * Component-wise multiplication assignment operator
     */
    vec3 operator *=(const float& other);

    /**
     * Component-wise division assignment operator
     */
    vec3 operator /=(const vec3& other);

    /**
     * Component-wise division assignment operator
     */
    vec3 operator /=(const float& other);

    /**
     * Component-wise increment operator
     */
    vec3 operator ++();

    /**
     * Component-wise decrement operator
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
     * reflects incident vector, I, over surface with normal, N
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

}

namespace std {

/**
 * converts a vector to a string
 */
std::string to_string(const Engine::vec3& vec);

}

#endif
