#ifndef ENGINE_MESH
#define ENGINE_MESH

#include "../Utils.hpp"
#include <vector>

namespace Engine::Graphics { 

  /**
   * A structure used to store mesh vertices. 
   * Each vertex has a position, texture coordinate, and normal vector which can be processed in shaders.
   * Positions and coordinates are required, however normals are predefined or calculated if not provided.
   */
  struct Vertex {
    float x, y, z, u, v;
    float nx = 0.0f, ny = 0.0f, nz = 1.0f;

    /**
     * Calculates the normal vector of the triangle.
     * takes this vector this method is associated with and two other 
     * vertices to calculate the normal of the triangle.
     * 
     * @param v2 The second vertex of the triangle
     * @param v3 The third vertex of the triangle
     */
    void CalculateNormals(Vertex& v2, Vertex& v3);

    bool operator==(const Vertex& rhs);
  };

  /**
   * An abstract class that stores mesh data to the game engine
   * To create a mesh, you will need to derive from this class. 
   * There will potentially be a class in the future to generate new meshes
   * @caution All triangles must be loaded in counter-clockwise order due to 
   * OpenGL's winding order.
   * @author Roberto Selles
   */
  class Mesh {
    private:
      std::vector<Vertex> m_vertices;
      std::vector<unsigned short> m_indices;

    protected:

      /**
       * Adds a triangle to the mesh, and computes the normals for the vertices
       * 
       * Until further notice, this method will be deprecated. It will still work, but it will not behave as intended
       * 
       * @param v1 The first vertex of the triangle
       * @param v2 The second vertex of the triangle
       * @param v3 The third vertex of the triangle
       * 
       */
      Success AddTriangle(Vertex v1, Vertex v2, Vertex v3);

      /**
       * Adds a quad to the mesh, and computes the normals for the vertices
       * 
       * @param v1 The first vertex of the quad
       * @param v2 The second vertex of the quad
       * @param v3 The third vertex of the quad
       * @param v4 The fourth vertex of the quad
       */
      Success AddQuad(Vertex v1, Vertex v2, Vertex v3, Vertex v4);

    public:

      /**
       * Returns a pointer to float C array of vertices
       * This output is designed to be ready for OpenGL use
       */
      float* GetVertices();

      /**
       * Returns a pointer to float C array of vertices
       * This output is designed to be ready for OpenGL use
       */
      unsigned short* GetIndices();

      /**
       * Returns the number of indeces in the index buffer
       */
      unsigned long GetIndexCount();
  };

}

#endif