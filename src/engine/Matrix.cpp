#include "Matrix.hpp"

#pragma region mat4

namespace Engine {

#pragma region constants

/**
 * identity matrix
 * equivalent to `mat4(1)`
 */
const mat4 mat4::identity = mat4(1);
/**
 * matrix of all zeros
 * equivalent to `mat4(0)`
 */
const mat4 mat4::zero = mat4(0);
/**
 * matrix of all ones
 * for diagonal ones, use mat4::identity
 */
const mat4 one = mat4(vec4(1), vec4(1), vec4(1), vec4(1));

#pragma endregion constants

#pragma region constructors

/**
 * Default constructor
 * Initializes all components to 0
 */
mat4::mat4() {
    data.fill(0);
}

/**
 * more constructors in Matrix.hpp
 */

#pragma endregion constructors

#pragma region accessors

/**
 * Column accessor
 */
vec4& mat4::operator [](unsigned int i) {
    if (i >= N) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

/**
 * Column accessor 
 */
const vec4& mat4::operator [](unsigned int i) const {
    if (i >= N) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

#pragma endregion accessors

#pragma region iteration

/**
 * iterator to the first component
 */
auto mat4::begin() noexcept {
    return data.begin();
}

/**
 * iterator to the end of the components
 */
auto mat4::end() noexcept {
    return data.end();
}

/**
 * iterator to the first component
 */
auto mat4::begin() const noexcept {
    return data.begin();
}

/**
 * iterator to the end of the components
 */
auto mat4::end() const noexcept {
    return data.end();
}

/**
 * iterator to the first component
 */
auto mat4::cbegin() const noexcept {
    return data.cbegin();
}

/**
 * iterator to the end of the components
 */
auto mat4::cend() const noexcept {
    return data.cend();
}

/**
 * reverse iterator to the first component
 */
auto mat4::rbegin() noexcept {
    return data.rbegin();
}

/**
 * reverse iterator to the end of the components
 */
auto mat4::rend() noexcept {
    return data.rend();
}

/**
 * reverse iterator to the first component
 */
auto mat4::rbegin() const noexcept {
    return data.rbegin();
}

/**
 * reverse iterator to the end of the components
 */
auto mat4::rend() const noexcept {
    return data.rend();
}

/**
 * reverse iterator to the first component
 */
auto mat4::crbegin() const noexcept {
    return data.crbegin();
}

/**
 * reverse iterator to the end of the components
 */
auto mat4::crend() const noexcept {
    return data.crend();
}

#pragma endregion iteration

#pragma region conversions

/**
 * unrolls the matrix in column major order (elements in the same column are adjacent in memory)
 */
std::array<float,mat4::N*mat4::N> mat4::flatten(const mat4& mat) {
    return {mat.data[0][0], mat.data[0][1], mat.data[0][2], mat.data[0][3], mat.data[1][0], mat.data[1][1], mat.data[1][2], mat.data[1][3], mat.data[2][0], mat.data[2][1], mat.data[2][2], mat.data[2][3], mat.data[3][0], mat.data[3][1], mat.data[3][2], mat.data[3][3]};
}

/**
 * unrolls the matrix in column major order (elements in the same column are adjacent in memory)
 */
std::array<float,mat4::N*mat4::N> mat4::flatten() const {
    return flatten(*this);
}

/**
 * unrolls the matrix in row major order (elements in the same row are adjacent in memory)
 */
std::array<float,mat4::N*mat4::N> mat4::flatten_row(const mat4& mat) {
    return {mat.data[0][0], mat.data[1][0], mat.data[2][0], mat.data[3][0], mat.data[0][1], mat.data[1][1], mat.data[2][1], mat.data[3][1], mat.data[0][2], mat.data[1][2], mat.data[2][2], mat.data[3][2], mat.data[0][3], mat.data[1][3], mat.data[2][3], mat.data[3][3]};
}

/**
 * unrolls the matrix in row major order (elements in the same row are adjacent in memory)
 */
std::array<float,mat4::N*mat4::N> mat4::flatten_row() const {
    return flatten_row(*this);
}

/**
 * casts a matrix to a bool
 * true if all components are non-zero
 * to check if any components are non-zero, compare with vec4::zero rather than casting
 */
explicit mat4::operator bool() const {
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
std::ostream& operator <<(std::ostream& os, const mat4& mat){
    os << std::to_string(mat);
    return os;
}

/**
 * Copy assignment operator
 */
mat4& mat4::operator =(const mat4& other){
    for (unsigned int i = 0; i < N; i++) {
        data[i] = other.data[i];
    }
    return *this;
}

/**
 * Component-wise addition
 */
mat4 operator +(const mat4& a, const mat4& b){
    mat4 result;
    for (unsigned int i = 0; i < mat4::N; i++) {
        result.data[i] = a.data[i] + b.data[i];
    }
    return result;
}

/**
 * Component-wise addition
 */
mat4 operator +(const float& a, const mat4& b){
    mat4 result;
    for (unsigned int i = 0; i < mat4::N; i++) {
        result.data[i] = a + b.data[i];
    }
    return result;
}

/**
 * Component-wise addition
 */
mat4 operator +(const mat4& a, const float& b){
    mat4 result;
    for (unsigned int i = 0; i < mat4::N; i++) {
        result.data[i] = a.data[i] + b;
    }
    return result;
}

/**
 * Component-wise subtraction
 */
mat4 operator -(const mat4& a, const mat4& b){
    mat4 result;
    for (unsigned int i = 0; i < mat4::N; i++) {
        result.data[i] = a.data[i] - b.data[i];
    }
    return result;
}

/**
 * Component-wise subtraction
 */
mat4 operator -(const float& a, const mat4& b){
    mat4 result;
    for (unsigned int i = 0; i < mat4::N; i++) {
        result.data[i] = a - b.data[i];
    }
    return result;
}

/**
 * Component-wise subtraction
 */
mat4 operator -(const mat4& a, const float& b){
    mat4 result;
    for (unsigned int i = 0; i < mat4::N; i++) {
        result.data[i] = a.data[i] - b;
    }
    return result;
}

/**
 * Component-wise negation
 */
mat4 mat4::operator -() const {
    mat4 result;
    for (unsigned int i = 0; i < N; i++) {
        result.data[i] = -data[i];
    }
    return result;
}

/**
 * Column major matrix multiplication
 */
mat4 operator *(const mat4& a, const mat4& b){
    mat4 result;
    for (unsigned int i = 0; i < mat4::N; i++) {
        for (unsigned int j = 0; j < mat4::N; j++) {
            for (unsigned int k = 0; k < mat4::N; k++) {
                result[i][j] += a[k][i] * b[j][k];
            }
        }
    }
    return result;
}

/**
 * Column major matrix multiplication
 */
vec4 operator *(const mat4& a, const vec4& b){
    vec4 result;
    for (unsigned int i = 0; i < mat4::N; i++) {
        result += a[i]*b[i];
    }
    return result;
}

/**
 * Scalar multiplication (component-wise)
 */
mat4 operator *(const float& a, const mat4& b){
    mat4 result;
    for (unsigned int i = 0; i < mat4::N; i++) {
        result[i] = a*b[i];
    }
    return result;
}

/**
 * Scalar multiplication (component-wise)
 */
mat4 operator *(const mat4& a, const float& b){
    mat4 result;
    for (unsigned int i = 0; i < mat4::N; i++) {
        result[i] = a[i]*b;
    }
    return result;
}

/**
 * component-wise equality
 * true is all components are equal
 */
bool operator ==(const mat4& a, const mat4& b){
    for (unsigned int i = 0; i < mat4::N; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

/**
 * component-wise inequality
 * true is any component is not equal
 */
bool operator !=(const mat4& a, const mat4& b){
    for (unsigned int i = 0; i < mat4::N; i++) {
        if (a[i] != b[i]) return true;
    }
    return false;
}

/**
 * component-wise addition assignment operator
 */
mat4& mat4::operator +=(const mat4& mat) {
    *this = *this + mat;
    return *this;
}

/**
 * component-wise addition assignment operator
 */
mat4& mat4::operator +=(const float& a) {
    *this = *this + a;
    return *this;
}

/**
 * component-wise subtraction assignment operator
 */
mat4& mat4::operator -=(const mat4& mat) {
    *this = *this - mat;
    return *this;
}

/**
 * component-wise subtraction assignment operator
 */
mat4& mat4::operator -=(const float& a) {
    *this = *this - a;
    return *this;
}

/**
 * Column major matrix multiplication assignment operator
 */
mat4& mat4::operator *=(const mat4& mat) {
    *this = *this * mat;
    return *this;
}

/**
 * Scalar multiplication assignment operator (component-wise)
 */
mat4& mat4::operator *=(const float& a) {
    *this = *this * a;
    return *this;
}

/**
 * component-wise increment
 */
mat4& mat4::operator ++() {
    *this = *this + 1;
    return *this;
}

/**
 * component-wise decrement
 */
mat4& mat4::operator --() {
    *this = *this + 1;
    return *this;
}

#pragma endregion overloads

#pragma region matrix operations

/**
 * returns the transpose of this matrix
 */
mat4 mat4::transpose() const {
    mat4 result;
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
mat4 mat4::transpose(const mat4& mat) {
    return mat.transpose();
}

/**
 * returns the trace of this matrix (sum of diagonal elements)
 */
float mat4::trace() const {
    return data[0][0] + data[1][1] + data[2][2] + data[3][3];
}

/**
 * returns the trace of a matrix (sum of diagonal elements)
 */
float mat4::trace(const mat4& mat) {
    return mat.trace();
}

/**
 * returns a skew matrix
 */
mat4 mat4::skew(const vec4& skew) {
    return mat4(
        1, skew.x, skew.x, skew.x,
        skew.y, 1, skew.y, skew.y,
        skew.z, skew.z, 1, skew.z,
        skew.w, skew.w, skew.w, 1
    );
}

/**
 * returns a scale matrix
 * equaivalent to component-wise vector multiplication
 */
mat4 mat4::scale(const vec4& scale) {
    return mat4(
        scale.x, 0, 0,
        0, scale.y, 0,
        0, 0, scale.z
    );
}

/**
 * returns a basis matrix from 4 vectors
 * equaivalent to just constructing from 4 vectors
 */
mat4 mat4::basis(const vec4& x, const vec4& y, const vec4& z, const vec4& w) {
    return mat4(x, y, z);
}

#pragma endregion matrix operations

}

namespace std {
    /**
     * converts a matrix to a string
     * note: matrix is printed in column-major order
     */
    std::string to_string(const Engine::mat4& mat) {
        return "[ " + std::to_string(mat[0][0]) + " " + std::to_string(mat[0][1]) + " " + std::to_string(mat[0][2]) + " " + std::to_string(mat[0][3]) + 
        " ]\n[ " + std::to_string(mat[1][0]) + " " + std::to_string(mat[1][1]) + " " + std::to_string(mat[1][2]) + " " + std::to_string(mat[1][3]) + 
        " ]\n[ " + std::to_string(mat[2][0]) + " " + std::to_string(mat[2][1]) + " " + std::to_string(mat[2][2]) + " " + std::to_string(mat[2][3]) + 
        " ]\n[ " + std::to_string(mat[3][0]) + " " + std::to_string(mat[3][1]) + " " + std::to_string(mat[3][2]) + " " + std::to_string(mat[3][3]) + 
        " ]\n[ " + std::to_string(mat[4][0]) + " " + std::to_string(mat[4][1]) + " " + std::to_string(mat[4][2]) + " " + std::to_string(mat[4][3]) + " ]";
    }

}

#pragma endregion mat4

#pragma region mat3

namespace Engine {

#pragma region constants

/**
 * identity matrix
 * equivalent to `mat3(1)`
 */
const mat3 mat3::identity = mat3(1);
/**
 * matrix of all zeros
 * equivalent to `mat3(0)`
 */
const mat3 mat3::zero = mat3(0);
/**
 * matrix of all ones
 * for diagonal ones, use mat3::identity
 */
const mat3 one = mat3(vec3(1), vec3(1), vec3(1));

#pragma endregion constants

#pragma region constructors

/**
 * Default constructor
 * Initializes all components to 0
 */
mat3::mat3() {
    data.fill(0);
}

/**
 * more constructors in Matrix.hpp
 */

#pragma endregion constructors

#pragma region accessors

/**
 * Column accessor
 */
vec3& mat3::operator [](unsigned int i) {
    if (i >= N) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

/**
 * Column accessor 
 */
const vec3& mat3::operator [](unsigned int i) const {
    if (i >= N) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

#pragma endregion accessors

#pragma region iteration

/**
 * iterator to the first component
 */
auto mat3::begin() noexcept {
    return data.begin();
}

/**
 * iterator to the end of the components
 */
auto mat3::end() noexcept {
    return data.end();
}

/**
 * iterator to the first component
 */
auto mat3::begin() const noexcept {
    return data.begin();
}

/**
 * iterator to the end of the components
 */
auto mat3::end() const noexcept {
    return data.end();
}

/**
 * iterator to the first component
 */
auto mat3::cbegin() const noexcept {
    return data.cbegin();
}

/**
 * iterator to the end of the components
 */
auto mat3::cend() const noexcept {
    return data.cend();
}

/**
 * reverse iterator to the first component
 */
auto mat3::rbegin() noexcept {
    return data.rbegin();
}

/**
 * reverse iterator to the end of the components
 */
auto mat3::rend() noexcept {
    return data.rend();
}

/**
 * reverse iterator to the first component
 */
auto mat3::rbegin() const noexcept {
    return data.rbegin();
}

/**
 * reverse iterator to the end of the components
 */
auto mat3::rend() const noexcept {
    return data.rend();
}

/**
 * reverse iterator to the first component
 */
auto mat3::crbegin() const noexcept {
    return data.crbegin();
}

/**
 * reverse iterator to the end of the components
 */
auto mat3::crend() const noexcept {
    return data.crend();
}

#pragma endregion iteration

#pragma region conversions

/**
 * unrolls the matrix in column major order (elements in the same column are adjacent in memory)
 */
std::array<float,mat3::N*mat3::N> mat3::flatten(const mat3& mat) {
    return {mat.data[0][0], mat.data[0][1], mat.data[0][2], mat.data[1][0], mat.data[1][1], mat.data[1][2], mat.data[2][0], mat.data[2][1], mat.data[2][2]};
}

/**
 * unrolls the matrix in column major order (elements in the same column are adjacent in memory)
 */
std::array<float,mat3::N*mat3::N> mat3::flatten() const {
    return flatten(*this);
}

/**
 * unrolls the matrix in row major order (elements in the same row are adjacent in memory)
 */
std::array<float,mat3::N*mat3::N> mat3::flatten_row(const mat3& mat) {
    return {mat.data[0][0], mat.data[1][0], mat.data[2][0], mat.data[0][1], mat.data[1][1], mat.data[2][1], mat.data[0][2], mat.data[1][2], mat.data[2][2]};
}

/**
 * unrolls the matrix in row major order (elements in the same row are adjacent in memory)
 */
std::array<float,mat3::N*mat3::N> mat3::flatten_row() const {
    return flatten_row(*this);
}

/**
 * casts a matrix to a bool
 * true if all components are non-zero
 * to check if any components are non-zero, compare with vec4::zero rather than casting
 */
explicit mat3::operator bool() const {
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
std::ostream& operator <<(std::ostream& os, const mat3& mat){
    os << std::to_string(mat);
    return os;
}

/**
 * Copy assignment operator
 */
mat3& mat3::operator =(const mat3& other){
    for (unsigned int i = 0; i < N; i++) {
        data[i] = other.data[i];
    }
    return *this;
}

/**
 * Component-wise addition
 */
mat3 operator +(const mat3& a, const mat3& b){
    mat3 result;
    for (unsigned int i = 0; i < mat3::N; i++) {
        result.data[i] = a.data[i] + b.data[i];
    }
    return result;
}

/**
 * Component-wise addition
 */
mat3 operator +(const float& a, const mat3& b){
    mat3 result;
    for (unsigned int i = 0; i < mat3::N; i++) {
        result.data[i] = a + b.data[i];
    }
    return result;
}

/**
 * Component-wise addition
 */
mat3 operator +(const mat3& a, const float& b){
    mat3 result;
    for (unsigned int i = 0; i < mat3::N; i++) {
        result.data[i] = a.data[i] + b;
    }
    return result;
}

/**
 * Component-wise subtraction
 */
mat3 operator -(const mat3& a, const mat3& b){
    mat3 result;
    for (unsigned int i = 0; i < mat3::N; i++) {
        result.data[i] = a.data[i] - b.data[i];
    }
    return result;
}

/**
 * Component-wise subtraction
 */
mat3 operator -(const float& a, const mat3& b){
    mat3 result;
    for (unsigned int i = 0; i < mat3::N; i++) {
        result.data[i] = a - b.data[i];
    }
    return result;
}

/**
 * Component-wise subtraction
 */
mat3 operator -(const mat3& a, const float& b){
    mat3 result;
    for (unsigned int i = 0; i < mat3::N; i++) {
        result.data[i] = a.data[i] - b;
    }
    return result;
}

/**
 * Component-wise negation
 */
mat3 mat3::operator -() const {
    mat3 result;
    for (unsigned int i = 0; i < N; i++) {
        result.data[i] = -data[i];
    }
    return result;
}

/**
 * Column major matrix multiplication
 */
mat3 operator *(const mat3& a, const mat3& b){
    mat3 result;
    for (unsigned int i = 0; i < mat3::N; i++) {
        for (unsigned int j = 0; j < mat3::N; j++) {
            for (unsigned int k = 0; k < mat3::N; k++) {
                result[i][j] += a[k][i] * b[j][k];
            }
        }
    }
    return result;
}

/**
 * Column major matrix multiplication
 */
vec3 operator *(const mat3& a, const vec3& b){
    vec3 result;
    for (unsigned int i = 0; i < mat3::N; i++) {
        result += a[i]*b[i];
    }
    return result;
}

/**
 * Scalar multiplication (component-wise)
 */
mat3 operator *(const float& a, const mat3& b){
    mat3 result;
    for (unsigned int i = 0; i < mat3::N; i++) {
        result[i] = a*b[i];
    }
    return result;
}

/**
 * Scalar multiplication (component-wise)
 */
mat3 operator *(const mat3& a, const float& b){
    mat3 result;
    for (unsigned int i = 0; i < mat3::N; i++) {
        result[i] = a[i]*b;
    }
    return result;
}

/**
 * component-wise equality
 * true is all components are equal
 */
bool operator ==(const mat3& a, const mat3& b){
    for (unsigned int i = 0; i < mat3::N; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

/**
 * component-wise inequality
 * true is any component is not equal
 */
bool operator !=(const mat3& a, const mat3& b){
    for (unsigned int i = 0; i < mat3::N; i++) {
        if (a[i] != b[i]) return true;
    }
    return false;
}

/**
 * component-wise addition assignment operator
 */
mat3& mat3::operator +=(const mat3& mat) {
    *this = *this + mat;
    return *this;
}

/**
 * component-wise addition assignment operator
 */
mat3& mat3::operator +=(const float& a) {
    *this = *this + a;
    return *this;
}

/**
 * component-wise subtraction assignment operator
 */
mat3& mat3::operator -=(const mat3& mat) {
    *this = *this - mat;
    return *this;
}

/**
 * component-wise subtraction assignment operator
 */
mat3& mat3::operator -=(const float& a) {
    *this = *this - a;
    return *this;
}

/**
 * Column major matrix multiplication assignment operator
 */
mat3& mat3::operator *=(const mat3& mat) {
    *this = *this * mat;
    return *this;
}

/**
 * Scalar multiplication assignment operator (component-wise)
 */
mat3& mat3::operator *=(const float& a) {
    *this = *this * a;
    return *this;
}

/**
 * component-wise increment
 */
mat3& mat3::operator ++() {
    *this = *this + 1;
    return *this;
}

/**
 * component-wise decrement
 */
mat3& mat3::operator --() {
    *this = *this + 1;
    return *this;
}

#pragma endregion overloads

#pragma region matrix operations

/**
 * returns the determinant of this matrix
 */
float mat3::determinant() const {
    float det = 0;
    for (unsigned int i = 0; i < N; i ++){
        det += (i % 2 == 0 ? 1 : -1) * data[i][0] * (data[(i + 1) % 3][1]*data[(i + 2) % 3][2] - data[(i + 1) % 3][2]*data[(i + 2) % 3][1]);
    }
    return det;
}

/**
 * returns the determinant of a matrix
 */
float mat3::determinant(const mat3& mat) {
    return mat.determinant();
}

/**
 * returns the transpose of this matrix
 */
mat3 mat3::transpose() const {
    mat3 result;
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
mat3 mat3::transpose(const mat3& mat) {
    return mat.transpose();
}

/**
 * returns the inverse of this matrix
 * code modified from https://stackoverflow.com/a/18504573
 */
mat3 mat3::inverse() const {
    return inverse(*this);
}

/**
 * returns the inverse of a matrix
 * code modified from https://stackoverflow.com/a/18504573
 */
mat3 mat3::inverse(const mat3& mat) {
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
float mat3::trace() const {
    return data[0][0] + data[1][1] + data[2][2];
}

/**
 * returns the trace of a matrix (sum of diagonal elements)
 */
float mat3::trace(const mat3& mat) {
    return mat.trace();
}

/**
 * returns a 3d rotation matrix of some angle about an axis
 */
mat3 mat3::rotation(const vec3& axis, const float& angle) {
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
mat3 mat3::rotation(const vec3& euler) {
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
mat3 mat3::rotationX(const float& angle) {
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
mat3 mat3::rotationY(const float& angle) {
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
mat3 mat3::rotationZ(const float& angle) {
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
mat3 mat3::skew(const vec3& skew) {
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
mat3 mat3::scale(const vec3& scale) {
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
mat3 mat3::basis(const vec3& x, const vec3& y, const vec3& z) {
    return mat3(x, y, z);
}

/**
 * returns a basis matrix from 2 vectors (assumed to be the x and y axies respectively)
 * third vector is determined by the cross product of x and y
 */
mat3 mat3::basis(const vec3& x, const vec3& y) {
    return mat3(x, y, vec3::cross(x,y));
}

/**
 * returns a basis matrix from one vector (assumed to be the z axis)
 * the x axis is found using vec3::tangent and the y axis is the cross of x and z
 */
mat3 mat3::basis(const vec3& z) {
    vec3 t = z.tangent();
    return mat3(t, vec3::cross(t,z), z);
}

#pragma endregion matrix operations

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

#pragma endregion mat3

#pragma region mat2

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
const mat2 one = mat2(vec2(1), vec2(1));

#pragma endregion constants

#pragma region constructors

/**
 * Default constructor
 * Initializes all components to 0
 */
mat2::mat2() {
    data.fill(0);
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
 * iterator to the first component
 */
auto mat2::begin() noexcept {
    return data.begin();
}

/**
 * iterator to the end of the components
 */
auto mat2::end() noexcept {
    return data.end();
}

/**
 * iterator to the first component
 */
auto mat2::begin() const noexcept {
    return data.begin();
}

/**
 * iterator to the end of the components
 */
auto mat2::end() const noexcept {
    return data.end();
}

/**
 * iterator to the first component
 */
auto mat2::cbegin() const noexcept {
    return data.cbegin();
}

/**
 * iterator to the end of the components
 */
auto mat2::cend() const noexcept {
    return data.cend();
}

/**
 * reverse iterator to the first component
 */
auto mat2::rbegin() noexcept {
    return data.rbegin();
}

/**
 * reverse iterator to the end of the components
 */
auto mat2::rend() noexcept {
    return data.rend();
}

/**
 * reverse iterator to the first component
 */
auto mat2::rbegin() const noexcept {
    return data.rbegin();
}

/**
 * reverse iterator to the end of the components
 */
auto mat2::rend() const noexcept {
    return data.rend();
}

/**
 * reverse iterator to the first component
 */
auto mat2::crbegin() const noexcept {
    return data.crbegin();
}

/**
 * reverse iterator to the end of the components
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
explicit mat2::operator bool() const {
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
 * component-wise equality
 * true is all components are equal
 */
bool operator ==(const mat2& a, const mat2& b){
    for (unsigned int i = 0; i < mat2::N; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

/**
 * component-wise inequality
 * true is any component is not equal
 */
bool operator !=(const mat2& a, const mat2& b){
    for (unsigned int i = 0; i < mat2::N; i++) {
        if (a[i] != b[i]) return true;
    }
    return false;
}

/**
 * component-wise addition assignment operator
 */
mat2& mat2::operator +=(const mat2& mat) {
    *this = *this + mat;
    return *this;
}

/**
 * component-wise addition assignment operator
 */
mat2& mat2::operator +=(const float& a) {
    *this = *this + a;
    return *this;
}

/**
 * component-wise subtraction assignment operator
 */
mat2& mat2::operator -=(const mat2& mat) {
    *this = *this - mat;
    return *this;
}

/**
 * component-wise subtraction assignment operator
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
 * component-wise increment
 */
mat2& mat2::operator ++() {
    *this = *this + 1;
    return *this;
}

/**
 * component-wise decrement
 */
mat2& mat2::operator --() {
    *this = *this + 1;
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

#pragma endregion mat2
