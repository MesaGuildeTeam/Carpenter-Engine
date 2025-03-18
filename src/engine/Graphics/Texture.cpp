#include "Texture.hpp"
#include <GLES3/gl3.h>
#include <emscripten.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Engine::Graphics::Texture::Texture(const char* path) {
  m_filename = path;
}

void Engine::Graphics::Texture::LoadTexture() {
  glGenTextures(1, &m_texture);
  glBindTexture(GL_TEXTURE_2D, m_texture);

  unsigned char* data;
  int size;

  emscripten_wget_data(m_filename, (void**)&data, &size, nullptr);

  // Load Image
  //unsigned char* textureData = stbi_load(m_filename, &m_dimensions[0], &m_dimensions[1], nullptr, 4);
  unsigned char* textureData = stbi_load_from_memory(data, size, &m_dimensions[0], &m_dimensions[1], nullptr, 4);

  free(data);

  if (textureData == nullptr) {
    std::cerr << "ERROR: Failed to load image name: " << m_filename << std::endl;
    return;
  }

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_dimensions[0], m_dimensions[1], 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
  glGenerateMipmap(GL_TEXTURE_2D);

  STBI_FREE(textureData);
}

unsigned Engine::Graphics::Texture::GetTexture() {
  if (m_texture == -1)
    LoadTexture();

  return m_texture;
}