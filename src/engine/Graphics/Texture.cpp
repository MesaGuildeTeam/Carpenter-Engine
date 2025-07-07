/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "Texture.hpp"
#include <GLES3/gl3.h>
#include <emscripten.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Engine::Graphics::Texture::Texture(const char* path) {
  m_filename = path;
}

unsigned Engine::Graphics::Texture::LoadTexture() {

  if (m_request.req_state == 0) {
    m_request.req_state = 1;
    emscripten_async_wget_data(m_filename, (void*)&m_request,
      [](void* arg, void* d, int s) {
        AssetRequest* req = (AssetRequest*)arg;
        req->data = new unsigned char[s];
        memcpy((void*)req->data, d, s);
        req->size = s;
        req->req_state = 2;
      }, nullptr);
  }
  //emscripten_wget_data(m_filename, (void**)&data, &size, nullptr);

  while (m_request.req_state == 1) return 0;

  // Load Image
  unsigned char* textureData = stbi_load_from_memory(m_request.data, m_request.size, &m_dimensions[0],
    &m_dimensions[1], nullptr, 4);

  delete[] m_request.data;

  if (textureData == nullptr) {
    std::cerr << "ERROR: Failed to load image name: " << m_filename << std::endl;
    m_texture = 0;
    return 0;
  }

  glGenTextures(1, &m_texture);
  glBindTexture(GL_TEXTURE_2D, m_texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_dimensions[0], m_dimensions[1], 0,
    GL_RGBA, GL_UNSIGNED_BYTE, textureData);
  glGenerateMipmap(GL_TEXTURE_2D);

  STBI_FREE(textureData);
  return m_texture;
}

unsigned Engine::Graphics::Texture::GetTexture() {
  if (m_texture == -1)
    return LoadTexture();

  return m_texture;
}
