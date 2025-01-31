#ifndef ENGINE_VEC4B
#define ENGINE_VEC4B

#include "Vector.hpp"
#include "vec4.hpp"

namespace Engine {

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
     * Vector of all falses
     */
    static const vec4b zero;
    /**
     * Vector of all trues
     */
    static const vec4b one;

    /**
     * Dimension of vector
     */
    static constexpr unsigned int dimension = 4;

    #pragma endregion constants

    #pragma region constructors

    /**
     * Default constructor, fills the vector with false
     */
    vec4b();

    /**
     * Fill constructor, fills the vector with the provided scalar value
     * @param a scalar to fill with
     */
    template <typename T>
    requires std::is_convertible_v<T, bool>
    vec4b(T a){
        data.fill(bool(a));
    }

    /**
     * Concatenation constructor
     * Creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
     * @param vecs list of vectors or scalars
     * @note `vec4(vec2(1,2), 3, 4) == vec4(1, 2, 3, 4)`
     */
    template <typename ... Vectors>
    requires ((is_vec_v<Vectors> || std::is_convertible_v<Vectors, bool>) && ... ) && ((dimension_of_v<Vectors> + ...) == dimension)
    vec4b(Vectors... vecs) {
        unsigned int i = 0;
        ([&] {
            if constexpr (is_vec_v<Vectors>) {
                for (unsigned int j = 0; j < Vectors::dimension; j++) {
                    data[i] = bool(vecs[j]);
                    i++;
                }
            } else {
                data[i] = bool(vecs);
                i++;
            }
        }(), ...);
    }

    #pragma endregion constructors

    #pragma region conversions

    /**
     * Casts a vector to a bool
     * True if all components are non-zero
     * To check if any components are non-zero, compare with `vec4b::zero` rather than casting
     */
    operator bool() const;

    /**
     * Casts a float vector to a boolean vector
     * @param vec float vector
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
     * @note Equivalent to `vec[0]`
     */
    bool& x = data[0];
    /**
     * The 2nd component of the vector
     * @note Equivalent to `vec[1]`
     */
    bool& y = data[1];
    /**
     * The 3rd component of the vector
     * @note Equivalent to `vec[2]`
     */
    bool& z = data[2];
    /**
     * The 4th component of the vector
     * @note Equivalent to `vec[3]`
     */
    bool& w = data[3];

    // color
    /**
     * The 1st component of the vector
     * @note Equivalent to `vec[0]`
     */
    bool& r = data[0];
    /**
     * The 2nd component of the vector
     * @note Equivalent to `vec[1]`
     */
    bool& g = data[1];
    /**
     * The 3rd component of the vector
     * @note Equivalent to `vec[2]`
     */
    bool& b = data[2];
    /**
     * The 4th component of the vector
     * @note Equivalent to `vec[3]`
     */
    bool& a = data[3];

    // texture coordinate
    /**
     * The 1st component of the vector
     * @note Equivalent to `vec[0]`
     */
    bool& u = data[0];
    /**
     * The 2nd component of the vector
     * @note Equivalent to `vec[1]`
     */
    bool& v = data[1];

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
    vec4b& operator =(const vec4b& other);

    /**
     * Component-wise and operator
     */
    friend vec4b operator &&(const vec4b& a, const vec4b& b);

    /**
     * Component-wise and operator
     */
    friend vec4b operator &&(const bool& a, const vec4b& b);

    /**
     * Component-wise and operator
     */
    friend vec4b operator &&(const vec4b& a, const bool& b);

    /**
     * Component-wise or operator
     */
    friend vec4b operator ||(const vec4b& a, const vec4b& b);

    /**
     * Component-wise or operator
     */
    friend vec4b operator ||(const bool& a, const vec4b& b);

    /**
     * Component-wise or operator
     */
    friend vec4b operator ||(const vec4b& a, const bool& b);

    /**
     * Component-wise not operator
     */
    vec4b operator !() const;

    /**
     * Component-wise equality operator
     */
    friend vec4b operator ==(const vec4b& a, const vec4b& b);

    /**
     * Component-wise inequality operator
     */
    friend vec4b operator !=(const vec4b& a, const vec4b& b);

    #pragma endregion overloads

    #pragma region vector operations

    /**
     * Returns if any component is true
     * @return `true` if any component is true, `false` otherwise
     */
    bool any() const;

    /**
     * Returns if all components are true
     * @return `true` if all components are true, `false` otherwise
     */
    bool all() const;

    /**
     * Returns the number of true components
     * @return the number of true components
    */
    unsigned int count() const;

    #pragma endregion vector operations
};

/**
 * Converts a vector to a string
 * @note Format is `[x, y, ...]`
 */
std::string to_string(const vec4b& vec);

}

#endif
