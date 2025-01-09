#include <type_traits>
#include <initializer_list>
#include <stdexcept>
#include <array>
#include <concepts>
#include <cmath>
#include <string>
#include <iterator>

typedef Vector<float, 3> vec3

/**
 * mathematical vector class
 * note: multiplication & division are component-wise
 */
template <typename T, unsigned int N>
class Vector {
    private:
    // components
    std::array<T,N> data;

    public:
    // needed for the concatenation constructor
    using value_type = T;
    using dimension = N;

    #pragma region constructors

    /**
     * default constructor, fills the vector with the default value of the base type (0 for most things)
     */
    Vector() {
        for (int i = 0; i < N; i++) {
            data[i] = T(); // use the type's default constructor (zero value for most things)
        }
    }

    /**
     * fill constructor, fills the vector with the provided scalar value
     */
    Vector(const T& a){
        for (int i = 0; i < N; i++) {
            data[i] = a;
        }
    }

    /**
     * concatenation constructor
     * creates a vector from a list of vectors of a convertible type and of total dimensions summing to the target dimension
     */
    template <IsVectorOf<T>... Vectors>
    Vector(const Vectors&... vectors) {
        // need to handle scalar arguments
        constexpr unsigned int totaldim = (Vectors::dimension + ...);
        static_assert(totaldim == N, "Input dimensions do not sum to target dimension");

        unsigned int i = 0;
        ([&] {
            for (unsigned int j = 0; j < Vectors::dimension; ++j) {
                data[i + j] = vectors[j];
            }
            i += Vectors::dimension;
        }(), ...);
    }

    #pragma endregion constructors

    #pragma region accessors

    /**
     * Array accessor
     * Returns the component at index i, 0-indexed
     */
    T& operator [](unsigned int i) {
        if (i >= N) {
            throw std::out_of_range("Index out of range");
        }
        return data[i];
    }

    const T& operator [](unsigned int i) const {
        if (i >= N) {
            throw std::out_of_range("Index out of range");
        }
        return data[i];
    }

    // position
    /**
     * The 1st component of the vector
     * equivalent to vec[0]
     */
    T& x = data[0];
    /**
     * The 2nd component of the vector
     * equivalent to vec[1]
     */
    T& y = data[1];
    /**
     * The 3rd component of the vector
     * equivalent to vec[2]
     */
    T& z = data[2];
    /**
     * The 4th component of the vector
     * equivalent to vec[3]
     */
    T& w = data[3];

    // color
    /**
     * The 1st component of the vector
     * equivalent to vec[0]
     */
    T& r = data[0];
    /**
     * The 2nd component of the vector
     * equivalent to vec[1]
     */
    T& g = data[1];
    /**
     * The 3rd component of the vector
     * equivalent to vec[2]
     */
    T& b = data[2];
    /**
     * The 4th component of the vector
     * equivalent to vec[3]
     */
    T& a = data[3];

    // texture coordinate
    /**
     * The 1st component of the vector
     * equivalent to vec[0]
     */
    T& u = data[0];
    /**
     * The 2nd component of the vector
     * equivalent to vec[1]
     */
    T& v = data[1];

    #pragma endregion accessors
    
    #pragma region overloads

    /**
     * Copy assignment operator
     */
    Vector<T,N>& operator =(const Vector<T,N>& other) {
        for (unsigned int i = 0; i < N; i++) {
            data[i] = other[i];
        }
        return *this;
    }

    /**
     * component-wise addition operator
     */
    Vector<T,N> operator +(const Vector<T,N>& other) const {
        Vector<T,N> result;
        for (unsigned int i = 0; i < N; i++) {
            result[i] = data[i] + other[i];
        }
        return result;
    }

    /**
     * component-wise subtraction operator
     */
    Vector<T,N> operator -(const Vector<T,N>& other) const {
        Vector<T,N> result;
        for (unsigned int i = 0; i < N; i++) {
            result[i] = data[i] - other[i];
        }
        return result;
    }

    /**
     * component-wise negation operator
     */
    Vector<T,N> operator -() const {
        Vector<T,N> result;
        for (unsigned int i = 0; i < N; i++) {
            result[i] = -data[i];
        }
        return result;
    }

    /**
     * component-wise multiplication operator
     */
    Vector<T,N> operator *(const Vector<T,N>& other) const {
        Vector<T,N> result;
        for (unsigned int i = 0; i < N; i++) {
            result[i] = data[i] * other[i];
        }
        return result;
    }

    /**
     * component-wise division operator
     */
    Vector<T,N> operator /(const Vector<T,N>& other) const {
        Vector<T,N> result;
        for (unsigned int i = 0; i < N; i++) {
            result[i] = data[i] / other[i];
        }
        return result;
    }

    /**
     * component-wise modulo operator
     */
    Vector<T,N> operator %(const Vector<T,N>& other) const {
        Vector<T,N> result;
        for (unsigned int i = 0; i < N; i++) {
            result[i] = data[i] % other[i];
        }
        return result;
    }

    /**
     * component-wise bitwise and operator
     */
    Vector<T,N> operator &(const Vector<T,N>& other) const {
        Vector<T,N> result;
        for (unsigned int i = 0; i < N; i++) {
            result[i] = data[i] & other[i];
        }
        return result;
    }

    /**
     * component-wise bitwise or operator
     */
    Vector<T,N> operator |(const Vector<T,N>& other) const {
        Vector<T,N> result;
        for (unsigned int i = 0; i < N; i++) {
            result[i] = data[i] | other[i];
        }
        return result;
    }

    /**
     * component-wise bitwise xor operator
     */
    Vector<T,N> operator ^(const Vector<T,N>& other) const {
        Vector<T,N> result;
        for (unsigned int i = 0; i < N; i++) {
            result[i] = data[i] ^ other[i];
        }
        return result;
    }

    /**
     * component-wise bitwise not operator
     */
    Vector<T,N> operator ~(const Vector<T,N>& other) const {
        Vector<T,N> result;
        for (unsigned int i = 0; i < N; i++) {
            result[i] = ~data[i];
        }
        return result;
    }

    /**
     * component-wise shift left operator
     */
    Vector<T,N> operator <<(const Vector<T,N>& other) const {
        Vector<T,N> result;
        for (unsigned int i = 0; i < N; i++) {
            result[i] = data[i] << other[i];
        }
        return result;
    }

    /**
     * component-wise shift right operator
     */
    Vector<T,N> operator >>(const Vector<T,N>& other) const {
        Vector<T,N> result;
        for (unsigned int i = 0; i < N; i++) {
            result[i] = data[i] >> other[i];
        }
        return result;
    }

    /**
     * component-wise equality operator
     */
    Vector<bool,N> operator ==(const Vector<T,N>& other) const {
        Vector<T,N> result;
        for (unsigned int i = 0; i < N; i++) {
            result[i] = data[i] == other[i];
        }
        return result;
    }

    /**
     * component-wise inequality operator
     */
    Vector<bool,N> operator !=(const Vector<T,N>& other) const {
        Vector<T,N> result;
        for (unsigned int i = 0; i < N; i++) {
            result[i] = data[i] != other[i];
        }
        return result;
    }

    /**
     * component-wise less than operator
     */
    Vector<bool,N> operator <(const Vector<T,N>& other) const {
        Vector<T,N> result;
        for (unsigned int i = 0; i < N; i++) {
            result[i] = data[i] < other[i];
        }
        return result;
    }

    /**
     * component-wise greater than operator
     */
    Vector<bool,N> operator >(const Vector<T,N>& other) const {
        Vector<T,N> result;
        for (unsigned int i = 0; i < N; i++) {
            result[i] = data[i] > other[i];
        }
        return result;
    }

    /**
     * component-wise less than or equal to operator
     */
    Vector<bool,N> operator <=(const Vector<T,N>& other) const {
        Vector<T,N> result;
        for (unsigned int i = 0; i < N; i++) {
            result[i] = data[i] <= other[i];
        }
        return result;
    }

    /**
     * component-wise greater than or equal to operator
     */
    Vector<bool,N> operator >=(const Vector<T,N>& other) const {
        Vector<T,N> result;
        for (unsigned int i = 0; i < N; i++) {
            result[i] = data[i] >= other[i];
        }
        return result;
    }

    /**
     * component-wise logical and operator
     */
    Vector<bool,N> operator &&(const Vector<T,N>& other) const {
        Vector<T,N> result;
        for (unsigned int i = 0; i < N; i++) {
            result[i] = data[i] && other[i];
        }
        return result;
    }

    /**
     * component-wise logical or operator
     */
    Vector<bool,N> operator ||(const Vector<T,N>& other) const {
        Vector<T,N> result;
        for (unsigned int i = 0; i < N; i++) {
            result[i] = data[i] || other[i];
        }
        return result;
    }

    /**
     * component-wise logical not operator
     */
    Vector<bool,N> operator !(const Vector<T,N>& other) const {
        Vector<T,N> result;
        for (unsigned int i = 0; i < N; i++) {
            result[i] = !data[i];
        }
        return result;
    }

    /**
     * component-wise increment operator
     */
    Vector<T,N> operator ++() {
        for (unsigned int i = 0; i < N; i++) {
            data[i] ++;
        }
        return *this;
    }

    /**
     * component-wise decrement operator
     */
    Vector<T,N> operator --() {
        for (unsigned int i = 0; i < N; i++) {
            data[i] --;
        }
        return *this;
    }

    /**
     * component-wise addition assignment operator
     */
    Vector<T,N> operator +=(const Vector<T,N>& other) {
        for (unsigned int i = 0; i < N; i++) {
            data[i] += other[i];
        }
        return *this;
    }

    /**
     * component-wise subtraction assignment operator
     */
    Vector<T,N> operator -=(const Vector<T,N>& other) {
        for (unsigned int i = 0; i < N; i++) {
            data[i] -= other[i];
        }
        return *this;
    }

    /**
     * component-wise multiplication assignment operator
     */
    Vector<T,N> operator *=(const Vector<T,N>& other) {
        for (unsigned int i = 0; i < N; i++) {
            data[i] *= other[i];
        }
        return *this;
    }

    /**
     * component-wise division assignment operator
     */
    Vector<T,N> operator /=(const Vector<T,N>& other) {
        for (unsigned int i = 0; i < N; i++) {
            data[i] /= other[i];
        }
        return *this;
    }

    /**
     * component-wise modulo assignment operator
     */
    Vector<T,N> operator %=(const Vector<T,N>& other) {
        for (unsigned int i = 0; i < N; i++) {
            data[i] %= other[i];
        }
        return *this;
    }

    /**
     * component-wise bitwise and assignment operator
     */
    Vector<T,N> operator &=(const Vector<T,N>& other) {
        for (unsigned int i = 0; i < N; i++) {
            data[i] &= other[i];
        }
        return *this;
    }

    /**
     * component-wise bitwise or assignment operator
     */
    Vector<T,N> operator |=(const Vector<T,N>& other) {
        for (unsigned int i = 0; i < N; i++) {
            data[i] |= other[i];
        }
        return *this;
    }

    /**
     * component-wise bitwise xor assignment operator
     */
    Vector<T,N> operator ^=(const Vector<T,N>& other) {
        for (unsigned int i = 0; i < N; i++) {
            data[i] ^= other[i];
        }
        return *this;
    }

    /**
     * component-wise shift left assignment operator
     */
    Vector<T,N> operator <<=(const Vector<T,N>& other) {
        for (unsigned int i = 0; i < N; i++) {
            data[i] <<= other[i];
        }
        return *this;
    }

    /**
     * component-wise shift right assignment operator
     */
    Vector<T,N> operator >>=(const Vector<T,N>& other) {
        for (unsigned int i = 0; i < N; i++) {
            data[i] >>= other[i];
        }
        return *this;
    }

    #pragma endregion overloads

    #pragma region iterator functions

    /**
     * iterator to the first component
     */
    auto begin() noexcept {
        return data.begin();
    }

    /**
     * iterator to the end of the components
     */
    auto end() noexcept {
        return data.end();
    }

    /**
     * iterator to the first component
     */
    auto begin() const noexcept {
        return data.begin();
    }

    /**
     * iterator to the end of the components
     */
    auto end() const noexcept {
        return data.end();
    }

    /**
     * iterator to the first component
     */
    auto cbegin() const noexcept {
        return data.cbegin();
    }

    /**
     * iterator to the end of the components
     */
    auto cend() const noexcept {
        return data.cend();
    }

    /**
     * reverse iterator to the first component
     */
    auto rbegin() noexcept {
        return data.rbegin();
    }

    /**
     * reverse iterator to the end of the components
     */
    auto rend() noexcept {
        return data.rend();
    }

    /**
     * reverse iterator to the first component
     */
    auto rbegin() const noexcept {
        return data.rbegin();
    }

    /**
     * reverse iterator to the end of the components
     */
    auto rend() const noexcept {
        return data.rend();
    }

    /**
     * reverse iterator to the first component
     */
    auto crbegin() const noexcept {
        return data.crbegin();
    }

    /**
     * reverse iterator to the end of the components
     */
    auto crend() const noexcept {
        return data.crend();
    }

    #pragma endregion iterator functions

    // misc

    /**
     * converts a vector to a string
     */
    friend std::to_string(const Vector<T,N>& vec) {
        std::string result = "[";
        for (unsigned int i = 0; i < N; i++) {
            result += std::to_string(vec[i]);
            if (i != N - 1) {
                result += ", ";
            }
        }
        result += "]";
        return result;
    }

    /**
     * casts a vector to bool
     * true if all components cast to true
     */
    explicit operator bool() const {
        for (unsigned int i = 0; i < N; i++) {
            if (!bool(data[i])) {
                return false;
            }
        }
        return true;
    }

    /**
     * Returns the dimension of a vector
     */
    unsigned int dim() const {
        return N;
    }
    

    #pragma region vector operations
    
    /**
     * dot product of two vectors
     */
    friend T dot(const Vector<T,N>& a, const Vector<T,N>& b) const {
        T result = T();
        for (int i = 0; i < N; i++) {
            result += a[i]*b[i];
        }
        return result;
    }

    /**
     * angle between two vectors
     */
    friend double angleBetween(const Vector<T,N>& a, const Vector<T,N>& b) const {
        return acos( dot(other) / sqrt(a.lengthSquared()*b.lengthSquared()) );
    }

    /**
     * cross product of two vectors
     * defined only for 2d and 3d vectors
     * for 2d vectors, returns a scalar
     * for 3d vectors, returns a vector tangent to both input vectors
     */
    template <typename = std::enable_if_t<N == 2>>
    friend T cross(const Vector<T,2>& a, const Vector<T,2>& b) const {
        return a.x*b.y - a.y*a.x;
    }

    /**
     * cross product of two vectors
     * defined only for 2d and 3d vectors
     * for 2d vectors, returns a scalar
     * for 3d vectors, returns a vector tangent to both input vectors
     */
    template <typename = std::enable_if_t<N == 3>>
    friend Vector<T,3> cross(const Vector<T,3>& a, const Vector<T,3>& b) const {
        return Vector<T,3>(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
    }

    /**
     * distance between two vectors
     */
    template <typename = std::enable_if_t<N == 3>>
    friend Vector<T,3> cross(const Vector<T,3>& a, const Vector<T,3>& b) const {
        return Vector<T,3>(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
    }

    /**
     * reflects incident vector, I, over normal, N
     */
    friend Vector<T,N> reflect(const Vector<T,N>& I, const Vector<T,N>& N) const {
        I - 2.0 * dot(N, I) * N
    }

    /**
     * returns a vector in the same direction as the input vector, but with a length of 1
     */
    friend Vector<T,N> normalize(const Vector<T,N>& vec) {
        return vec/vec.length();
    }

    /**
     * returns a vector in the same direction as this vector, but with a length of 1
     */
    Vector<T,N> normalized() {
        return *this/length();
    }

    /**
     * returns the distance between two vectors
     */
    friend T distanceSquared(const Vector<T,N>& other) {
        return (other - *this).lengthSquared();
    }

    /**
     * returns the distance between two vectors
     */
    friend T distance(const Vector<T,N>& other) {
        return (other - *this).length();
    }

    /**
     * Returns the length squared of the vector
     * equivalent to dot product with itself
     */
    T lengthSquared() const {
        return dot(*this, *this);
    }

    /**
     * Returns the length of the vector
     */
    T length() const {
        return sqrt(lengthSquared());
    }

    /**
     * Returns a tangent vector of the same length to the current vector
     * in 2d the equation used is (-y, x)
     * in 3d the equation used is (-y,x,0) if |x| <= |z|, else (0,-z,y)
     */
    template <typename = std::enable_if_t<N == 2>>
    Vector<T,2> tangent() const {
        return Vector<T,2>(-y, x);
    }

    /**
     * Returns a tangent vector of the same length to the current vector
     * in 2d the equation used is (-y, x)
     * in 3d the equation used is (-y,x,0) if |x| <= |z|, else (0,-z,y)
     */
    template <typename = std::enable_if_t<N == 3>>
    Vector<T,3> tangent() const {
        Vector<T,3> a = |x| <= |z| ? Vector<T,3>(-y,x,0) : Vector<T,3>(0,-z,y);
        return a*sqrt(lengthSquared()/a.lengthSquared());
    }

    #pragma endregion vector operations
};