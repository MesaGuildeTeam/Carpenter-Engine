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
    mat3() {
        data.fill(0);
    }

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
    vec3& operator [](unsigned int i) {
        if (i >= 3) {
            throw std::out_of_range("Index out of range");
        }
        return data[i];
    }

    /**
     * Column accessor 
     */
    const vec3& operator [](unsigned int i) const {
        if (i >= 3) {
            throw std::out_of_range("Index out of range");
        }
        return data[i];
    }

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
    static std::array<float,9> flatten(const mat3& mat) {
        return {mat.data[0][0], mat.data[0][1], mat.data[0][2], mat.data[1][0], mat.data[1][1], mat.data[1][2], mat.data[2][0], mat.data[2][1], mat.data[2][2]};
    }

    /**
     * unrolls the matrix in column major order (elements in the same column are adjacent in memory)
     */
    std::array<float,9> flatten() const {
        return flatten(*this);
    }

    /**
     * unrolls the matrix in row major order (elements in the same row are adjacent in memory)
     */
    static std::array<float,9> flatten_row(const mat3& mat) {
        return {mat.data[0][0], mat.data[1][0], mat.data[2][0], mat.data[0][1], mat.data[1][1], mat.data[2][1], mat.data[0][2], mat.data[1][2], mat.data[2][2]};
    }

    /**
     * unrolls the matrix in row major order (elements in the same row are adjacent in memory)
     */
    std::array<float,9> flatten_row() const {
        return flatten_row(*this);
    }

    /**
     * casts a matrix to a bool
     * true if all components are non-zero
     * to check if any components are non-zero, compare with vec4::zero rather than casting
     */
    explicit operator bool() const {
        for (unsigned int i = 0; i < 3; i++) {
            for (unsigned int j = 0; j < 3; j++) {
                if (data[i][j] == 0) return false;
            }
        }
        return true;
    }

    #pragma endregion conversions

    #pragma region overloads

    /**
     * stream insertion operator
     * note: matrix is printed in column-major order
     */
    friend std::ostream& operator <<(std::ostream& os, const mat3& mat){
        os << std::to_string(mat);
        return os;
    }

    /**
     * Copy assignment operator
     */
    mat3& operator =(const mat3& other){
        for (unsigned int i = 0; i < 3; i++) {
            data[i] = other.data[i];
        }
        return *this;
    }

    /**
     * Component-wise addition
     */
    friend mat3 operator +(const mat3& a, const mat3& b){
        mat3 result;
        for (unsigned int i = 0; i < 3; i++) {
            result.data[i] = a.data[i] + b.data[i];
        }
        return result;
    }

    /**
     * Component-wise addition
     */
    friend mat3 operator +(const float& a, const mat3& b){
        mat3 result;
        for (unsigned int i = 0; i < 3; i++) {
            result.data[i] = a + b.data[i];
        }
        return result;
    }

    /**
     * Component-wise addition
     */
    friend mat3 operator +(const mat3& a, const float& b){
        mat3 result;
        for (unsigned int i = 0; i < 3; i++) {
            result.data[i] = a.data[i] + b;
        }
        return result;
    }

    /**
     * Component-wise subtraction
     */
    friend mat3 operator -(const mat3& a, const mat3& b){
        mat3 result;
        for (unsigned int i = 0; i < 3; i++) {
            result.data[i] = a.data[i] - b.data[i];
        }
        return result;
    }

    /**
     * Component-wise subtraction
     */
    friend mat3 operator -(const float& a, const mat3& b){
        mat3 result;
        for (unsigned int i = 0; i < 3; i++) {
            result.data[i] = a - b.data[i];
        }
        return result;
    }

    /**
     * Component-wise subtraction
     */
    friend mat3 operator -(const mat3& a, const float& b){
        mat3 result;
        for (unsigned int i = 0; i < 3; i++) {
            result.data[i] = a.data[i] - b;
        }
        return result;
    }

    /**
     * Component-wise negation
     */
    mat3 operator -() const {
        mat3 result;
        for (unsigned int i = 0; i < 3; i++) {
            result.data[i] = -data[i];
        }
        return result;
    }

    /**
     * Column major matrix multiplication
     */
    friend mat3 operator *(const mat3& a, const mat3& b){
        mat3 result;
        for (unsigned int i = 0; i < 3; i++) {
            for (unsigned int j = 0; j < 3; j++) {
                for (unsigned int k = 0; k < 3; k++) {
                    result[i][j] += a[k][i] * b[j][k];
                }
            }
        }
        return result;
    }

    /**
     * Row major matrix multiplication
     */
    friend vec3 operator *(const mat3& a, const vec3& b){
        return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
    }

    /**
     * Scalar multiplication (component-wise)
     */
    friend mat3 operator *(const float& a, const mat3& b){
        mat3 result;
        for (unsigned int i = 0; i < 3; i++) {
            result[i] = a*b[i];
        }
        return result;
    }

    /**
     * Scalar multiplication (component-wise)
     */
    friend mat3 operator *(const mat3& a, const float& b){
        mat3 result;
        for (unsigned int i = 0; i < 3; i++) {
            result[i] = a[i]*b;
        }
        return result;
    }

    /**
     * component-wise equality
     * true is all components are equal
     */
    friend bool operator ==(const mat3& a, const mat3& b){
        for (unsigned int i = 0; i < 3; i++) {
            if (a[i] != b[i]) return false;
        }
        return true;
    }

    /**
     * component-wise inequality
     * true is any component is not equal
     */
    friend bool operator !=(const mat3& a, const mat3& b){
        for (unsigned int i = 0; i < 3; i++) {
            if (a[i] != b[i]) return true;
        }
        return false;
    }

    /**
     * component-wise addition assignment operator
     */
    mat3& operator +=(const mat3& mat) {
        *this = *this + mat;
        return *this;
    }

    /**
     * component-wise addition assignment operator
     */
    mat3& operator +=(const float& a) {
        *this = *this + a;
        return *this;
    }

    /**
     * component-wise subtraction assignment operator
     */
    mat3& operator -=(const mat3& mat) {
        *this = *this - mat;
        return *this;
    }
    
    /**
     * component-wise subtraction assignment operator
     */
    mat3& operator -=(const float& a) {
        *this = *this - a;
        return *this;
    }

    /**
     * Column major matrix multiplication assignment operator
     */
    mat3& operator *=(const mat3& mat) {
        *this = *this * mat;
        return *this;
    }

    /**
     * Scalar multiplication assignment operator (component-wise)
     */
    mat3& operator *=(const float& a) {
        *this = *this * a;
        return *this;
    }

    /**
     * component-wise increment
     */
    mat3& operator ++() {
        *this = *this + 1;
        return *this;
    }

    /**
     * component-wise decrement
     */
    mat3& operator --() {
        *this = *this + 1;
        return *this;
    }

    #pragma endregion overloads

    #pragma region matrix operations

    /**
     * returns the determinant of this matrix
     */
    float determinant() const {
        float det = 0;
        for (unsigned int i = 0; i < 3; i ++){
            det += (i % 2 == 0 ? 1 : -1) * data[i][0] * (data[(i + 1) % 3][1]*data[(i + 2) % 3][2] - data[(i + 1) % 3][2]*data[(i + 2) % 3][1]);
        }
        return det;
    }

    /**
     * returns the determinant of a matrix
     */
    static float determinant(const mat3& mat) {
        return mat.determinant();
    }

    /**
     * returns the transpose of this matrix
     */
    mat3 transpose() const {
        mat3 result;
        for (unsigned int i = 0; i < 3; i++) {
            for (unsigned int j = 0; j < 3; j++) {
                result[i][j] = data[j][i];
            }
        }
        return result;
    }

    /**
     * returns the transpose of a matrix
     */
    static mat3 transpose(const mat3& mat) {
        return mat.transpose();
    }

    /**
     * returns the inverse of this matrix
     * code modified from https://stackoverflow.com/a/18504573
     */
    mat3 inverse() const {
        return inverse(*this);
    }

    /**
     * returns the inverse of a matrix
     * code modified from https://stackoverflow.com/a/18504573
     */
    static mat3 inverse(const mat3& mat) {
        float a = mat[1][1]*mat[2][2] - mat[2][1]*mat[1][2];
        float b = mat[1][2]*mat[2][0] - mat[1][0]*mat[2][2];
        float c = mat[1][0]*mat[2][1] - mat[2][0]*mat[1][1];

        float det = mat[0][0]*a + mat[0][1]*b + mat[0][2]*c;

        // non - invertible
        if (det == 0) return mat3();

        float invdet = 1 / det;

        mat3 inv;
        inv[0][0] = a*invdet;
        inv[0][1] = (mat[0][2]*mat[2][1] - mat[0][1]*mat[2][2])*invdet;
        inv[0][2] = (mat[0][1]*mat[1][2] - mat[0][2]*mat[1][1])*invdet;
        inv[1][0] = b*invdet;
        inv[1][1] = (mat[0][0]*mat[2][2] - mat[0][2]*mat[2][0])*invdet;
        inv[1][2] = (mat[1][0]*mat[0][2] - mat[0][0]*mat[1][2])*invdet;
        inv[2][0] = c*invdet;
        inv[2][1] = (mat[2][0]*mat[0][1] - mat[0][0]*mat[2][1])*invdet;
        inv[2][2] = (mat[0][0]*mat[1][1] - mat[1][0]*mat[0][1])*invdet;
        return inv;
    }

    /**
     * returns the trace of this matrix (sum of diagonal elements)
     */
    float trace() const {
        return data[0][0] + data[1][1] + data[2][2];
    }

    /**
     * returns the trace of a matrix (sum of diagonal elements)
     */
    static float trace(const mat3& mat) {
        return mat.trace();
    }

    /**
     * returns a 3d rotation matrix of some angle about an axis
     */
    static mat3 rotation(const vec3& axis, const float& angle) {
        float s = sinf(angle);
        float c = cosf(angle);
        float t = 1 - c;
        return mat3(
            axis.x*axis.x*t + c, axis.x*axis.y*t + axis.z*s, axis.x*axis.z*t - axis.y*s,
            axis.x*axis.y*t - axis.z*s, axis.y*axis.y*t + c, axis.y*axis.z*t + axis.x*s,
            axis.x*axis.z*t + axis.y*s, axis.y*axis.z*t - axis.x*s, axis.z*axis.z*t + c
        );
    }

    /**
     * returns a 3d rotation matrix about z then y then x
     */
    static mat3 rotation(const vec3& euler) {
        // most compilers will optimize this
        float cx = cosf(euler.x);
        float sx = sinf(euler.x);
        float cy = cosf(euler.y);    
        float sy = sinf(euler.y);
        float cz = cosf(euler.z);
        float sz = sinf(euler.z);
        return rotationX(euler.x) * rotationY(euler.y) * rotationZ(euler.z);
    }

    /**
     * returns a 3d rotation matrix about the x axis
     */
    static mat3 rotationX(const float& angle) {
        float c = cosf(angle);
        float s = sinf(angle);
        return mat3(
            1, 0, 0,
            0, c, -s,
            0, s, c
        );
    }

    /**
     * returns a 3d rotation matrix about the y axis
     */
    static mat3 rotationY(const float& angle) {
        float c = cosf(angle);
        float s = sinf(angle);
        return mat3(
            c, 0, s,
            0, 1, 0,
            -s, 0, c
        );
    }

    /**
     * returns a 3d rotation matrix about the z axis
     */
    static mat3 rotationZ(const float& angle) {
        float c = cosf(angle);
        float s = sinf(angle);
        return mat3(
            c, -s, 0,
            s, c, 0,
            0, 0, 1
        );
    }

    /**
     * returns a skew matrix
     */
    static mat3 skew(const vec3& skew) {
        return mat3(
            1, skew.x, skew.x,
            skew.y, 1, skew.y,
            skew.z, skew.z, 1
        );
    }

    /**
     * returns a scale matrix
     * equaivalent to component-wise vector multiplication
     */
    static mat3 scale(const vec3& scale) {
        return mat3(
            scale.x, 0, 0,
            0, scale.y, 0,
            0, 0, scale.z
        );
    }

    /**
     * returns a basis matrix from 3 vectors
     * equaivalent to just constructing from 3 vectors
     */
    static mat3 basis(const vec3& x, const vec3& y, const vec3& z) {
        return mat3(x, y, z);
    }

    /**
     * returns a basis matrix from 2 vectors (assumed to be the x and y axies respectively)
     * third vector is determined by the cross product of x and y
     */
    static mat3 basis(const vec3& x, const vec3& y) {
        return mat3(x, y, vec3::cross(x,y));
    }

    /**
     * returns a basis matrix from one vector (assumed to be the z axis)
     * the x axis is found using vec3::tangent and the y axis is the cross of x and z
     */
    static mat3 basis(const vec3& z) {
        vec3 t = z.tangent();
        return mat3(t, vec3::cross(t,z), z);
    }

    #pragma endregion matrix operations
};

}

namespace std {
    /**
     * converts a matrix to a string
     * note: matrix is printed in column-major order
     */
    std::string to_string(const Engine::mat3& mat) {
        return "[ " + std::to_string(mat[0][0]) + " " + std::to_string(mat[0][1]) + " " + std::to_string(mat[0][2]) + " ]\n[ " + std::to_string(mat[1][0]) + " " + std::to_string(mat[1][1]) + " " + std::to_string(mat[1][2]) + " ]\n[ " + std::to_string(mat[2][0]) + " " + std::to_string(mat[2][1]) + " " + std::to_string(mat[2][2]) + " ]";
    }

}

#endif