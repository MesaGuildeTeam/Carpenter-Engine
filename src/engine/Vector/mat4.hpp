#ifndef ENGINE_MAT4
#define ENGINE_MAT4

#include "Vector.hpp"
#include "vec4.hpp"
#include "vec4b.hpp"

namespace Engine {

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
     * Identity matrix
     * Equivalent to `mat4(1)`
     */
    static const mat4 identity;
    /**
     * Matrix of all zeros
     * Equivalent to `mat4(0)`
     */
    static const mat4 zero;
    /**
     * Matrix of all ones
     */
    static const mat4 one;

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
    mat4();

    /**
     * Copy constructor
     * @param mat Matrix to copy
     */
    mat4(const mat4& mat);

    /**
     * Fill constructor
     * Fills the matrix diagonal with the provided value
     * The remaining components are set to 0
     * @param value value to fill the diagonal with
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
     * @param vecs list of vectors and scalars
     * @warning vectors and floats are inserted as columns. This means that `mat2(1,2,3,4)` creates the matrix with columns [1,2] and [3,4]
     */
    template <typename ... Vectors>
    requires ((is_vec_v<Vectors> || std::is_convertible_v<Vectors, float>) && ... ) && ((dimension_of_v<Vectors> + ...) == dimension*dimension)
    mat4(const Vectors... vecs) {
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
    vec4& operator [](unsigned int i);

    /**
     * Column accessor, 0-indexed 
     */
    const vec4& operator [](unsigned int i) const;

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
    static std::array<float,N*N> flatten(const mat4& mat);

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
    static std::array<float,N*N> flatten_row(const mat4& mat);

    /**
     * Unrolls the matrix in row major order (elements in the same row are adjacent in memory)
     * @return array with values from matrix flattened
     */
    std::array<float,N*N> flatten_row() const;

    /**
     * Casts a matrix to a bool
     * True if **all** components are non-zero
     * @note To check if **any** components are non-zero, use `mat != mat4::zero`
     */
    operator bool() const;

    #pragma endregion conversions

    #pragma region overloads

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
     * Component-wise equality
     * true is all components are equal
     */
    friend bool operator ==(const mat4& a, const mat4& b);

    /**
     * Component-wise inequality
     * true is any component is not equal
     */
    friend bool operator !=(const mat4& a, const mat4& b);

    /**
     * Component-wise addition assignment operator
     */
    mat4& operator +=(const mat4& mat);

    /**
     * Component-wise addition assignment operator
     */
    mat4& operator +=(const float& a);

    /**
     * Component-wise subtraction assignment operator
     */
    mat4& operator -=(const mat4& mat);
    
    /**
     * Component-wise subtraction assignment operator
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
     * Component-wise increment
     */
    mat4& operator ++();

    /**
     * Component-wise decrement
     */
    mat4& operator --();

    #pragma endregion overloads

    #pragma region matrix operations

    
    /**
     * Returns the determinant of this matrix
     * @return Determinant of this matrix
     */
    //float determinant() const;

    /**
     * Returns the transpose of this matrix
     * @return Transpose of this matrix
     */
    mat4 transpose() const;

    /**
     * Returns the inverse of this matrix
     * @return Inverse of this matrix
     */
    //mat4 inverse() const;

    /**
     * Returns the trace of this matrix (sum of diagonal elements)
     * @return Trace of this matrix
     */
    float trace() const;

    #pragma endregion matrix operations
};

/**
 * Returns a skew matrix
 * @param skew the skew vector
 * @return A 3d skew matrix
 */
mat4 skew(const vec4& skew);

/**
 * Returns a scale matrix
 * Equaivalent to component-wise vector multiplication
 * @param scale the scale vector
 * @return A 4d scale matrix
 */
mat4 scale(const vec4& scale);

/**
 * Returns a basis matrix from 4 vectors
 * @param x the x basis vector
 * @param y the y basis vector
 * @param z the z basis vector
 * @param w the w basis vector
 * @return A 4d basis matrix
 * Equaivalent to just constructing from 4 vectors
 */
mat4 basis(const vec4& x, const vec4& y, const vec4& z, const vec4& w);
    
/**
 * Converts a matrix to a string
 * @note The matrix is printed in column-major order
 */
std::string to_string(const mat4& mat);

}

#endif