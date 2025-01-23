#include "mat2.hpp"
#include <cmath>

namespace Engine {

#pragma region constants

/**
 * identity matrix
 * equivalent to `mat2(1)`
 */
const mat2 mat2::identity = mat2(1);
/**
 * matrix of all zeros
 * equivalent to `mat2(0)`
 */
const mat2 mat2::zero = mat2(0);
/**
 * matrix of all ones
 * for diagonal ones, use mat2::identity
 */
const mat2 mat2::one = mat2(vec2(1), vec2(1));

#pragma endregion constants

#pragma region constructors

/**
 * Default constructor
 * Initializes all components to 0
 */
mat2::mat2() {
    data.fill(vec2(0));
}

/**
 * Copy constructor
 */
mat2::mat2(const mat2& mat) {
    for (unsigned int i = 0; i < N; i++) {
        data[i] = mat[i];
    }
}

/**
 * more constructors in Matrix.hpp
 */

#pragma endregion constructors

#pragma region accessors

/**
 * Column accessor
 */
vec2& mat2::operator [](unsigned int i) {
    if (i >= N) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

/**
 * Column accessor 
 */
const vec2& mat2::operator [](unsigned int i) const {
    if (i >= N) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

#pragma endregion accessors

#pragma region iteration

/**
 * Iterator to the first component
 */
auto mat2::begin() noexcept {
    return data.begin();
}

/**
 * Iterator to the end of the components
 */
auto mat2::end() noexcept {
    return data.end();
}

/**
 * Iterator to the first component
 */
auto mat2::begin() const noexcept {
    return data.begin();
}

/**
 * Iterator to the end of the components
 */
auto mat2::end() const noexcept {
    return data.end();
}

/**
 * Iterator to the first component
 */
auto mat2::cbegin() const noexcept {
    return data.cbegin();
}

/**
 * Iterator to the end of the components
 */
auto mat2::cend() const noexcept {
    return data.cend();
}

/**
 * Reverse iterator to the first component
 */
auto mat2::rbegin() noexcept {
    return data.rbegin();
}

/**
 * Reverse iterator to the end of the components
 */
auto mat2::rend() noexcept {
    return data.rend();
}

/**
 * Reverse iterator to the first component
 */
auto mat2::rbegin() const noexcept {
    return data.rbegin();
}

/**
 * Reverse iterator to the end of the components
 */
auto mat2::rend() const noexcept {
    return data.rend();
}

/**
 * Reverse iterator to the first component
 */
auto mat2::crbegin() const noexcept {
    return data.crbegin();
}

/**
 * Reverse iterator to the end of the components
 */
auto mat2::crend() const noexcept {
    return data.crend();
}

#pragma endregion iteration

#pragma region conversions

/**
 * unrolls the matrix in column major order (elements in the same column are adjacent in memory)
 */
std::array<float,mat2::N*mat2::N> mat2::flatten(const mat2& mat) {
    return {mat.data[0][0], mat.data[0][1], mat.data[1][0], mat.data[1][1]};
}

/**
 * unrolls the matrix in column major order (elements in the same column are adjacent in memory)
 */
std::array<float,mat2::N*mat2::N> mat2::flatten() const {
    return flatten(*this);
}

/**
 * unrolls the matrix in row major order (elements in the same row are adjacent in memory)
 */
std::array<float,mat2::N*mat2::N> mat2::flatten_row(const mat2& mat) {
    return {mat.data[0][0], mat.data[1][0], mat.data[0][1], mat.data[1][1]};
}

/**
 * unrolls the matrix in row major order (elements in the same row are adjacent in memory)
 */
std::array<float,mat2::N*mat2::N> mat2::flatten_row() const {
    return flatten_row(*this);
}

/**
 * casts a matrix to a bool
 * true if all components are non-zero
 * to check if any components are non-zero, compare with vec4::zero rather than casting
 */
mat2::operator bool() const {
    for (unsigned int i = 0; i < N; i++) {
        for (unsigned int j = 0; j < N; j++) {
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
std::ostream& operator <<(std::ostream& os, const mat2& mat){
    os << std::to_string(mat);
    return os;
}

/**
 * Copy assignment operator
 */
mat2& mat2::operator =(const mat2& other){
    for (unsigned int i = 0; i < N; i++) {
        data[i] = other.data[i];
    }
    return *this;
}

/**
 * Component-wise addition
 */
mat2 operator +(const mat2& a, const mat2& b){
    mat2 result;
    for (unsigned int i = 0; i < mat2::N; i++) {
        result.data[i] = a.data[i] + b.data[i];
    }
    return result;
}

/**
 * Component-wise addition
 */
mat2 operator +(const float& a, const mat2& b){
    mat2 result;
    for (unsigned int i = 0; i < mat2::N; i++) {
        result.data[i] = a + b.data[i];
    }
    return result;
}

/**
 * Component-wise addition
 */
mat2 operator +(const mat2& a, const float& b){
    mat2 result;
    for (unsigned int i = 0; i < mat2::N; i++) {
        result.data[i] = a.data[i] + b;
    }
    return result;
}

/**
 * Component-wise subtraction
 */
mat2 operator -(const mat2& a, const mat2& b){
    mat2 result;
    for (unsigned int i = 0; i < mat2::N; i++) {
        result.data[i] = a.data[i] - b.data[i];
    }
    return result;
}

/**
 * Component-wise subtraction
 */
mat2 operator -(const float& a, const mat2& b){
    mat2 result;
    for (unsigned int i = 0; i < mat2::N; i++) {
        result.data[i] = a - b.data[i];
    }
    return result;
}

/**
 * Component-wise subtraction
 */
mat2 operator -(const mat2& a, const float& b){
    mat2 result;
    for (unsigned int i = 0; i < mat2::N; i++) {
        result.data[i] = a.data[i] - b;
    }
    return result;
}

/**
 * Component-wise negation
 */
mat2 mat2::operator -() const {
    mat2 result;
    for (unsigned int i = 0; i < N; i++) {
        result.data[i] = -data[i];
    }
    return result;
}

/**
 * Column major matrix multiplication
 */
mat2 operator *(const mat2& a, const mat2& b){
    mat2 result;
    for (unsigned int i = 0; i < mat2::N; i++) {
        for (unsigned int j = 0; j < mat2::N; j++) {
            for (unsigned int k = 0; k < mat2::N; k++) {
                result[i][j] += a[k][i] * b[j][k];
            }
        }
    }
    return result;
}

/**
 * Column major matrix multiplication
 */
vec2 operator *(const mat2& a, const vec2& b){
    vec2 result;
    for (unsigned int i = 0; i < mat2::N; i++) {
        result += a[i]*b[i];
    }
    return result;
}

/**
 * Scalar multiplication (component-wise)
 */
mat2 operator *(const float& a, const mat2& b){
    mat2 result;
    for (unsigned int i = 0; i < mat2::N; i++) {
        result[i] = a*b[i];
    }
    return result;
}

/**
 * Scalar multiplication (component-wise)
 */
mat2 operator *(const mat2& a, const float& b){
    mat2 result;
    for (unsigned int i = 0; i < mat2::N; i++) {
        result[i] = a[i]*b;
    }
    return result;
}

/**
 * Component-wise equality
 * true is all components are equal
 */
bool operator ==(const mat2& a, const mat2& b){
    for (unsigned int i = 0; i < mat2::N; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

/**
 * Component-wise inequality
 * true is any component is not equal
 */
bool operator !=(const mat2& a, const mat2& b){
    for (unsigned int i = 0; i < mat2::N; i++) {
        if (a[i] != b[i]) return true;
    }
    return false;
}

/**
 * Component-wise addition assignment operator
 */
mat2& mat2::operator +=(const mat2& mat) {
    *this = *this + mat;
    return *this;
}

/**
 * Component-wise addition assignment operator
 */
mat2& mat2::operator +=(const float& a) {
    *this = *this + a;
    return *this;
}

/**
 * Component-wise subtraction assignment operator
 */
mat2& mat2::operator -=(const mat2& mat) {
    *this = *this - mat;
    return *this;
}

/**
 * Component-wise subtraction assignment operator
 */
mat2& mat2::operator -=(const float& a) {
    *this = *this - a;
    return *this;
}

/**
 * Column major matrix multiplication assignment operator
 */
mat2& mat2::operator *=(const mat2& mat) {
    *this = *this * mat;
    return *this;
}

/**
 * Scalar multiplication assignment operator (component-wise)
 */
mat2& mat2::operator *=(const float& a) {
    *this = *this * a;
    return *this;
}

/**
 * Component-wise increment
 */
mat2& mat2::operator ++() {
    *this = *this + 1.0f;
    return *this;
}

/**
 * Component-wise decrement
 */
mat2& mat2::operator --() {
    *this = *this - 1.0f;
    return *this;
}

#pragma endregion overloads

#pragma region matrix operations

/**
 * returns the determinant of this matrix
 */
float mat2::determinant() const {
    return data[0][0]*data[1][1] - data[0][1]*data[1][0];
}

/**
 * returns the determinant of a matrix
 */
float mat2::determinant(const mat2& mat) {
    return mat.determinant();
}

/**
 * returns the transpose of this matrix
 */
mat2 mat2::transpose() const {
    mat2 result;
    for (unsigned int i = 0; i < N; i++) {
        for (unsigned int j = 0; j < N; j++) {
            result[i][j] = data[j][i];
        }
    }
    return result;
}

/**
 * returns the transpose of a matrix
 */
mat2 mat2::transpose(const mat2& mat) {
    return mat.transpose();
}

/**
 * returns the inverse of this matrix
 */
mat2 mat2::inverse() const {
    return inverse(*this);
}

/**
 * returns the inverse of a matrix
 */
mat2 mat2::inverse(const mat2& mat) {
    float det = mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0];

    // non - invertible
    if (det == 0) return mat2();

    float invdet = 1 / det;

    mat2 inv;
    inv[0][0] = mat[1][1] * invdet;
    inv[0][1] = -mat[0][1] * invdet;
    inv[1][0] = -mat[1][0] * invdet;
    inv[1][1] = mat[0][0] * invdet;

    return inv;
}

/**
 * returns the trace of this matrix (sum of diagonal elements)
 */
float mat2::trace() const {
    return data[0][0] + data[1][1] + data[2][2];
}

/**
 * returns the trace of a matrix (sum of diagonal elements)
 */
float mat2::trace(const mat2& mat) {
    return mat.trace();
}

    /**
     * returns a 2d rotation matrix of some angle
     */
mat2 mat2::rotation(const float& angle) {
    float s = sinf(angle);
    float c = cosf(angle);
    return mat2(
        c, s,
        -s, c
    );
}

/**
 * returns a skew matrix
 */
mat2 mat2::skew(const vec2& skew) {
    return mat2(
        1, skew.x,
        skew.y, 1
    );
}

/**
 * returns a scale matrix
 * equaivalent to component-wise vector multiplication
 */
mat2 mat2::scale(const vec2& scale) {
    return mat2(
        scale.x, 0,
        0, scale.y
    );
}

/**
 * returns a basis matrix from 2 vectors
 * equaivalent to just constructing from 2 vectors
 */
mat2 mat2::basis(const vec2& x, const vec2& y) {
    return mat2(x, y);
}

/**
 * returns a basis matrix from one vector (assumed to be the x axis)
 */
mat2 mat2::basis(const vec2& x) {
    return mat2(x, x.tangent());
}

#pragma endregion matrix operations

}

namespace std {
    /**
     * converts a matrix to a string
     * note: matrix is printed in column-major order
     */
    std::string to_string(const Engine::mat2& mat) {
        return "[ " + std::to_string(mat[0][0]) + " " + std::to_string(mat[0][1]) + " ]\n[ " + std::to_string(mat[1][0]) + " " + std::to_string(mat[1][1]) + " ]";
    }

}
