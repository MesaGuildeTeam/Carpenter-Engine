#ifndef ENGINE_MATRIX
#define ENGINE_MATRIX

#include <array>
#include <string>
#include <iostream>
#include "Vector.hpp"

namespace Engine {

class mat3;

/**
 * An MxN column-major matrix of float
 */
class mat3 {
    private:
    // components
    std::array<vec3, 3> data;

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
    static constexpr unsigned int dimension = 3;

    #pragma endregion constants

    #pragma region constructors

    /**
     * Default constructor
     * Initializes all components to 0
     */
    mat3();

    /**
     * Fill constructor
     * Fills the matrix diagonal with the provided value
     * The remaining components are set to 0
     */
    template <typename T>
    requires (std::is_convertible_v<T, float>)
    mat3(T value) {
        data.fill(0);
        for (unsigned int i = 0; i < 3; i++) {
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
    requires ((std::is_convertible_v<Vectors, float> || isVec<Vectors>) && ...)
    mat3(const Vectors... vecs) {
        constexpr unsigned int sum = ((std::is_convertible_v<Vectors, float> ? 1 : isVec<Vectors> ? Vectors::dimension : dimension*dimension + 1) + ...);
        static_assert(sum == dimension*dimension, "Total number of components must equal " + std::to_string(dimension*dimension));

        unsigned int i = 0;
        unsigned int j = 0;
        ([&] {
            if constexpr (isVec<Vectors>) {
                for (unsigned int i = 0; i < Vectors::dimension; i++) {
                    data[j][i] = float(vecs[i]);
                    if (i == dimension - 1) {
                        j++;
                        i = 0;
                    } else {
                        i++;
                    }
                }
            } else {
                data[j][i] = float(vecs);
                if (i == dimension - 1) {
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
    static std::array<float,9> flatten(const mat3& mat);

    /**
     * unrolls the matrix in column major order (elements in the same column are adjacent in memory)
     */
    std::array<float,9> flatten() const;

    /**
     * unrolls the matrix in row major order (elements in the same row are adjacent in memory)
     */
    static std::array<float,9> flatten_row(const mat3& mat);

    /**
     * unrolls the matrix in row major order (elements in the same row are adjacent in memory)
     */
    std::array<float,9> flatten_row() const;

    /**
     * casts a matrix to a bool
     * true if all components are non-zero
     * to check if any components are non-zero, compare with vec4::zero rather than casting
     */
    explicit operator bool() const;

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
     * Row major matrix multiplication
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

}

namespace std {
    /**
     * converts a matrix to a string
     * note: matrix is printed in column-major order
     */
    std::string to_string(const Engine::mat3& mat);

}

#endif