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
     * vector of all falses
     */
    static const vec4b zero;
    /**
     * vector of all trues
     */
    static const vec4b one;

    /**
     * dimension of vector
     */
    static constexpr unsigned int dimension = 4;

    #pragma endregion constants

    #pragma region constructors

    /**
     * default constructor, fills the vector with false
     */
    vec4b();

    /**
     * fill constructor, fills the vector with the provided scalar value
     */
    template <typename T>
    requires std::is_convertible_v<T, bool>
    vec4b(T a){
        data.fill(bool(a));
    }

    /**
     * concatenation constructor
     * creates a vector from a list of vectors and scalars of a convertible type and of total dimensions summing to the target dimension
     */
    template <typename ... Vectors>
    requires ((is_vec_v<Vectors> || std::is_convertible_v<Vectors, bool>) && ... ) && ((dimension_of_v<Vectors> + ...) == dimension)
    vec4b(Vectors... vecs) {
        unsigned int i = 0;
        ([&] {
            if constexpr (is_vec_v<Vectors>) {
                for (unsigned int i = 0; i < Vectors::dimension; i++) {
                    data[i] = bool(vecs[i]);
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
     * casts a vector to a bool
     * true if all components are non-zero
     * to check if any components are non-zero, compare with vec4b::zero rather than casting
     */
    operator bool() const;

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
     * stream insertion operator
     */
    friend std::ostream& operator <<(std::ostream& os, const vec4b& vec);

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

}

namespace std {

/**
 * converts a vector to a string
 */
std::string to_string(const Engine::vec4b& vec);

}

#endif
