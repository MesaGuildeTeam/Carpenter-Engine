#ifndef ENGINE_MAT3
#define ENGINE_MAT3


#include "Vector.hpp"
#include "vec3.hpp"
#include "vec3b.hpp"

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

}

namespace std {

/**
 * converts a matrix to a string
 * note: matrix is printed in column-major order
 */
std::string to_string(const Engine::mat3& mat);

}

#endif