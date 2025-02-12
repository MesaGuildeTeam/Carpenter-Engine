#include "mat3.hpp"
#include <cmath>

namespace Engine {

#pragma region constants


const mat3 mat3::identity = mat3(1);

const mat3 mat3::zero = mat3(0);

const mat3 mat3::one = mat3(vec3(1), vec3(1), vec3(1));

#pragma endregion constants

#pragma region constructors


mat3::mat3() {
    data.fill(vec3(0));
}


mat3::mat3(const mat3& mat) {
    for (unsigned int i = 0; i < N; i++) {
        data[i] = mat[i];
    }
}



#pragma endregion constructors

#pragma region accessors


vec3& mat3::operator [](unsigned int i) {
    if (i >= N) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}


const vec3& mat3::operator [](unsigned int i) const {
    if (i >= N) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

#pragma endregion accessors

#pragma region iteration


mat3::iterator mat3::begin() noexcept {
    return data.begin();
}


mat3::iterator mat3::end() noexcept {
    return data.end();
}


mat3::const_iterator mat3::begin() const noexcept {
    return data.begin();
}


mat3::const_iterator mat3::end() const noexcept {
    return data.end();
}


mat3::const_iterator mat3::cbegin() const noexcept {
    return data.cbegin();
}


mat3::const_iterator mat3::cend() const noexcept {
    return data.cend();
}


mat3::reverse_iterator mat3::rbegin() noexcept {
    return data.rbegin();
}


mat3::reverse_iterator mat3::rend() noexcept {
    return data.rend();
}


mat3::const_reverse_iterator mat3::rbegin() const noexcept {
    return data.rbegin();
}


mat3::const_reverse_iterator mat3::rend() const noexcept {
    return data.rend();
}


mat3::const_reverse_iterator mat3::crbegin() const noexcept {
    return data.crbegin();
}


mat3::const_reverse_iterator mat3::crend() const noexcept {
    return data.crend();
}

#pragma endregion iteration

#pragma region conversions


std::array<float,mat3::N*mat3::N> mat3::flatten(const mat3& mat) {
    return {mat.data[0][0], mat.data[0][1], mat.data[0][2], mat.data[1][0], mat.data[1][1], mat.data[1][2], mat.data[2][0], mat.data[2][1], mat.data[2][2]};
}


std::array<float,mat3::N*mat3::N> mat3::flatten() const {
    return flatten(*this);
}


std::array<float,mat3::N*mat3::N> mat3::flatten_row(const mat3& mat) {
    return {mat.data[0][0], mat.data[1][0], mat.data[2][0], mat.data[0][1], mat.data[1][1], mat.data[2][1], mat.data[0][2], mat.data[1][2], mat.data[2][2]};
}


std::array<float,mat3::N*mat3::N> mat3::flatten_row() const {
    return flatten_row(*this);
}


mat3::operator bool() const {
    for (unsigned int i = 0; i < N; i++) {
        for (unsigned int j = 0; j < N; j++) {
            if (data[i][j] == 0) return false;
        }
    }
    return true;
}

#pragma endregion conversions

#pragma region overloads


mat3& mat3::operator =(const mat3& other){
    for (unsigned int i = 0; i < N; i++) {
        data[i] = other.data[i];
    }
    return *this;
}


mat3 operator +(const mat3& a, const mat3& b){
    mat3 result;
    for (unsigned int i = 0; i < mat3::N; i++) {
        result.data[i] = a.data[i] + b.data[i];
    }
    return result;
}


mat3 operator +(const float& a, const mat3& b){
    mat3 result;
    for (unsigned int i = 0; i < mat3::N; i++) {
        result.data[i] = a + b.data[i];
    }
    return result;
}


mat3 operator +(const mat3& a, const float& b){
    mat3 result;
    for (unsigned int i = 0; i < mat3::N; i++) {
        result.data[i] = a.data[i] + b;
    }
    return result;
}


mat3 operator -(const mat3& a, const mat3& b){
    mat3 result;
    for (unsigned int i = 0; i < mat3::N; i++) {
        result.data[i] = a.data[i] - b.data[i];
    }
    return result;
}


mat3 operator -(const float& a, const mat3& b){
    mat3 result;
    for (unsigned int i = 0; i < mat3::N; i++) {
        result.data[i] = a - b.data[i];
    }
    return result;
}


mat3 operator -(const mat3& a, const float& b){
    mat3 result;
    for (unsigned int i = 0; i < mat3::N; i++) {
        result.data[i] = a.data[i] - b;
    }
    return result;
}


mat3 mat3::operator -() const {
    mat3 result;
    for (unsigned int i = 0; i < N; i++) {
        result.data[i] = -data[i];
    }
    return result;
}


mat3 operator *(const mat3& a, const mat3& b){
    mat3 result;
    for (unsigned int i = 0; i < mat3::N; i++) {
        for (unsigned int j = 0; j < mat3::N; j++) {
            for (unsigned int k = 0; k < mat3::N; k++) {
                result[j][i] += a[k][i] * b[j][k];
            }
        }
    }
    return result;
}


vec3 operator *(const mat3& a, const vec3& b){
    vec3 result;
    for (unsigned int i = 0; i < mat3::N; i++) {
        result += a[i]*b[i];
    }
    return result;
}


mat3 operator *(const float& a, const mat3& b){
    mat3 result;
    for (unsigned int i = 0; i < mat3::N; i++) {
        result[i] = a*b[i];
    }
    return result;
}


mat3 operator *(const mat3& a, const float& b){
    mat3 result;
    for (unsigned int i = 0; i < mat3::N; i++) {
        result[i] = a[i]*b;
    }
    return result;
}


bool operator ==(const mat3& a, const mat3& b){
    for (unsigned int i = 0; i < mat3::N; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}


bool operator !=(const mat3& a, const mat3& b){
    for (unsigned int i = 0; i < mat3::N; i++) {
        if (a[i] != b[i]) return true;
    }
    return false;
}


mat3& mat3::operator +=(const mat3& mat) {
    *this = *this + mat;
    return *this;
}


mat3& mat3::operator +=(const float& a) {
    *this = *this + a;
    return *this;
}


mat3& mat3::operator -=(const mat3& mat) {
    *this = *this - mat;
    return *this;
}


mat3& mat3::operator -=(const float& a) {
    *this = *this - a;
    return *this;
}


mat3& mat3::operator *=(const mat3& mat) {
    *this = *this * mat;
    return *this;
}


mat3& mat3::operator *=(const float& a) {
    *this = *this * a;
    return *this;
}


mat3& mat3::operator ++() {
    *this = *this + 1.0f;
    return *this;
}


mat3& mat3::operator --() {
    *this = *this - 1.0f;
    return *this;
}

#pragma endregion overloads

#pragma region matrix operations


float mat3::determinant() const {
    return data[0][0]*(data[1][1]*data[2][2] - data[2][1]*data[1][2]) + data[0][1]*(data[2][0]*data[1][2] - data[1][0]*data[2][2]) + data[0][2]*(data[1][0]*data[2][1] - data[2][0]*data[1][1]);
}


mat3 mat3::transpose() const {
    mat3 result;
    for (unsigned int i = 0; i < N; i++) {
        for (unsigned int j = 0; j < N; j++) {
            result[i][j] = data[j][i];
        }
    }
    return result;
}


mat3 mat3::inverse() const {
    const mat3& mat = *this;

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


float mat3::trace() const {
    return data[0][0] + data[1][1] + data[2][2];
}


mat3 rotation(const vec3& axis, const float& angle) {
    float s = sinf(angle);
    float c = cosf(angle);
    float t = 1 - c;
    return mat3(
        axis.x*axis.x*t + c, axis.x*axis.y*t + axis.z*s, axis.x*axis.z*t - axis.y*s,
        axis.x*axis.y*t - axis.z*s, axis.y*axis.y*t + c, axis.y*axis.z*t + axis.x*s,
        axis.x*axis.z*t + axis.y*s, axis.y*axis.z*t - axis.x*s, axis.z*axis.z*t + c
    );
}


mat3 rotation(const vec3& a, const vec3& b){
    vec3 na = a/sqrtf(dot(a,a)*dot(b,b));
    vec3 axis = cross(na,b);
    float c = dot(na,b);
    float s = sqrtf(1 - c*c);
    float t = 1 - c;
    return mat3(
        axis.x*axis.x*t + c, axis.x*axis.y*t + axis.z*s, axis.x*axis.z*t - axis.y*s,
        axis.x*axis.y*t - axis.z*s, axis.y*axis.y*t + c, axis.y*axis.z*t + axis.x*s,
        axis.x*axis.z*t + axis.y*s, axis.y*axis.z*t - axis.x*s, axis.z*axis.z*t + c
    );
}


mat3 rotation(const vec3& euler) {
    return rotationX(euler.x) * rotationY(euler.y) * rotationZ(euler.z);
}


mat3 rotationX(const float& angle) {
    float c = cosf(angle);
    float s = sinf(angle);
    return mat3(
        1, 0, 0,
        0, c, -s,
        0, s, c
    );
}


mat3 rotationY(const float& angle) {
    float c = cosf(angle);
    float s = sinf(angle);
    return mat3(
        c, 0, s,
        0, 1, 0,
        -s, 0, c
    );
}


mat3 rotationZ(const float& angle) {
    float c = cosf(angle);
    float s = sinf(angle);
    return mat3(
        c, -s, 0,
        s, c, 0,
        0, 0, 1
    );
}


mat3 skew(const vec3& skew) {
    return mat3(
        1, skew.x, skew.x,
        skew.y, 1, skew.y,
        skew.z, skew.z, 1
    );
}


mat3 scale(const vec3& scale) {
    return mat3(
        scale.x, 0, 0,
        0, scale.y, 0,
        0, 0, scale.z
    );
}


mat3 basis(const vec3& x, const vec3& y) {
    return mat3(x, y, cross(x,y));
}


mat3 basis(const vec3& z) {
    vec3 t = z.tangent();
    return mat3(t, cross(t,z), z);
}


std::string to_string(const mat3& mat) {
    return "[ " + std::to_string(mat[0][0]) + " " + std::to_string(mat[0][1]) + " " + std::to_string(mat[0][2]) + " ]\n[ " + std::to_string(mat[1][0]) + " " + std::to_string(mat[1][1]) + " " + std::to_string(mat[1][2]) + " ]\n[ " + std::to_string(mat[2][0]) + " " + std::to_string(mat[2][1]) + " " + std::to_string(mat[2][2]) + " ]";
}


#pragma endregion matrix operations

}
