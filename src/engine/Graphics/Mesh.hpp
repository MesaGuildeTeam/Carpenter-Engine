#ifndef ENGINE_MESH
#define ENGINE_MESH

#include "../Utils.hpp"
#include <vector>

namespace Engine::Graphics { 

  /**
   * @brief A structure used to store mesh vertices.
   * 
   * Each vertex has a position, texture coordinate, and normal vector which can be processed in shaders.
   * Positions and coordinates are required, however normals are predefined or calculated if not provided.
   */
  struct Vertex {
    float x, y, z, u, v;
    float nx = 0.0f, ny = 0.0f, nz = 1.0f;

    /**
     * @brief Calculates the normal vector of the vertices.
     * 
     * takes this vector this method is associated with and two other 
     * vertices to calculate the normal of the triangle.
     * The normal vector is then stored in the three vertex structs.
     * 
     * @param v2 The second vertex of the triangle
     * @param v3 The third vertex of the triangle
     */
    void CalculateNormals(Vertex& v2, Vertex& v3);

    /**
     * @brief Checks if two vertices are equal
     * 
     * @returns True if the vertices are completely identical
     */
    bool operator==(const Vertex& rhs);
  };

  /**
   * @brief An abstract class that stores mesh data to the game engine
   * 
   * To create a usable mesh, you will need to derive from this class.
   * There will potentially be a class in the future to load meshes by file
   * 
   * ## Example
   * 
   * ```cpp
   * class MyMesh : public Engine::Graphics::Mesh {
   *   MyMesh() : Engine::Graphics::Mesh() {
   *      AddTriangle({0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f});
   *   }
   * }
   * 
   * @warning All triangles must be loaded in counter-clockwise order 
   * due to the engine's winding order.
   * 
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
       * @brief Returns a pointer to a float array of vertices.
       * This output is designed to be ready for OpenGL use.
       * 
       * @return A pointer to the vertices array of the mesh
       */
      float* GetVertices();

      /**
       * @brief Returns a pointer to an unsigned int array of indices.
       * This output is designed to be ready for OpenGL use.
       * 
       * @return A pointer to the indices array of the mesh
       */
      unsigned short* GetIndices();

      /**
       * @brief Returns the number of indeces in the index buffer
       * 
       * @return The number of indices
       */
      unsigned long GetIndexCount();
  };

}

#endif