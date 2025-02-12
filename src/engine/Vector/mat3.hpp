#ifndef ENGINE_MAT3
#define ENGINE_MAT3


#include "Vector.hpp"
#include "vec3.hpp"
#include "bvec3.hpp"

namespace Engine {

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

    // forwards iterator
    using iterator = std::array<vec3,N>::iterator;
    // const forwards iterator
    using const_iterator = std::array<vec3,N>::const_iterator;
    // reverse iterator
    using reverse_iterator = std::array<vec3,N>::reverse_iterator;
    // const reverse iterator
    using const_reverse_iterator = std::array<vec3,N>::const_reverse_iterator;

    #pragma region constants

    /**
     * Identity matrix
     * Equivalent to `mat3(1)`
     */
    static const mat3 identity;
    /**
     * Matrix of all zeros
     * Equivalent to `mat3(0)`
     */
    static const mat3 zero;
    /**
     * Matrix of all ones
     */
    static const mat3 one;

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
    mat3();

    /**
     * Copy constructor
     * @param mat matrix to copy
     */
    mat3(const mat3& mat);

    /**
     * Fill constructor
     * Fills the matrix diagonal with the provided value
     * The remaining components are set to 0
     * @param value value to fill the diagonal with
     */
    template <typename T>
    requires (std::is_convertible_v<T, float>)
    explicit mat3(const T value) {
        data.fill(vec3(0));
        for (unsigned int i = 0; i < N; i++) {
            data[i][i] = float(value);
        }
    }

    //static_assert(std::is_convertible_v<mat3, float>);
    //static_assert(std::is_convertible_v<int, float>);
    //static_assert(is_vec_v<mat3>);

    template <typename ... Vectors>
    requires (std::is_convertible_v<Vectors, float> && ... )
    bool test(const Vectors... vecs) {
        return true;
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
    mat3(const Vectors... vecs) {
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
    vec3& operator [](unsigned int i);

    /**
     * Column accessor, 0-indexed 
     */
    const vec3& operator [](unsigned int i) const;

    #pragma endregion accessors

    #pragma region iteration

    /**
     * Iterator to the first component
     * @see [std::array::begin](https://en.cppreference.com/w/cpp/container/array/begin)
     */
    iterator begin() noexcept;

    /**
     * Iterator to the end of the components
     * @see [std::array::end](https://en.cppreference.com/w/cpp/container/array/end)
     */
    iterator end() noexcept;

    /**
     * Const iterator to the first component
     * @see [std::array::begin](https://en.cppreference.com/w/cpp/container/array/begin)
     */
    const_iterator begin() const noexcept;

    /**
     * Const iterator to the end of the components
     * @see [std::array::end](https://en.cppreference.com/w/cpp/container/array/end)
     */
    const_iterator end() const noexcept;

    /**
     * Const iterator to the first component
     * @see [std::array::cbegin](https://en.cppreference.com/w/cpp/container/array/cbegin)
     */
    const_iterator cbegin() const noexcept;

    /**
     * Const iterator to the end of the components
     * @see [std::array::cend](https://en.cppreference.com/w/cpp/container/array/cend)
     */
    const_iterator cend() const noexcept;

    /**
     * Reverse iterator to the first component
     * @see [std::array::rbegin](https://en.cppreference.com/w/cpp/container/array/rbegin)
     */
    reverse_iterator rbegin() noexcept;

    /**
     * Reverse iterator to the end of the components
     * @see [std::array::rend](https://en.cppreference.com/w/cpp/container/array/rend)
     */
    reverse_iterator rend() noexcept;

    /**
     * Const reverse iterator to the first component
     * @see [std::array::rbegin](https://en.cppreference.com/w/cpp/container/array/rbegin)
     */
    const_reverse_iterator rbegin() const noexcept;

    /**
     * Const reverse iterator to the end of the components
     * @see [std::array::rend](https://en.cppreference.com/w/cpp/container/array/rend)
     */
    const_reverse_iterator rend() const noexcept;

    /**
     * Const reverse iterator to the first component
     * @see [std::array::crbegin](https://en.cppreference.com/w/cpp/container/array/crbegin)
     */
    const_reverse_iterator crbegin() const noexcept;

    /**
     * Const reverse iterator to the end of the components
     * @see [std::array::crend](https://en.cppreference.com/w/cpp/container/array/crend)
     */
    const_reverse_iterator crend() const noexcept;

    #pragma endregion iteration

    #pragma region conversions

    /**
     * Unrolls the matrix in column major order (elements in the same column are adjacent in memory)
     * @param mat matrix to flatten
     * @return array with values from matrix flattened
     */
    static std::array<float,N*N> flatten(const mat3& mat);

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
    static std::array<float,N*N> flatten_row(const mat3& mat);

    /**
     * Unrolls the matrix in row major order (elements in the same row are adjacent in memory)
     * @return array with values from matrix flattened
     */
    std::array<float,N*N> flatten_row() const;

    /**
     * Casts a matrix to a bool
     * True if **all** components are non-zero
     * @note To check if **any** components are non-zero, use `mat != mat3::zero`
     */
    operator bool() const;

    #pragma endregion conversions

    #pragma region overloads

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
     * Component-wise equality
     * true is all components are equal
     */
    friend bool operator ==(const mat3& a, const mat3& b);

    /**
     * Component-wise inequality
     * true is any component is not equal
     */
    friend bool operator !=(const mat3& a, const mat3& b);

    /**
     * Component-wise addition assignment operator
     */
    mat3& operator +=(const mat3& mat);

    /**
     * Component-wise addition assignment operator
     */
    mat3& operator +=(const float& a);

    /**
     * Component-wise subtraction assignment operator
     */
    mat3& operator -=(const mat3& mat);
    
    /**
     * Component-wise subtraction assignment operator
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
     * Component-wise increment
     */
    mat3& operator ++();

    /**
     * Component-wise decrement
     */
    mat3& operator --();

    #pragma endregion overloads

    #pragma region matrix operations

    /**
     * Returns the determinant of this matrix
     * @return Determinant of this matrix
     */
    float determinant() const;

    /**
     * Returns the transpose of this matrix
     * @return Transpose of this matrix
     */
    mat3 transpose() const;

    /**
     * Returns the inverse of this matrix
     * Code modified from https://stackoverflow.com/a/18504573
     * @return Inverse of this matrix
     */
    mat3 inverse() const;

    /**
     * Returns the trace of this matrix (sum of diagonal elements)
     * @return Trace of this matrix
     */
    float trace() const;

    #pragma endregion matrix operations
};

/**
 * Returns a 3d rotation matrix of some angle about an axis
 * @param axis the axis of rotation, assumed to be normalized
 * @param angle the angle of the rotation in radians
 * @return A 3d rotation matrix of `angle` radians about `axis`
 */
mat3 rotation(const vec3& axis, const float& angle);

/**
 * Returns a 3d rotation matrix from a to b
 * @param a the first vector
 * @param b the second vector
 * @return A 3d rotation matrix of angle: `angleBetween(a,b)` radians, about axis: `cross(a,b)`, such that `rotation(a,b)*a = b`
 */
mat3 rotation(const vec3& a, const vec3& b);

/**
 * Returns a 3d rotation matrix about z then y then x
 * @param euler the euler angles of the rotation in radians
 * @return A 3d rotation matrix of `euler.x` radians about the x axis, `euler.y` radians about the y axis, and `euler.z` radians about the z axis
 */
mat3 rotation(const vec3& euler);

/**
 * Returns a 3d rotation matrix about the x axis
 * @param angle the angle of the rotation in radians
 * @return A 3d rotation matrix of `angle` radians about the x axis
 */
mat3 rotationX(const float& angle);

/**
 * Returns a 3d rotation matrix about the y axis
 * @param angle the angle of the rotation in radians
 * @return A 3d rotation matrix of `angle` radians about the y axis
 */
mat3 rotationY(const float& angle);

/**
 * Returns a 3d rotation matrix about the z axis
 * @param angle the angle of the rotation in radians
 * @return A 3d rotation matrix of `angle` radians about the z axis
 */
mat3 rotationZ(const float& angle);

/**
 * Returns a skew matrix
 * @param skew the skew vector
 * @return A 3d skew matrix
 */
mat3 skew(const vec3& skew);

/**
 * Returns a scale matrix
 * Equaivalent to component-wise vector multiplication
 * @param scale the scale vector
 * @return A 3d scale matrix
 */
mat3 scale(const vec3& scale);

/**
 * Returns a basis matrix from 2 vectors (assumed to be the `x` and `y` axies respectively)
 * The third vector is determined by the cross product of `x` and `y`
 * @param x the x axis, assumed to be normalized
 * @param y the y axis, assumed to be normalized, and orthogonal to `x`
 * @return A 3d basis matrix
 */
mat3 basis(const vec3& x, const vec3& y);

/**
 * Returns an orthonormal basis matrix from one vector (assumed to be the `z` axis)
 * The x axis is found using `vec3::tangent` and the y axis is the cross product of the x axis and `z`
 * @param z the z axis, assumed to be normalized
 * @return A 3d basis matrix
 */
mat3 basis(const vec3& z);

/**
 * Converts a matrix to a string
 * @note Column vectors are printed horizontally
 */
std::string to_string(const mat3& mat);

}

#endif