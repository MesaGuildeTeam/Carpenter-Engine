# Vectors

## Construction

```cpp
// Default
vec3 a = vec3(); // a = [0, 0, 0]

// Fill with scalar vaule
a = vec3(3); // a = [3, 3, 3]

// Construct from vectors or scalars of total dimension = 3
// total dimension: 1 + 1 + 1 = 3
a = vec3(1,2,3); // a = [1,2,3]
// total dimension: 2 + 1 = 3
a = vec3(vec2(1,2),3); // a = [1,2,3]

// Use bracket notation
vec3 a = {1,2,3}; // a = [1,2,3]
```

## Accessors

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
// Normalize
// 
// Dot product
```

## Vector Constants

```cpp
vec3::up; // = [0,1,0]
vec4::zero; // = [0,0,0,0]
```