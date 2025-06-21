#ifndef ENGINE_COLLISIONMESH
#define ENGINE_COLLISIONMESH

#include "../Utils.hpp"

namespace Engine::Physics {
  typedef enum {
    SPHERE,
    BOX,
    POINT
  } Shapes;

  union ShapeData {
    struct {
      float radius;
    } Sphere;
    Vec3f Box;
  };

  /**
   * @brief a dynamic physics mesh used to determine collision types
   *
   * shapeData is a union that holds the data for the shape of the mesh.
   * Depending on the shape, the mesh accesses the information needed to
   * determine collision equations.
   */
  struct Mesh {
    Shapes shape;
    ShapeData shapeData;
  };

  /**
   * @brief creates a box mesh with the given dimensions
   * @param w width of the box
   * @param h height of the box
   * @param l length of the box
   * @return a Mesh object representing the box
   */
  extern Mesh BoxMesh(float w, float h, float l);
  extern Mesh SphereMesh(float radius);
};

#endif
