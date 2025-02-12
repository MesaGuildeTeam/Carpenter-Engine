# Vectors

## Construction

The following construction methods are supported:

```cpp
// Default
vec3 a = vec3(); // a = [0, 0, 0]

// Fill with scalar vaule
a = vec3(3); // a = [3, 3, 3]

// Construct from vectors or scalars of total dimension = dimension of vector
// total dimension: 1 + 1 + 1 = 3
a = vec3(1,2,3); // a = [1,2,3]
// total dimension: 2 + 1 = 3
a = vec3(vec2(1,2),3); // a = [1,2,3]

// Use bracket notation
vec3 a = {1,2,3}; // a = [1,2,3]
```

## Accessors

Components of vectors may be accessed by component accessors, array access, and iterators.  Any of these methods can read and edit the vector.

```cpp
vec4 a = {1,2,3,4};

// Component access
a.x; // = 1
a.y; // = 2
a.z; // = 3
a.w; // = 4

// Array access
a[0]; // = 1

for (const float& v : a){
    cout << v << ", "
}
// prints "1, 2, 3, 4, "

```

## Common Operations

```cpp
vec3 a = {1,2,3};
vec3 b = {3,0,4};

// Normalize and length
a.normalized().length() // = 1

// Component-wise operations
// multiplication
a*b; // = {3, 0, 12}
// addition
a+b; // = {4, 2, 12}

// Dot product
dot(a,b) // = 1*3 + 2*0 + 3*4

// Comparisons and boolean vectors

// Comparisons result in boolean vectors. eg:
a >= b; // = [false, true, false]
// any component wise comparisons are true
(a >= b).any(); // = true
// all component wise comparisons are true
(a >= b).all(); // = false
// bool vector to bool cast, equivalent to all()
(bool)(a >= b); // = false
```

## Vector Constants

Constants for the standard basis vectors and vectors of all zeros and all ones.

```cpp
vec3::up; // = [0,1,0]
vec4::zero; // = [0,0,0,0]
```

# Matrices

## Construction

```cpp
// Default
mat2 a = mat2(); // a = [0, 0], [0, 0]

// Fill with scalar vaule
a = mat2(3); // a = [3, 0], [0, 3]

// Construct from vectors or scalars of total dimension = dimensions of matrix
// total dimension: 1 + 1 + 1 + 1 = 4
a = mat2(1,2,3,4); // a = [1,2], [3,4]
// total dimension: 3 + 1 = 4
a = mat2(vec3(1,2,3),4); // a = [1,2], [3,4]

// Use bracket notation
mat2 a = {1,2,3,4}; // a = [1,2,3,4]
```

## Accessors

```cpp
mat2 a = {1,2,3,4};

// Component access
a[0][0]; // = 1
a[0][1]; // = 2
a[1][0]; // = 3
a[0][1]; // = 4

// Array access
a[0]; // = [1,2]

for (const float& v : a){
    cout << to_string(v) << ", "
}
// prints "[1, 2], [3, 4], "
```

## Common Operations

```cpp
mat2 a = {1,2,3,4};
mat2 b = {5,6,7,8};
vec2 v = {2,5};

// component wise addition
a + b; // = [6,8], [10,12]

// scalar multiplication
a*2.0f; // = [2,4], [6,8]

// matrix multiplication
a*v; // = [2*1 + 5*3, 2*2 + 5*4]

// matrix determinant
a.determinant(); // does what you think. If you don't know, google it
```

## Transformations

All angles are in radians. 

```cpp
vec3 axis = vec3(1,2,5).normalized();

// Rotations

// axis-angle
rotation(axis, 3.14f/2); // 3x3 rotation matrix of 3.14f/2 about axis
// euler angles
rotation(vec3(3.14f/2, 0, 3.14f/4)); // 3x3 rotation matrix of pi/2 about the x axis, 0 about y, and pi/4 about z
// rotation align
rotation(vec2(1,2), vec2(3,4)); // 2x2 rotation matrix representing a rotation of the angle between [1,2] and [3,4]

// scale
scale(vec4(3,4,5,6)); // 4x4 scale matrix representing a stretch of 3 times on the x axis, 4 times on y, 5 times on z, and 6 times on z

// basis
basis(vec3(1,0,0)); // 3x3 orthonormal basis matrix where [1,0,0] is one of the axies
```

## Matrix Constants

```cpp
mat3::identity; // multiplicative identity matrix
mat4::zero; // matrix of all zeros
mat2::one; // matrix of all ones
```