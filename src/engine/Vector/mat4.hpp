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
     * identity matrix
     * equivalent to `mat4(1)`
     */
    static const mat4 identity;
    /**
     * matrix of all zeros
     * equivalent to `mat4(0)`
     */
    static const mat4 zero;
    /**
     * matrix of all ones
     */
    static const mat4 one;

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
    mat4();

    /**
     * Copy constructor
     */
    mat4(const mat4& mat);

    /**
     * Fill constructor
     * Fills the matrix diagonal with the provided value
     * The remaining components are set to 0
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
     * @warning vectors and floats are inserted as columns. This means that `mat2(1,2,3,4)` creates the matrix with columns [1,2] and [3,4]
     */
    template <typename ... Vectors>
    requires ((is_vec_v<Vectors> || std::is_convertible_v<Vectors, float>) && ... ) && ((dimension_of_v<Vectors> + ...) == dimension*dimension)
    mat4(const Vectors... vecs) {
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
    vec4& operator [](unsigned int i);

    /**
     * Column accessor 
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
     * unrolls the matrix in column major order (elements in the same column are adjacent in memory)
     */
    static std::array<float,N*N> flatten(const mat4& mat);

    /**
     * unrolls the matrix in column major order (elements in the same column are adjacent in memory)
     */
    std::array<float,N*N> flatten() const;

    /**
     * unrolls the matrix in row major order (elements in the same row are adjacent in memory)
     */
    static std::array<float,N*N> flatten_row(const mat4& mat);

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
    friend std::ostream& operator <<(std::ostream& os, const mat4& mat);

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
     * returns the determinant of this matrix
     */
    //float determinant() const;

    /**
     * returns the determinant of a matrix
     */
    //static float determinant(const mat4& mat);

    /**
     * returns the transpose of this matrix
     */
    mat4 transpose() const;

    /**
     * returns the transpose of a matrix
     */
    static mat4 transpose(const mat4& mat);

    /**
     * returns the inverse of this matrix
     * code modified from https://stackoverflow.com/a/18504573
     */
    //mat4 inverse() const;

    /**
     * returns the inverse of a matrix
     * code modified from https://stackoverflow.com/a/18504573
     */
    //static mat4 inverse(const mat4& mat);

    /**
     * returns the trace of this matrix (sum of diagonal elements)
     */
    float trace() const;

    /**
     * returns the trace of a matrix (sum of diagonal elements)
     */
    static float trace(const mat4& mat);

    /**
     * returns a skew matrix
     */
    static mat4 skew(const vec4& skew);

    /**
     * returns a scale matrix
     * equaivalent to component-wise vector multiplication
     */
    static mat4 scale(const vec4& scale);

    /**
     * returns a basis matrix from 4 vectors
     * equaivalent to just constructing from 4 vectors
     */
    static mat4 basis(const vec4& x, const vec4& y, const vec4& z, const vec4& w);

    #pragma endregion matrix operations
};

}

namespace std {
    
/**
 * converts a matrix to a string
 * note: matrix is printed in column-major order
 */
std::string to_string(const Engine::mat4& mat);

}

#endif