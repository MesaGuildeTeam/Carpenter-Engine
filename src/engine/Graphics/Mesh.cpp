#include "Mesh.hpp"

Engine::Success Engine::Graphics::Mesh::AddTriangle(Vec3f v1, Vec3f v2, Vec3f v3, Vec2f t1, Vec2f t2, Vec2f t3) {
  // TODO: Make this more efficient with the following
  // - Check for duplicate vertices, texcoords and indices
  // - Implement normals calculation (Requires Vec3f's cross product to be implemented)
  
  m_vertices.push_back(v1);
  m_vertices.push_back(v2);
  m_vertices.push_back(v3);
  m_texcoords.push_back(t1);
  m_texcoords.push_back(t2);
  m_texcoords.push_back(t3);
  m_indices.push_back(m_vertices.size() - 3);
  m_indices.push_back(m_vertices.size() - 2);
  m_indices.push_back(m_vertices.size() - 1);
  
  return Engine::SUCCESS;
}

Engine::Success Engine::Graphics::Mesh::AddQuad(Vec3f v1, Vec3f v2, Vec3f v3, Vec3f v4, Vec2f t1, Vec2f t2, Vec2f t3, Vec2f t4) {
  m_vertices.push_back(v1);
  m_vertices.push_back(v2);
  m_vertices.push_back(v3);
  m_vertices.push_back(v4);
  m_texcoords.push_back(t1);
  m_texcoords.push_back(t2);
  m_texcoords.push_back(t3);
  m_texcoords.push_back(t4);
  m_indices.push_back(m_vertices.size() - 4);
  m_indices.push_back(m_vertices.size() - 3);
  m_indices.push_back(m_vertices.size() - 2);
  m_indices.push_back(m_vertices.size() - 1);
  
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