#include "Mesh.hpp"
#include <iostream>

void Engine::Graphics::Vertex::CalculateNormals(Vertex& v2, Vertex& v3) {
  // 
  // |  i   j   k  |
  // | u_x u_y u_z |
  // | v_x v_y v_z |
  //
  nx = (v2.y - y) * (v3.z - z) - (v2.z - z) * (v3.y - y);
  ny = (v2.z - z) * (v3.x - x) - (v2.x - x) * (v3.z - z);
  nz = (v2.x - x) * (v3.y - y) - (v2.y - y) * (v3.x - x);
  float length = sqrtf(nx * nx + ny * ny + nz * nz);

  nx /= length;
  ny /= length;
  nz /= length;
  
  v2 = {v2.x, v2.y, v2.z, v2.u, v2.v, nx, ny, nz};
  v3 = {v3.x, v3.y, v3.z, v3.u, v3.v, nx, ny, nz};
}

bool Engine::Graphics::Vertex::operator==(const Vertex& rhs) {
  if (x != rhs.x) return false;
  if (y != rhs.y) return false;
  if (z != rhs.z) return false;
  if (u != rhs.u) return false;
  if (v != rhs.v) return false;
  if (nx != rhs.nx) return false;
  if (ny != rhs.ny) return false;
  if (nz != rhs.nz) return false;
  return true;
  
  // bool output = x == rhs.x && y == rhs.y && z == rhs.z && u == rhs.u && v == rhs.v && nx == rhs.nx && ny == rhs.ny && nz == rhs.nz;
  // return output;
};

Engine::Success Engine::Graphics::Mesh::AddTriangle(Vertex v1, Vertex v2, Vertex v3) {
  // TODO: Make this more efficient with the following
  // - Implement normals calculation (Requires Vec3f's cross product to be implemented)
  
  // Compute New Normals of vertices
  Vertex n1 = v1, n2 = v2, n3 = v3;
  n1.CalculateNormals(n2, n3);
  
  auto hasV1 = std::find(m_vertices.begin(), m_vertices.end(), n1);
  auto hasV2 = std::find(m_vertices.begin(), m_vertices.end(), n2);
  auto hasV3 = std::find(m_vertices.begin(), m_vertices.end(), n3);

  bool isEmpty = m_vertices.size() == 0;

  // Each unique vertex should only be added once, but we add indices to the mesh regardless
  // The index refers to the position of the vertex in the vertices array as opengl usually does
  if (hasV1 < m_vertices.end() && isEmpty) {
    m_indices.push_back(hasV1 - m_vertices.begin());
  } else {
    m_vertices.push_back(n1);
    m_indices.push_back(m_vertices.size() - 1);
  }

  isEmpty = m_vertices.size() == 0;

  if (hasV2 < m_vertices.end() && isEmpty) {
    m_indices.push_back(hasV2 - m_vertices.begin());
  } else {
    m_vertices.push_back(n2);
    m_indices.push_back(m_vertices.size() - 1);
  }

  if (hasV3 < m_vertices.end() && isEmpty) {
    m_indices.push_back(hasV3 - m_vertices.begin());
  } else {
    m_vertices.push_back(n3);
    m_indices.push_back(m_vertices.size() - 1);
  }
  
  return Engine::SUCCESS;
}

Engine::Success Engine::Graphics::Mesh::AddQuad(Vertex v1, Vertex v2, Vertex v3, Vertex v4) {
  AddTriangle(v1, v2, v3);
  AddTriangle(v1, v3, v4);
  
  return Engine::SUCCESS;
}

float* Engine::Graphics::Mesh::GetVertices() {
  return (float*)(m_vertices.data());
}

unsigned long Engine::Graphics::Mesh::GetVertexCount() {
  return m_vertices.size();
}

unsigned short* Engine::Graphics::Mesh::GetIndices() {
  return m_indices.data();
}

unsigned long Engine::Graphics::Mesh::GetIndexCount() { 
  return m_indices.size(); 
}