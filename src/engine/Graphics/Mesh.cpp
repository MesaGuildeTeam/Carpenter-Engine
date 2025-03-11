#include "Mesh.hpp"
#include <iostream>

Engine::Success Engine::Graphics::Mesh::AddTriangle(Vec3f v1, Vec3f v2, Vec3f v3, Vec2f t1, Vec2f t2, Vec2f t3) {
  // TODO: Make this more efficient with the following
  // - Implement normals calculation (Requires Vec3f's cross product to be implemented)
  
  auto hasV1 = std::find(m_vertices.begin(), m_vertices.end(), v1);
  auto hasV2 = std::find(m_vertices.begin(), m_vertices.end(), v2);
  auto hasV3 = std::find(m_vertices.begin(), m_vertices.end(), v3);

  bool isEmpty = m_vertices.size() == 0;

  // Each unique vertex should only be added once, but we add indices to the mesh regardless
  // The index refers to the position of the vertex in the vertices array as opengl usually does
  if (hasV1 == m_vertices.end() && !isEmpty) {
    m_indices.push_back(hasV1 - m_vertices.begin());
  } else {
    m_vertices.push_back(v1);
    m_indices.push_back(m_vertices.size() - 1);
  }

  if (hasV2 == m_vertices.end() && !isEmpty) {
    m_indices.push_back(hasV2 - m_vertices.begin());
  } else {
    m_vertices.push_back(v2);
    m_indices.push_back(m_vertices.size() - 1);
  }

  if (hasV3 == m_vertices.end() && !isEmpty) {
    m_indices.push_back(hasV3 - m_vertices.begin());
  } else {
    m_vertices.push_back(v3);
    m_indices.push_back(m_vertices.size() - 1);
  }
  
  return Engine::SUCCESS;
}

Engine::Success Engine::Graphics::Mesh::AddQuad(Vec3f v1, Vec3f v2, Vec3f v3, Vec3f v4, Vec2f t1, Vec2f t2, Vec2f t3, Vec2f t4) {
  AddTriangle(v1, v2, v3, t1, t2, t3);
  AddTriangle(v1, v3, v4, t1, t3, t4);
  
  return Engine::SUCCESS;
}

Engine::Vec3f Engine::Graphics::Mesh::GetVertex(int index) { 
  return m_vertices[m_indices[index]]; 
}

Engine::Vec2f Engine::Graphics::Mesh::GetVertex2D(int index) {
  return {m_vertices[m_indices[index]].x, m_vertices[m_indices[index]].y};
}

Engine::Vec2f Engine::Graphics::Mesh::GetTextureCoord(int index) { 
  return m_texcoords[m_indices[index]]; 
}

float* Engine::Graphics::Mesh::GetVertices() {
  return (float*)(m_vertices.data());
}

unsigned short* Engine::Graphics::Mesh::GetIndices() {
  return m_indices.data();
}

unsigned long Engine::Graphics::Mesh::GetIndexCount() { 
  return m_indices.size(); 
}