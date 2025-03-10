#ifndef ENGINE_SHADER
#define ENGINE_SHADER

namespace Engine::Graphics {
  class Shader {
    private:

    unsigned int m_shaderProgram;

    public:

    Shader();

    Shader(const char* frag);

    Shader(const char* frag, const char* vert);

    void Use();
  };

  extern Shader DefaultShader;
}

#endif