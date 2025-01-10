#ifndef ENGINE_MATRIX
#define ENGINE_MATRIX

#include <array>
#include <string>
#include <iostream>

namespace Engine {

/**
 * An MxN row-major matrix of float
 */
template<unsigned int M, unsigned int N>
class matf {
    private:
    // components
    std::array<float, M*N> data;

    public:

    /*
    required constants:
    identity
    zero
    one
    */

    /*
    required constructors:
    default
    fill
    concatenation
    */

    /*
    required operators:
    addition
    subtraction
    multiplication
    assignment
    comparison
    */

    /*
    required matrix operations / generators:
    transpose
    inverse
    determinant
    trace

    rotation
    skew
    scale
    diagonal
    basis
    projection
    */
};

}

#endif