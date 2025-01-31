#include "mat4.hpp"
#include <cmath>

namespace Engine {

#pragma region constants


const mat4 mat4::identity = mat4(1);

const mat4 mat4::zero = mat4(0);

const mat4 mat4::one = mat4(vec4(1), vec4(1), vec4(1), vec4(1));

#pragma endregion constants

#pragma region constructors


mat4::mat4() {
    data.fill(vec4(0));
}


mat4::mat4(const mat4& mat) {
    for (unsigned int i = 0; i < N; i++) {
        data[i] = mat[i];
    }
}



#pragma endregion constructors

#pragma region accessors


vec4& mat4::operator [](unsigned int i) {
    if (i >= N) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}


const vec4& mat4::operator [](unsigned int i) const {
    if (i >= N) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

#pragma endregion accessors

#pragma region iteration


auto mat4::begin() noexcept {
    return data.begin();
}


auto mat4::end() noexcept {
    return data.end();
}


auto mat4::begin() const noexcept {
    return data.begin();
}


auto mat4::end() const noexcept {
    return data.end();
}


auto mat4::cbegin() const noexcept {
    return data.cbegin();
}


auto mat4::cend() const noexcept {
    return data.cend();
}


auto mat4::rbegin() noexcept {
    return data.rbegin();
}


auto mat4::rend() noexcept {
    return data.rend();
}


auto mat4::rbegin() const noexcept {
    return data.rbegin();
}


auto mat4::rend() const noexcept {
    return data.rend();
}


auto mat4::crbegin() const noexcept {
    return data.crbegin();
}


auto mat4::crend() const noexcept {
    return data.crend();
}

#pragma endregion iteration

#pragma region conversions


std::array<float,mat4::N*mat4::N> mat4::flatten(const mat4& mat) {
    return {mat.data[0][0], mat.data[0][1], mat.data[0][2], mat.data[0][3], mat.data[1][0], mat.data[1][1], mat.data[1][2], mat.data[1][3], mat.data[2][0], mat.data[2][1], mat.data[2][2], mat.data[2][3], mat.data[3][0], mat.data[3][1], mat.data[3][2], mat.data[3][3]};
}


std::array<float,mat4::N*mat4::N> mat4::flatten() const {
    return flatten(*this);
}


std::array<float,mat4::N*mat4::N> mat4::flatten_row(const mat4& mat) {
    return {mat.data[0][0], mat.data[1][0], mat.data[2][0], mat.data[3][0], mat.data[0][1], mat.data[1][1], mat.data[2][1], mat.data[3][1], mat.data[0][2], mat.data[1][2], mat.data[2][2], mat.data[3][2], mat.data[0][3], mat.data[1][3], mat.data[2][3], mat.data[3][3]};
}


std::array<float,mat4::N*mat4::N> mat4::flatten_row() const {
    return flatten_row(*this);
}


mat4::operator bool() const {
    for (unsigned int i = 0; i < N; i++) {
        for (unsigned int j = 0; j < N; j++) {
            if (data[i][j] == 0) return false;
        }
    }
    return true;
}

#pragma endregion conversions

#pragma region overloads


mat4& mat4::operator =(const mat4& other){
    for (unsigned int i = 0; i < N; i++) {
        data[i] = other.data[i];
    }
    return *this;
}


mat4 operator +(const mat4& a, const mat4& b){
    mat4 result;
    for (unsigned int i = 0; i < mat4::N; i++) {
        result.data[i] = a.data[i] + b.data[i];
    }
    return result;
}


mat4 operator +(const float& a, const mat4& b){
    mat4 result;
    for (unsigned int i = 0; i < mat4::N; i++) {
        result.data[i] = a + b.data[i];
    }
    return result;
}


mat4 operator +(const mat4& a, const float& b){
    mat4 result;
    for (unsigned int i = 0; i < mat4::N; i++) {
        result.data[i] = a.data[i] + b;
    }
    return result;
}


mat4 operator -(const mat4& a, const mat4& b){
    mat4 result;
    for (unsigned int i = 0; i < mat4::N; i++) {
        result.data[i] = a.data[i] - b.data[i];
    }
    return result;
}


mat4 operator -(const float& a, const mat4& b){
    mat4 result;
    for (unsigned int i = 0; i < mat4::N; i++) {
        result.data[i] = a - b.data[i];
    }
    return result;
}


mat4 operator -(const mat4& a, const float& b){
    mat4 result;
    for (unsigned int i = 0; i < mat4::N; i++) {
        result.data[i] = a.data[i] - b;
    }
    return result;
}


mat4 mat4::operator -() const {
    mat4 result;
    for (unsigned int i = 0; i < N; i++) {
        result.data[i] = -data[i];
    }
    return result;
}


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


vec4 operator *(const mat4& a, const vec4& b){
    vec4 result;
    for (unsigned int i = 0; i < mat4::N; i++) {
        result += a[i]*b[i];
    }
    return result;
}


mat4 operator *(const float& a, const mat4& b){
    mat4 result;
    for (unsigned int i = 0; i < mat4::N; i++) {
        result[i] = a*b[i];
    }
    return result;
}


mat4 operator *(const mat4& a, const float& b){
    mat4 result;
    for (unsigned int i = 0; i < mat4::N; i++) {
        result[i] = a[i]*b;
    }
    return result;
}


bool operator ==(const mat4& a, const mat4& b){
    for (unsigned int i = 0; i < mat4::N; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}


bool operator !=(const mat4& a, const mat4& b){
    for (unsigned int i = 0; i < mat4::N; i++) {
        if (a[i] != b[i]) return true;
    }
    return false;
}


mat4& mat4::operator +=(const mat4& mat) {
    *this = *this + mat;
    return *this;
}


mat4& mat4::operator +=(const float& a) {
    *this = *this + a;
    return *this;
}


mat4& mat4::operator -=(const mat4& mat) {
    *this = *this - mat;
    return *this;
}


mat4& mat4::operator -=(const float& a) {
    *this = *this - a;
    return *this;
}


mat4& mat4::operator *=(const mat4& mat) {
    *this = *this * mat;
    return *this;
}


mat4& mat4::operator *=(const float& a) {
    *this = *this * a;
    return *this;
}


mat4& mat4::operator ++() {
    *this = *this + 1.0f;
    return *this;
}


mat4& mat4::operator --() {
    *this = *this - 1.0f;
    return *this;
}

#pragma endregion overloads

#pragma region matrix operations


mat4 mat4::transpose() const {
    mat4 result;
    for (unsigned int i = 0; i < N; i++) {
        for (unsigned int j = 0; j < N; j++) {
            result[i][j] = data[j][i];
        }
    }
    return result;
}


float mat4::trace() const {
    return data[0][0] + data[1][1] + data[2][2] + data[3][3];
}


mat4 skew(const vec4& skew) {
    return mat4(
        1, skew.x, skew.x, skew.x,
        skew.y, 1, skew.y, skew.y,
        skew.z, skew.z, 1, skew.z,
        skew.w, skew.w, skew.w, 1
    );
}


mat4 scale(const vec4& scale) {
    return mat4(
        scale.x, 0, 0, 0,
        0, scale.y, 0, 0,
        0, 0, scale.z, 0,
        0, 0, 0, scale.w
    );
}


mat4 basis(const vec4& x, const vec4& y, const vec4& z, const vec4& w) {
    return mat4(x, y, z, w);
}


std::string to_string(const mat4& mat) {
    return "[ " + std::to_string(mat[0][0]) + " " + std::to_string(mat[0][1]) + " " + std::to_string(mat[0][2]) + " " + std::to_string(mat[0][3]) + 
    " ]\n[ " + std::to_string(mat[1][0]) + " " + std::to_string(mat[1][1]) + " " + std::to_string(mat[1][2]) + " " + std::to_string(mat[1][3]) + 
    " ]\n[ " + std::to_string(mat[2][0]) + " " + std::to_string(mat[2][1]) + " " + std::to_string(mat[2][2]) + " " + std::to_string(mat[2][3]) + 
    " ]\n[ " + std::to_string(mat[3][0]) + " " + std::to_string(mat[3][1]) + " " + std::to_string(mat[3][2]) + " " + std::to_string(mat[3][3]) + 
    " ]\n[ " + std::to_string(mat[4][0]) + " " + std::to_string(mat[4][1]) + " " + std::to_string(mat[4][2]) + " " + std::to_string(mat[4][3]) + " ]";
}


#pragma endregion matrix operations

}
