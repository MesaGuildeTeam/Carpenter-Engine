#ifndef ENGINE_VECTORCOMMON
#define ENGINE_VECTORCOMMON

#include <array>
#include <string>
#include <iostream>

namespace Engine {

    class vec2;
    class vec3;
    class vec4;
    class bvec2;
    class bvec3;
    class bvec4;
    class mat2;
    class mat3;
    class mat4;

    // has a true value if a type is a float vector
    template <typename T>
    struct is_vecf : std::false_type {};
    // has a true value if a type is a float vector
    template <typename T>
    requires (std::is_same_v<T, vec2> || std::is_same_v<T, vec3> || std::is_same_v<T, vec4>)
    struct is_vecf<T> : std::true_type {};

    // has a true value if a type is a bool vector
    template <typename T>
    struct is_vecb : std::false_type {};
    // has a true value if a type is a bool vector
    template <typename T>
    requires (std::is_same_v<T, bvec2> || std::is_same_v<T, bvec3> || std::is_same_v<T, bvec4>)
    struct is_vecf<T> : std::true_type {};

    // has a true value if a type is a vector
    template <typename T>
    struct is_vec : std::false_type {};
    // has a true value if a type is a vector
    template <typename T>
    requires (is_vecb<T>::value || is_vecf<T>::value)
    struct is_vec<T> : std::true_type {};

    // has a true value if a type is a float matrix
    template <typename T>
    struct is_matf : std::false_type {};
    // has a true value if a type is a float matrix
    template <typename T>
    requires (std::is_same_v<T, mat2> || std::is_same_v<T, mat3> || std::is_same_v<T, mat4>)
    struct is_matf<T> : std::true_type {};

    // has a true value if a type is a matrix
    template <typename T>
    struct is_mat : std::false_type {};
    // has a true value if a type is a matrix
    template <typename T>
    requires (is_matf<T>::value)
    struct is_mat<T> : std::true_type {};

    // true if a type is a float vector
    template <typename T>
    constexpr bool is_vecf_v = is_vecf<T>::value;

    // true if a type is a bool vector
    template <typename T>
    constexpr bool is_vecb_v = is_vecb<T>::value;

    // true if a type is a vector
    template <typename T>
    constexpr bool is_vec_v = is_vec<T>::value;

    // true if a type is a float matrix
    template <typename T>
    constexpr bool is_matf_v = is_matf<T>::value;

    // true if a type is a matrix
    template <typename T>
    constexpr bool is_mat_v = is_mat<T>::value;

    /**
     * returns the dimension of a vector, matrix, or scalar type
     */
    template <typename T>
    struct dimension_of : std::integral_constant<unsigned int, 1> {};
    /**
     * returns the dimension of a vector, matrix, or scalar type
     */
    template <typename T>
    requires (std::is_same_v<T, vec2> || std::is_same_v<T, bvec2>)
    struct dimension_of<T> : std::integral_constant<unsigned int, 2> {};
    /**
     * returns the dimension of a vector, matrix, or scalar type
     */
    template <typename T>
    requires (std::is_same_v<T, vec3> || std::is_same_v<T, bvec3>)
    struct dimension_of<T> : std::integral_constant<unsigned int, 3> {};
    /**
     * returns the dimension of a vector, matrix, or scalar type
     */
    template <typename T>
    requires (std::is_same_v<T, vec4> || std::is_same_v<T, bvec4>)
    struct dimension_of<T> : std::integral_constant<unsigned int, 4> {};
    /**
     * the dimension of a vector, matrix, or scalar type
     */
    template <typename T>
    constexpr unsigned int dimension_of_v = dimension_of<T>::value;
}

#endif