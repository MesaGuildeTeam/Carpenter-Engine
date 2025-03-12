#ifndef ENGINE_MESH
#define ENGINE_MESH

#include "../Utils.hpp"
#include <vector>

namespace Engine::Graphics {
  
  /**
   * An abstract class that stores mesh data to the game engine
   * To create a mesh, you will need to derive from this class. There will potentially be a class in the future to generate new meshes
   * @caution All triangles must be loaded in counter-clockwise order due to OpenGL's winding order
   * @author Roberto Selles
   */
  class Mesh {
    private:
      std::vector<Vec3f> m_vertices;
      std::vector<Vec3f> m_normals;
      std::vector<Vec2f> m_texcoords;
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
       * @param t1 The first texture coordinate of the triangle
       * @param t2 The second texture coordinate of the triangle
       * @param t3 The third texture coordinate of the triangle
       * 
       */
      Success AddTriangle(Vec3f v1, Vec3f v2, Vec3f v3, Vec2f t1, Vec2f t2, Vec2f t3);

      /**
       * Adds a quad to the mesh, and computes the normals for the vertices
       * 
       * @param v1 The first vertex of the quad
       * @param v2 The second vertex of the quad
       * @param v3 The third vertex of the quad
       * @param v4 The fourth vertex of the quad
       * @param t1 The first texture coordinate of the quad
       * @param t2 The second texture coordinate of the quad
       * @param t3 The third texture coordinate of the quad
       * @param t4 The fourth texture coordinate of the quad
       */
      Success AddQuad(Vec3f v1, Vec3f v2, Vec3f v3, Vec3f v4, Vec2f t1, Vec2f t2, Vec2f t3, Vec2f t4);

    public:
      /**
       * Returns the vertex at the given index based on the index buffer
       * 
       * @param index The index of the index array
       * @deprecated
       */
      Vec3f GetVertex(int index);

      /**
       * Returns the 2D component of the vertex at the given index based on the index buffer
       */
      Vec2f GetVertex2D(int index);

      /**
       * Returns the texture coordinate at the given index based on the index buffer
       */
      Vec2f GetTextureCoord(int index);

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