#ifndef ENGINE_MATRIX
#define ENGINE_MATRIX

#include <array>
#include <string>
#include <iostream>
#include "Vector.hpp"

namespace Engine {

class mat4;
class mat3;
class mat2;

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

/**
 * templated mat type (float) for selecting the matrix size at compile time
 */
template <unsigned int N>
struct mat {
    static_assert(N == 2 || N == 3 || N == 4, "Supported matrix dimensions are 2, 3 and 4");
    using type = std::conditional_t<N == 2, mat2, std::conditional_t<N == 3, mat3, mat4>>;
};

/**
 * A 4x4 column-major matrix of float
 */
typedef mat4 mat4x4;
/**
 * A 4x4 column-major matrix of float
 */
typedef mat4 mat4f;
/**
 * A 4x4 column-major matrix of float
 */
typedef mat4 mat4x4f;

/**
 * A 3x3 column-major matrix of float
 */
typedef mat3 mat3x3;
/**
 * A 3x3 column-major matrix of float
 */
typedef mat3 mat3f;
/**
 * A 3x3 column-major matrix of float
 */
typedef mat3 mat3x3f;

/**
 * A 2x2 column-major matrix of float
 */
typedef mat2 mat2x2;
/**
 * A 2x2 column-major matrix of float
 */
typedef mat2 mat2f;
/**
 * A 2x2 column-major matrix of float
 */
typedef mat2 mat2x2f;

/**
 * A 4x4 column-major matrix of float
 */
class mat4 {

    private:
    // dimensions
    static constexpr unsigned int N = 4;

    // components
    std::array<vec4, N> data;

    public:

    #pragma region constants

    /**
     * identity matrix
     * equivalent to `mat4(1)`
     */
    static const mat4 identity;
    /**
     * matrix of all zeros
     * equivalent to `mat4(0)`
     */
    static const mat4 zero;
    /**
     * matrix of all ones
     */
    static const mat4 one;

    /**
     * dimension of the matrix
     */
    static constexpr unsigned int dimension = N;

    #pragma endregion constants

    #pragma region constructors

    /**
     * Default constructor
     * Initializes all components to 0
     */
    mat4();

    /**
     * Copy constructor
     */
    mat4(const mat4& mat);

    /**
     * Fill constructor
     * Fills the matrix diagonal with the provided value
     * The remaining components are set to 0
     */
    template <typename T>
    requires (std::is_convertible_v<T, float>)
    explicit mat4(const T value) {
        data.fill(vec4(0));
        for (unsigned int i = 0; i < N; i++) {
            data[i][i] = float(value);
        }
    }

    /**
     * Concatenation constructor
     * Creates a matrix from a list of convertable vector and scalar types
     * Total dimension of input vectors must be 9
     * @warning vectors and floats are inserted as columns. This means that `mat2(1,2,3,4)` creates the matrix with columns [1,2] and [3,4]
     */
    template <typename ... Vectors>
    requires ((is_vec_v<Vectors> || std::is_convertible_v<Vectors, float>) && ... ) && ((dimension_of_v<Vectors> + ...) == dimension*dimension)
    mat4(const Vectors... vecs) {
        unsigned int i = 0;
        unsigned int j = 0;
        ([&] {
            if constexpr (is_vec_v<Vectors>) {
                for (unsigned int i = 0; i < Vectors::dimension; i++) {
                    data[j][i] = float(vecs[i]);
                    if (i == N - 1) {
                        j++;
                        i = 0;
                    } else {
                        i++;
                    }
                }
            } else {
                data[j][i] = float(vecs);
                if (i == N - 1) {
                    j++;
                    i = 0;
                } else {
                    i++;
                }
            }
        }(), ...);
    }

    #pragma endregion constructors

    #pragma region accessors

    /**
     * Column accessor
     */
    vec4& operator [](unsigned int i);

    /**
     * Column accessor 
     */
    const vec4& operator [](unsigned int i) const;

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

    #pragma region conversions

    /**
     * unrolls the matrix in column major order (elements in the same column are adjacent in memory)
     */
    static std::array<float,N*N> flatten(const mat4& mat);

    /**
     * unrolls the matrix in column major order (elements in the same column are adjacent in memory)
     */
    std::array<float,N*N> flatten() const;

    /**
     * unrolls the matrix in row major order (elements in the same row are adjacent in memory)
     */
    static std::array<float,N*N> flatten_row(const mat4& mat);

    /**
     * unrolls the matrix in row major order (elements in the same row are adjacent in memory)
     */
    std::array<float,N*N> flatten_row() const;

    /**
     * casts a matrix to a bool
     * true if all components are non-zero
     * to check if any components are non-zero, compare with vec4::zero rather than casting
     */
    operator bool() const;

    #pragma endregion conversions

    #pragma region overloads

    /**
     * stream insertion operator
     * note: matrix is printed in column-major order
     */
    friend std::ostream& operator <<(std::ostream& os, const mat4& mat);

    /**
     * Copy assignment operator
     */
    mat4& operator =(const mat4& other);

    /**
     * Component-wise addition
     */
    friend mat4 operator +(const mat4& a, const mat4& b);

    /**
     * Component-wise addition
     */
    friend mat4 operator +(const float& a, const mat4& b);

    /**
     * Component-wise addition
     */
    friend mat4 operator +(const mat4& a, const float& b);

    /**
     * Component-wise subtraction
     */
    friend mat4 operator -(const mat4& a, const mat4& b);

    /**
     * Component-wise subtraction
     */
    friend mat4 operator -(const float& a, const mat4& b);

    /**
     * Component-wise subtraction
     */
    friend mat4 operator -(const mat4& a, const float& b);

    /**
     * Component-wise negation
     */
    mat4 operator -() const;

    /**
     * Column major matrix multiplication
     */
    friend mat4 operator *(const mat4& a, const mat4& b);

    /**
     * Column major matrix multiplication
     */
    friend vec4 operator *(const mat4& a, const vec4& b);

    /**
     * Scalar multiplication (component-wise)
     */
    friend mat4 operator *(const float& a, const mat4& b);

    /**
     * Scalar multiplication (component-wise)
     */
    friend mat4 operator *(const mat4& a, const float& b);

    /**
     * component-wise equality
     * true is all components are equal
     */
    friend bool operator ==(const mat4& a, const mat4& b);

    /**
     * component-wise inequality
     * true is any component is not equal
     */
    friend bool operator !=(const mat4& a, const mat4& b);

    /**
     * component-wise addition assignment operator
     */
    mat4& operator +=(const mat4& mat);

    /**
     * component-wise addition assignment operator
     */
    mat4& operator +=(const float& a);

    /**
     * component-wise subtraction assignment operator
     */
    mat4& operator -=(const mat4& mat);
    
    /**
     * component-wise subtraction assignment operator
     */
    mat4& operator -=(const float& a);

    /**
     * Column major matrix multiplication assignment operator
     */
    mat4& operator *=(const mat4& mat);

    /**
     * Scalar multiplication assignment operator (component-wise)
     */
    mat4& operator *=(const float& a);

    /**
     * component-wise increment
     */
    mat4& operator ++();

    /**
     * component-wise decrement
     */
    mat4& operator --();

    #pragma endregion overloads

    #pragma region matrix operations

    
    /**
     * returns the determinant of this matrix
     */
    //float determinant() const;

    /**
     * returns the determinant of a matrix
     */
    //static float determinant(const mat4& mat);

    /**
     * returns the transpose of this matrix
     */
    mat4 transpose() const;

    /**
     * returns the transpose of a matrix
     */
    static mat4 transpose(const mat4& mat);

    /**
     * returns the inverse of this matrix
     * code modified from https://stackoverflow.com/a/18504573
     */
    //mat4 inverse() const;

    /**
     * returns the inverse of a matrix
     * code modified from https://stackoverflow.com/a/18504573
     */
    //static mat4 inverse(const mat4& mat);

    /**
     * returns the trace of this matrix (sum of diagonal elements)
     */
    float trace() const;

    /**
     * returns the trace of a matrix (sum of diagonal elements)
     */
    static float trace(const mat4& mat);

    /**
     * returns a skew matrix
     */
    static mat4 skew(const vec4& skew);

    /**
     * returns a scale matrix
     * equaivalent to component-wise vector multiplication
     */
    static mat4 scale(const vec4& scale);

    /**
     * returns a basis matrix from 4 vectors
     * equaivalent to just constructing from 4 vectors
     */
    static mat4 basis(const vec4& x, const vec4& y, const vec4& z, const vec4& w);

    #pragma endregion matrix operations
};

/**
 * A 3x3 column-major matrix of float
 */
class mat3 {

    private:
    // dimensions
    static constexpr unsigned int N = 3;

    // components
    std::array<vec3, N> data;

    public:

    #pragma region constants

    /**
     * identity matrix
     * equivalent to `mat3(1)`
     */
    static const mat3 identity;
    /**
     * matrix of all zeros
     * equivalent to `mat3(0)`
     */
    static const mat3 zero;
    /**
     * matrix of all ones
     */
    static const mat3 one;

    /**
     * dimension of the matrix
     */
    static constexpr unsigned int dimension = N;

    #pragma endregion constants

    #pragma region constructors

    /**
     * Default constructor
     * Initializes all components to 0
     */
    mat3();

    /**
     * Copy constructor
     */
    mat3(const mat3& mat);

    /**
     * Fill constructor
     * Fills the matrix diagonal with the provided value
     * The remaining components are set to 0
     */
    template <typename T>
    requires (std::is_convertible_v<T, float>)
    explicit mat3(const T value) {
        data.fill(vec3(0));
        for (unsigned int i = 0; i < N; i++) {
            data[i][i] = float(value);
        }
    }

    /**
     * Concatenation constructor
     * Creates a matrix from a list of convertable vector and scalar types
     * Total dimension of input vectors must be 9
     * @warning vectors and floats are inserted as columns. This means that `mat2(1,2,3,4)` creates the matrix with columns [1,2] and [3,4]
     */
    template <typename ... Vectors>
    requires ((is_vec_v<Vectors> || std::is_convertible_v<Vectors, float>) && ... ) && ((dimension_of_v<Vectors> + ...) == dimension*dimension)
    mat3(const Vectors... vecs) {
        unsigned int i = 0;
        unsigned int j = 0;
        ([&] {
            if constexpr (is_vec_v<Vectors>) {
                for (unsigned int i = 0; i < Vectors::dimension; i++) {
                    data[j][i] = float(vecs[i]);
                    if (i == N - 1) {
                        j++;
                        i = 0;
                    } else {
                        i++;
                    }
                }
            } else {
                data[j][i] = float(vecs);
                if (i == N - 1) {
                    j++;
                    i = 0;
                } else {
                    i++;
                }
            }
        }(), ...);
    }

    #pragma endregion constructors

    #pragma region accessors

    /**
     * Column accessor
     */
    vec3& operator [](unsigned int i);

    /**
     * Column accessor 
     */
    const vec3& operator [](unsigned int i) const;

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

    #pragma region conversions

    /**
     * unrolls the matrix in column major order (elements in the same column are adjacent in memory)
     */
    static std::array<float,N*N> flatten(const mat3& mat);

    /**
     * unrolls the matrix in column major order (elements in the same column are adjacent in memory)
     */
    std::array<float,N*N> flatten() const;

    /**
     * unrolls the matrix in row major order (elements in the same row are adjacent in memory)
     */
    static std::array<float,N*N> flatten_row(const mat3& mat);

    /**
     * unrolls the matrix in row major order (elements in the same row are adjacent in memory)
     */
    std::array<float,N*N> flatten_row() const;

    /**
     * casts a matrix to a bool
     * true if all components are non-zero
     * to check if any components are non-zero, compare with vec4::zero rather than casting
     */
    operator bool() const;

    #pragma endregion conversions

    #pragma region overloads

    /**
     * stream insertion operator
     * note: matrix is printed in column-major order
     */
    friend std::ostream& operator <<(std::ostream& os, const mat3& mat);

    /**
     * Copy assignment operator
     */
    mat3& operator =(const mat3& other);

    /**
     * Component-wise addition
     */
    friend mat3 operator +(const mat3& a, const mat3& b);

    /**
     * Component-wise addition
     */
    friend mat3 operator +(const float& a, const mat3& b);

    /**
     * Component-wise addition
     */
    friend mat3 operator +(const mat3& a, const float& b);

    /**
     * Component-wise subtraction
     */
    friend mat3 operator -(const mat3& a, const mat3& b);

    /**
     * Component-wise subtraction
     */
    friend mat3 operator -(const float& a, const mat3& b);

    /**
     * Component-wise subtraction
     */
    friend mat3 operator -(const mat3& a, const float& b);

    /**
     * Component-wise negation
     */
    mat3 operator -() const;

    /**
     * Column major matrix multiplication
     */
    friend mat3 operator *(const mat3& a, const mat3& b);

    /**
     * Column major matrix multiplication
     */
    friend vec3 operator *(const mat3& a, const vec3& b);

    /**
     * Scalar multiplication (component-wise)
     */
    friend mat3 operator *(const float& a, const mat3& b);

    /**
     * Scalar multiplication (component-wise)
     */
    friend mat3 operator *(const mat3& a, const float& b);

    /**
     * component-wise equality
     * true is all components are equal
     */
    friend bool operator ==(const mat3& a, const mat3& b);

    /**
     * component-wise inequality
     * true is any component is not equal
     */
    friend bool operator !=(const mat3& a, const mat3& b);

    /**
     * component-wise addition assignment operator
     */
    mat3& operator +=(const mat3& mat);

    /**
     * component-wise addition assignment operator
     */
    mat3& operator +=(const float& a);

    /**
     * component-wise subtraction assignment operator
     */
    mat3& operator -=(const mat3& mat);
    
    /**
     * component-wise subtraction assignment operator
     */
    mat3& operator -=(const float& a);

    /**
     * Column major matrix multiplication assignment operator
     */
    mat3& operator *=(const mat3& mat);

    /**
     * Scalar multiplication assignment operator (component-wise)
     */
    mat3& operator *=(const float& a);

    /**
     * component-wise increment
     */
    mat3& operator ++();

    /**
     * component-wise decrement
     */
    mat3& operator --();

    #pragma endregion overloads

    #pragma region matrix operations

    /**
     * returns the determinant of this matrix
     */
    float determinant() const;

    /**
     * returns the determinant of a matrix
     */
    static float determinant(const mat3& mat);

    /**
     * returns the transpose of this matrix
     */
    mat3 transpose() const;

    /**
     * returns the transpose of a matrix
     */
    static mat3 transpose(const mat3& mat);

    /**
     * returns the inverse of this matrix
     * code modified from https://stackoverflow.com/a/18504573
     */
    mat3 inverse() const;

    /**
     * returns the inverse of a matrix
     * code modified from https://stackoverflow.com/a/18504573
     */
    static mat3 inverse(const mat3& mat);

    /**
     * returns the trace of this matrix (sum of diagonal elements)
     */
    float trace() const;

    /**
     * returns the trace of a matrix (sum of diagonal elements)
     */
    static float trace(const mat3& mat);

    /**
     * returns a 3d rotation matrix of some angle about an axis
     */
    static mat3 rotation(const vec3& axis, const float& angle);

    /**
     * returns a 3d rotation matrix about z then y then x
     */
    static mat3 rotation(const vec3& euler);

    /**
     * returns a 3d rotation matrix about the x axis
     */
    static mat3 rotationX(const float& angle);

    /**
     * returns a 3d rotation matrix about the y axis
     */
    static mat3 rotationY(const float& angle);

    /**
     * returns a 3d rotation matrix about the z axis
     */
    static mat3 rotationZ(const float& angle);

    /**
     * returns a skew matrix
     */
    static mat3 skew(const vec3& skew);

    /**
     * returns a scale matrix
     * equaivalent to component-wise vector multiplication
     */
    static mat3 scale(const vec3& scale);

    /**
     * returns a basis matrix from 3 vectors
     * equaivalent to just constructing from 3 vectors
     */
    static mat3 basis(const vec3& x, const vec3& y, const vec3& z);

    /**
     * returns a basis matrix from 2 vectors (assumed to be the x and y axies respectively)
     * third vector is determined by the cross product of x and y
     */
    static mat3 basis(const vec3& x, const vec3& y);

    /**
     * returns a basis matrix from one vector (assumed to be the z axis)
     * the x axis is found using vec3::tangent and the y axis is the cross of x and z
     */
    static mat3 basis(const vec3& z);

    #pragma endregion matrix operations
};

/**
 * A 2x2 column-major matrix of float
 */
class mat2 {

    private:
    // dimensions
    static constexpr unsigned int N = 2;

    // components
    std::array<vec2, N> data;

    public:

    #pragma region constants

    /**
     * identity matrix
     * equivalent to `mat2(1)`
     */
    static const mat2 identity;
    /**
     * matrix of all zeros
     * equivalent to `mat2(0)`
     */
    static const mat2 zero;
    /**
     * matrix of all ones
     */
    static const mat2 one;

    /**
     * dimension of the matrix
     */
    static constexpr unsigned int dimension = N;

    #pragma endregion constants

    #pragma region constructors

    /**
     * Default constructor
     * Initializes all components to 0
     */
    mat2();

    /**
     * Copy constructor
     */
    mat2(const mat2& mat);

    /**
     * Fill constructor
     * Fills the matrix diagonal with the provided value
     * The remaining components are set to 0
     */
    template <typename T>
    requires (std::is_convertible_v<T, float>)
    explicit mat2(const T value) {
        data.fill(vec2(0));
        for (unsigned int i = 0; i < N; i++) {
            data[i][i] = float(value);
        }
    }

    /**
     * Concatenation constructor
     * Creates a matrix from a list of convertable vector and scalar types
     * Total dimension of input vectors must be 9
     * @warning vectors and floats are inserted as columns. This means that `mat2(1,2,3,4)` creates the matrix with columns [1,2] and [3,4]
     */
    template <typename ... Vectors>
    requires ((is_vec_v<Vectors> || std::is_convertible_v<Vectors, float>) && ... ) && ((dimension_of_v<Vectors> + ...) == dimension*dimension)
    mat2(const Vectors... vecs) {
        unsigned int i = 0;
        unsigned int j = 0;
        ([&] {
            if constexpr (is_vec_v<Vectors>) {
                for (unsigned int i = 0; i < Vectors::dimension; i++) {
                    data[j][i] = float(vecs[i]);
                    if (i == N - 1) {
                        j++;
                        i = 0;
                    } else {
                        i++;
                    }
                }
            } else {
                data[j][i] = float(vecs);
                if (i == N - 1) {
                    j++;
                    i = 0;
                } else {
                    i++;
                }
            }
        }(), ...);
    }

    #pragma endregion constructors

    #pragma region accessors

    /**
     * Column accessor
     */
    vec2& operator [](unsigned int i);

    /**
     * Column accessor 
     */
    const vec2& operator [](unsigned int i) const;

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

    #pragma region conversions

    /**
     * unrolls the matrix in column major order (elements in the same column are adjacent in memory)
     */
    static std::array<float,N*N> flatten(const mat2& mat);

    /**
     * unrolls the matrix in column major order (elements in the same column are adjacent in memory)
     */
    std::array<float,N*N> flatten() const;

    /**
     * unrolls the matrix in row major order (elements in the same row are adjacent in memory)
     */
    static std::array<float,N*N> flatten_row(const mat2& mat);

    /**
     * unrolls the matrix in row major order (elements in the same row are adjacent in memory)
     */
    std::array<float,N*N> flatten_row() const;

    /**
     * casts a matrix to a bool
     * true if all components are non-zero
     * to check if any components are non-zero, compare with vec4::zero rather than casting
     */
    operator bool() const;

    #pragma endregion conversions

    #pragma region overloads

    /**
     * stream insertion operator
     * note: matrix is printed in column-major order
     */
    friend std::ostream& operator <<(std::ostream& os, const mat2& mat);

    /**
     * Copy assignment operator
     */
    mat2& operator =(const mat2& other);

    /**
     * Component-wise addition
     */
    friend mat2 operator +(const mat2& a, const mat2& b);

    /**
     * Component-wise addition
     */
    friend mat2 operator +(const float& a, const mat2& b);

    /**
     * Component-wise addition
     */
    friend mat2 operator +(const mat2& a, const float& b);

    /**
     * Component-wise subtraction
     */
    friend mat2 operator -(const mat2& a, const mat2& b);

    /**
     * Component-wise subtraction
     */
    friend mat2 operator -(const float& a, const mat2& b);

    /**
     * Component-wise subtraction
     */
    friend mat2 operator -(const mat2& a, const float& b);

    /**
     * Component-wise negation
     */
    mat2 operator -() const;

    /**
     * Column major matrix multiplication
     */
    friend mat2 operator *(const mat2& a, const mat2& b);

    /**
     * Column major matrix multiplication
     */
    friend vec2 operator *(const mat2& a, const vec2& b);

    /**
     * Scalar multiplication (component-wise)
     */
    friend mat2 operator *(const float& a, const mat2& b);

    /**
     * Scalar multiplication (component-wise)
     */
    friend mat2 operator *(const mat2& a, const float& b);

    /**
     * component-wise equality
     * true is all components are equal
     */
    friend bool operator ==(const mat2& a, const mat2& b);

    /**
     * component-wise inequality
     * true is any component is not equal
     */
    friend bool operator !=(const mat2& a, const mat2& b);

    /**
     * component-wise addition assignment operator
     */
    mat2& operator +=(const mat2& mat);

    /**
     * component-wise addition assignment operator
     */
    mat2& operator +=(const float& a);

    /**
     * component-wise subtraction assignment operator
     */
    mat2& operator -=(const mat2& mat);
    
    /**
     * component-wise subtraction assignment operator
     */
    mat2& operator -=(const float& a);

    /**
     * Column major matrix multiplication assignment operator
     */
    mat2& operator *=(const mat2& mat);

    /**
     * Scalar multiplication assignment operator (component-wise)
     */
    mat2& operator *=(const float& a);

    /**
     * component-wise increment
     */
    mat2& operator ++();

    /**
     * component-wise decrement
     */
    mat2& operator --();

    #pragma endregion overloads

    #pragma region matrix operations

    /**
     * returns the determinant of this matrix
     */
    float determinant() const;

    /**
     * returns the determinant of a matrix
     */
    static float determinant(const mat2& mat);

    /**
     * returns the transpose of this matrix
     */
    mat2 transpose() const;

    /**
     * returns the transpose of a matrix
     */
    static mat2 transpose(const mat2& mat);

    /**
     * returns the inverse of this matrix
     */
    mat2 inverse() const;

    /**
     * returns the inverse of a matrix
     */
    static mat2 inverse(const mat2& mat);

    /**
     * returns the trace of this matrix (sum of diagonal elements)
     */
    float trace() const;

    /**
     * returns the trace of a matrix (sum of diagonal elements)
     */
    static float trace(const mat2& mat);

    /**
     * returns a 2d rotation matrix of some angle
     */
    static mat2 rotation(const float& angle);

    /**
     * returns a skew matrix
     */
    static mat2 skew(const vec2& skew);

    /**
     * returns a scale matrix
     * equaivalent to component-wise vector multiplication
     */
    static mat2 scale(const vec2& scale);

    /**
     * returns a basis matrix from 2 vectors
     * equaivalent to just constructing from 2 vectors
     */
    static mat2 basis(const vec2& x, const vec2& y);

    /**
     * returns a basis matrix from one vector (assumed to be the x axis)
     */
    static mat2 basis(const vec2& x);

    #pragma endregion matrix operations
};

}

namespace std {
    /**
     * converts a matrix to a string
     * note: matrix is printed in column-major order
     */
    std::string to_string(const Engine::mat4& mat);
    /**
     * converts a matrix to a string
     * note: matrix is printed in column-major order
     */
    std::string to_string(const Engine::mat3& mat);
    /**
     * converts a matrix to a string
     * note: matrix is printed in column-major order
     */
    std::string to_string(const Engine::mat2& mat);

}

#pragma endregion mat4

#endif