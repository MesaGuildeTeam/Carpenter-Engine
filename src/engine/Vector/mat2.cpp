#include "mat2.hpp"
#include <cmath>

namespace Engine {

#pragma region constants


const mat2 mat2::identity = mat2(1);

const mat2 mat2::zero = mat2(0);

const mat2 mat2::one = mat2(vec2(1), vec2(1));

#pragma endregion constants

#pragma region constructors


mat2::mat2() {
    data.fill(vec2(0));
}


mat2::mat2(const mat2& mat) {
    for (unsigned int i = 0; i < N; i++) {
        data[i] = mat[i];
    }
}



#pragma endregion constructors

#pragma region accessors


vec2& mat2::operator [](unsigned int i) {
    if (i >= N) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}


const vec2& mat2::operator [](unsigned int i) const {
    if (i >= N) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

#pragma endregion accessors

#pragma region iteration


auto mat2::begin() noexcept {
    return data.begin();
}


auto mat2::end() noexcept {
    return data.end();
}


auto mat2::begin() const noexcept {
    return data.begin();
}


auto mat2::end() const noexcept {
    return data.end();
}


auto mat2::cbegin() const noexcept {
    return data.cbegin();
}


auto mat2::cend() const noexcept {
    return data.cend();
}


auto mat2::rbegin() noexcept {
    return data.rbegin();
}


auto mat2::rend() noexcept {
    return data.rend();
}


auto mat2::rbegin() const noexcept {
    return data.rbegin();
}


auto mat2::rend() const noexcept {
    return data.rend();
}


auto mat2::crbegin() const noexcept {
    return data.crbegin();
}


auto mat2::crend() const noexcept {
    return data.crend();
}

#pragma endregion iteration

#pragma region conversions


std::array<float,mat2::N*mat2::N> mat2::flatten(const mat2& mat) {
    return {mat.data[0][0], mat.data[0][1], mat.data[1][0], mat.data[1][1]};
}


std::array<float,mat2::N*mat2::N> mat2::flatten() const {
    return flatten(*this);
}


std::array<float,mat2::N*mat2::N> mat2::flatten_row(const mat2& mat) {
    return {mat.data[0][0], mat.data[1][0], mat.data[0][1], mat.data[1][1]};
}


std::array<float,mat2::N*mat2::N> mat2::flatten_row() const {
    return flatten_row(*this);
}


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


mat2& mat2::operator =(const mat2& other){
    for (unsigned int i = 0; i < N; i++) {
        data[i] = other.data[i];
    }
    return *this;
}


mat2 operator +(const mat2& a, const mat2& b){
    mat2 result;
    for (unsigned int i = 0; i < mat2::N; i++) {
        result.data[i] = a.data[i] + b.data[i];
    }
    return result;
}


mat2 operator +(const float& a, const mat2& b){
    mat2 result;
    for (unsigned int i = 0; i < mat2::N; i++) {
        result.data[i] = a + b.data[i];
    }
    return result;
}


mat2 operator +(const mat2& a, const float& b){
    mat2 result;
    for (unsigned int i = 0; i < mat2::N; i++) {
        result.data[i] = a.data[i] + b;
    }
    return result;
}


mat2 operator -(const mat2& a, const mat2& b){
    mat2 result;
    for (unsigned int i = 0; i < mat2::N; i++) {
        result.data[i] = a.data[i] - b.data[i];
    }
    return result;
}


mat2 operator -(const float& a, const mat2& b){
    mat2 result;
    for (unsigned int i = 0; i < mat2::N; i++) {
        result.data[i] = a - b.data[i];
    }
    return result;
}


mat2 operator -(const mat2& a, const float& b){
    mat2 result;
    for (unsigned int i = 0; i < mat2::N; i++) {
        result.data[i] = a.data[i] - b;
    }
    return result;
}


mat2 mat2::operator -() const {
    mat2 result;
    for (unsigned int i = 0; i < N; i++) {
        result.data[i] = -data[i];
    }
    return result;
}


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


vec2 operator *(const mat2& a, const vec2& b){
    vec2 result;
    for (unsigned int i = 0; i < mat2::N; i++) {
        result += a[i]*b[i];
    }
    return result;
}


mat2 operator *(const float& a, const mat2& b){
    mat2 result;
    for (unsigned int i = 0; i < mat2::N; i++) {
        result[i] = a*b[i];
    }
    return result;
}


mat2 operator *(const mat2& a, const float& b){
    mat2 result;
    for (unsigned int i = 0; i < mat2::N; i++) {
        result[i] = a[i]*b;
    }
    return result;
}


bool operator ==(const mat2& a, const mat2& b){
    for (unsigned int i = 0; i < mat2::N; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}


bool operator !=(const mat2& a, const mat2& b){
    for (unsigned int i = 0; i < mat2::N; i++) {
        if (a[i] != b[i]) return true;
    }
    return false;
}


mat2& mat2::operator +=(const mat2& mat) {
    *this = *this + mat;
    return *this;
}


mat2& mat2::operator +=(const float& a) {
    *this = *this + a;
    return *this;
}


mat2& mat2::operator -=(const mat2& mat) {
    *this = *this - mat;
    return *this;
}


mat2& mat2::operator -=(const float& a) {
    *this = *this - a;
    return *this;
}


mat2& mat2::operator *=(const mat2& mat) {
    *this = *this * mat;
    return *this;
}


mat2& mat2::operator *=(const float& a) {
    *this = *this * a;
    return *this;
}


mat2& mat2::operator ++() {
    *this = *this + 1.0f;
    return *this;
}


mat2& mat2::operator --() {
    *this = *this - 1.0f;
    return *this;
}

#pragma endregion overloads

#pragma region matrix operations


float mat2::determinant() const {
    return data[0][0]*data[1][1] - data[0][1]*data[1][0];
}


mat2 mat2::transpose() const {
    mat2 result;
    for (unsigned int i = 0; i < N; i++) {
        for (unsigned int j = 0; j < N; j++) {
            result[i][j] = data[j][i];
        }
    }
    return result;
}


mat2 mat2::inverse() const {
    const mat2& mat = *this;
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


float mat2::trace() const {
    return data[0][0] + data[1][1] + data[2][2];
}


mat2 rotation(const float& angle) {
    float s = sinf(angle);
    float c = cosf(angle);
    return mat2(
        c, s,
        -s, c
    );
}


mat2 skew(const vec2& skew) {
    return mat2(
        1, skew.x,
        skew.y, 1
    );
}


mat2 scale(const vec2& scale) {
    return mat2(
        scale.x, 0,
        0, scale.y
    );
}


mat2 basis(const vec2& x, const vec2& y) {
    return mat2(x, y);
}


mat2 basis(const vec2& x) {
    return mat2(x, x.tangent());
}


std::string to_string(const mat2& mat) {
    return "[ " + std::to_string(mat[0][0]) + " " + std::to_string(mat[0][1]) + " ]\n[ " + std::to_string(mat[1][0]) + " " + std::to_string(mat[1][1]) + " ]";
}

#pragma endregion matrix operations

}
