#ifndef ENGINE_VECTORCOMMON
#define ENGINE_VECTORCOMMON

#include <array>
#include <string>
#include <iostream>

namespace Engine {

    class vec2;
    class vec3;
    class vec4;
    class vec2b;
    class vec3b;
    class vec4b;
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
    requires (std::is_same_v<T, vec2b> || std::is_same_v<T, vec3b> || std::is_same_v<T, vec4b>)
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
    requires (std::is_same_v<T, vec2> || std::is_same_v<T, vec2b>)
    struct dimension_of<T> : std::integral_constant<unsigned int, 2> {};
    /**
     * returns the dimension of a vector, matrix, or scalar type
     */
    template <typename T>
    requires (std::is_same_v<T, vec3> || std::is_same_v<T, vec3b>)
    struct dimension_of<T> : std::integral_constant<unsigned int, 3> {};
    /**
     * returns the dimension of a vector, matrix, or scalar type
     */
    template <typename T>
    requires (std::is_same_v<T, vec4> || std::is_same_v<T, vec4b>)
    struct dimension_of<T> : std::integral_constant<unsigned int, 4> {};
    /**
     * the dimension of a vector, matrix, or scalar type
     */
    template <typename T>
    constexpr unsigned int dimension_of_v = dimension_of<T>::value;
    /**
     * returns the dimension of a vector, matrix, or scalar type
     */
    template <typename T>
    requires (std::is_same_v<T, mat2>)
    struct dimension_of<T> : std::integral_constant<unsigned int, 2> {};
    /**
     * returns the dimension of a vector, matrix, or scalar type
     */
    template <typename T>
    requires (std::is_same_v<T, mat3>)
    struct dimension_of<T> : std::integral_constant<unsigned int, 3> {};
    /**
     * returns the dimension of a vector, matrix, or scalar type
     */
    template <typename T>
    requires (std::is_same_v<T, mat4>)
    struct dimension_of<T> : std::integral_constant<unsigned int, 4> {};

    #if false
    /**
     * templated mat type (float) for selecting the matrix size at compile time
     */
    template <unsigned int N>
    struct mat {
        static_assert(N == 2 || N == 3 || N == 4, "Supported matrix dimensions are 2, 3 and 4");
        using type = std::conditional_t<N == 2, mat2, std::conditional_t<N == 3, mat3, mat4>>;
    };

    /**
     * templated vec type (float) for selecting the matrix size at compile time
     */
    template <unsigned int N>
    struct vec {
        static_assert(N == 2 || N == 3 || N == 4, "Supported vector dimensions are 2, 3 and 4");
        using type = std::conditional_t<N == 2, vec2, std::conditional_t<N == 3, vec3, vec4>>;
    };

    /**
     * templated vec type (bool) for selecting the vector type at compile time
     */
    template <unsigned int N>
    struct vecb {
        static_assert(N == 2 || N == 3 || N == 4, "Supported vector dimensions are 2, 3 and 4");
        using type = std::conditional_t<N == 2, vec2b, std::conditional_t<N == 3, vec3b, vec4b>>;
    };

    /**
     * templated vec type (float) for selecting the vector type at compile time
     */
    template <unsigned int N>
    using vecf = vec<N>;
    #endif

    /**
     * 4d vector of float
     * Aka `vec4`
     */
    typedef vec4 vec4f;
    /**
     * 3d vector of float
     * Aka `vec3`
     */
    typedef vec3 vec3f;
    /**
     * 2d vector of float
     * Aka `vec2`
     */
    typedef vec2 vec2f;

    /**
     * A 4x4 column-major matrix of float
     * Aka `mat4`, `mat4f`, `mat4x4f`
     */
    typedef mat4 mat4x4;
    /**
     * A 4x4 column-major matrix of float
     * Aka `mat4`, `mat4x4`, `mat4x4f`
     */
    typedef mat4 mat4f;
    /**
     * A 4x4 column-major matrix of float
     * Aka `mat4`, `mat4f`, `mat4x4`
     */
    typedef mat4 mat4x4f;

    /**
     * A 3x3 column-major matrix of float
     * Aka `mat3`, `mat3f`, `mat3x3f`
     */
    typedef mat3 mat3x3;
    /**
     * A 3x3 column-major matrix of float
     * Aka `mat3`, `mat3x3`, `mat3x3f`
     */
    typedef mat3 mat3f;
    /**
     * A 3x3 column-major matrix of float
     * Aka `mat3`, `mat3f`, `mat3x3`
     */
    typedef mat3 mat3x3f;

    /**
     * A 2x2 column-major matrix of float
     * Aka `mat2`, `mat2f`, `mat2x2f`
     */
    typedef mat2 mat2x2;
    /**
     * A 2x2 column-major matrix of float
     * Aka `mat2`, `mat2x2`, `mat2x2f`
     */
    typedef mat2 mat2f;
    /**
     * A 2x2 column-major matrix of float
     * Aka `mat2`, `mat2f`, `mat2x2`
     */
    typedef mat2 mat2x2f;
}

#endif