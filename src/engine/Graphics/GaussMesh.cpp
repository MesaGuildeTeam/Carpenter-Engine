#include "GaussMesh.hpp"

#include <cstdlib>

#define GAUSSES_PER_AXIS 30

Engine::Success Engine::Graphics::GaussMesh::AddTriangle(Vertex v1, Vertex v2, Vertex v3) {
  // Compute New Normals of vertices
  Vertex n1 = v1, n2 = v2, n3 = v3;
  n1.CalculateNormals(n2, n3);

  for (int i = 0; i < GAUSSES_PER_AXIS; i++) {
    for (int j = 0; j < GAUSSES_PER_AXIS; j++) {
        float u = (i + (float)rand() / RAND_MAX) / GAUSSES_PER_AXIS;
        float v = (j + (float)rand() / RAND_MAX) / GAUSSES_PER_AXIS;

        if (u + v > 1.0) {
            u = 1.0 - u;
            v = 1.0 - v;
        }

        float imgu = n1.u + u*(n2.u - n1.u) + v*(n3.u - n1.u);
        float imgv = n1.v + u*(n2.v - n1.v) + v*(n3.v - n1.v);

        Engine::Vec3f p = Engine::Vec3f{v1.x, v1.y, v1.z} * (1.0f - u - v)
            + Engine::Vec3f{v2.x, v2.y, v2.z} * u + Engine::Vec3f{v3.x, v3.y, v3.z} * v;
        m_vertices.push_back(Vertex{p.x, p.y, p.z, imgu, imgv, n1.nx, n1.ny, n1.nz});
    } 
  }

  return Engine::SUCCESS;
}

float* Engine::Graphics::GaussMesh::GetVertices() {
  // Sort vertexBuffer

  return (float*)(m_vertices.data());
}