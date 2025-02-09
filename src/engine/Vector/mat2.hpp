#ifndef ENGINE_MAT2
#define ENGINE_MAT2


#include "Vector.hpp"
#include "vec2.hpp"
#include "bvec2.hpp"

namespace Engine {

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
     * Identity matrix
     * Equivalent to `mat2(1)`
     */
    static const mat2 identity;
    /**
     * Matrix of all zeros
     * Equivalent to `mat2(0)`
     */
    static const mat2 zero;
    /**
     * Matrix of all ones
     */
    static const mat2 one;

    /**
     * Dimension of the matrix
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
     * @param mat matrix to copy
     */
    mat2(const mat2& mat);

    /**
     * Fill constructor
     * Fills the matrix diagonal with the provided value
     * The remaining components are set to 0
     * @param value value to fill the diagonal with
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
     * @param vecs list of vectors and scalars
     * @warning vectors and floats are inserted as columns. This means that `mat2(1,2,3,4)` creates the matrix with columns [1,2] and [3,4]
     */
    template <typename ... Vectors>
    requires ((is_vec_v<Vectors> || std::is_convertible_v<Vectors, float>) && ... ) && ((dimension_of_v<Vectors> + ...) == dimension*dimension)
    mat2(const Vectors... vecs) {
        unsigned int i = 0;
        unsigned int j = 0;
        ([&] {
            if constexpr (is_vec_v<Vectors>) {
                for (unsigned int k = 0; k < Vectors::dimension; k++) {
                    data[j][i] = float(vecs[k]);
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
     * Column accessor, 0-indexed
     */
    vec2& operator [](unsigned int i);

    /**
     * Column accessor, 0-indexed
     */
    const vec2& operator [](unsigned int i) const;

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

    #pragma region conversions

    /**
     * Unrolls the matrix in column major order (elements in the same column are adjacent in memory)
     * @param mat matrix to flatten
     * @return array with values from matrix flattened
     */
    static std::array<float,N*N> flatten(const mat2& mat);

    /**
     * Unrolls the matrix in column major order (elements in the same column are adjacent in memory)
     * @return array with values from matrix flattened
     */
    std::array<float,N*N> flatten() const;

    /**
     * Unrolls the matrix in row major order (elements in the same row are adjacent in memory)
     * @param mat matrix to flatten
     * @return array with values from matrix flattened
     */
    static std::array<float,N*N> flatten_row(const mat2& mat);

    /**
     * Unrolls the matrix in row major order (elements in the same row are adjacent in memory)
     * @return array with values from matrix flattened
     */
    std::array<float,N*N> flatten_row() const;

    /**
     * Casts a matrix to a bool
     * True if **all** components are non-zero
     * @note To check if **any** components are non-zero, use `mat != mat2::zero`
     */
    operator bool() const;

    #pragma endregion conversions

    #pragma region overloads

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
     * Component-wise equality
     * true is all components are equal
     */
    friend bool operator ==(const mat2& a, const mat2& b);

    /**
     * Component-wise inequality
     * true is any component is not equal
     */
    friend bool operator !=(const mat2& a, const mat2& b);

    /**
     * Component-wise addition assignment operator
     */
    mat2& operator +=(const mat2& mat);

    /**
     * Component-wise addition assignment operator
     */
    mat2& operator +=(const float& a);

    /**
     * Component-wise subtraction assignment operator
     */
    mat2& operator -=(const mat2& mat);
    
    /**
     * Component-wise subtraction assignment operator
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
     * Component-wise increment
     */
    mat2& operator ++();

    /**
     * Component-wise decrement
     */
    mat2& operator --();

    #pragma endregion overloads

    #pragma region matrix operations

    /**
     * Returns the determinant of this matrix
     * @return determinant of this matrix
     */
    float determinant() const;

    /**
     * Returns the transpose of this matrix
     * @return transpose of this matrix
     */
    mat2 transpose() const;

    /**
     * Returns the inverse of this matrix
     * @return inverse of this matrix
     */
    mat2 inverse() const;

    /**
     * Returns the trace of this matrix (sum of diagonal elements)
     * @return trace of this matrix
     */
    float trace() const;

    #pragma endregion matrix operations
};

/**
 * Returns a 2d rotation matrix of some angle
 * @param angle the angle of the rotation in radians
 * @return A 2d rotation matrix of `angle` radians
 */
mat2 rotation(const float& angle);

/**
 * Returns a scale matrix
 * @param scale the scale vector
 * @return A 2d scale matrix
 * @note Equaivalent to component-wise vector multiplication
 */
mat2 scale(const vec2& scale);

/**
 * Returns an orthonormal basis matrix from one vector (assumed to be the x axis)
 * @param x the x axis, assumed to be normalized
 * @return A 2d basis matrix
 */
mat2 basis(const vec2& x);

/**
 * Converts a matrix to a string
 * @note The matrix is printed in column-major order
 */
std::string to_string(const mat2& mat);

}

#endif