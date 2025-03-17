#ifndef ENGINE_TEXTURE
#define ENGINE_TEXTURE

#include "../Utils.hpp"

namespace Engine::Graphics {

  class Texture {
    private:
    unsigned int m_texture = -1;
    int m_dimensions[2];
    const char* m_filename;
    
    void LoadTexture();

    public:
    
    Texture(const char* path);

    unsigned GetTexture();


  };
};

#endif 