/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

 #ifndef ENGINE_MESH
#define ENGINE_MESH

#include "../Utils.hpp"
#include <vector>

namespace Engine::Graphics { 

  /**
   * @brief A structure used to store mesh vertices.
   * 
   * Each vertex has a position, texture coordinate, and normal vector which can be processed in shaders.
   * Positions and coordinates are required. However, normal vectors are optional.
   * If you don't provide a normal vector, the engine will compute one for you in respect to the triangle you create.
   * 
   * @param x The x position of the vertex
   * @param y The y position of the vertex
   * @param z The z position of the vertex
   * @param u The u texture coordinate of the vertex
   * @param v The v texture coordinate of the vertex
   * @param nx The x component of the normal vector *(optional)*
   * @param ny The y component of the normal vector *(optional)*
   * @param nz The z component of the normal vector *(optional)*
   * 
   * @authors
   * - Roberto Selles/Henderythmix
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
   * @authors
   * - Roberto Selles/Henderythmix
   */
  class Mesh {
    private:
      std::vector<Vertex> m_vertices;
      std::vector<unsigned short> m_indices;

    protected:

      /**
       * @brief Adds a triangle to the mesh, and computes the normals for the vertices
       * 
       * Triangles must be added in counter-clockwise order. 
       * If not, the renderer will assume the plane is facing the wrong way.
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
       * @brief Returns the number of vertices in the vertex buffer
       * 
       * @return The number of vertices
       */
      unsigned long GetVertexCount();

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