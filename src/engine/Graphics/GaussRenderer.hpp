#ifndef ENGINE_GAUSS_RENDERER
#define ENGINE_GAUSS_RENDERER

#include "Renderer.hpp"

namespace Engine::Graphics {
    class GaussRenderer: public Renderer {
        public:
        
        GaussRenderer(const char* id = "canvas");

        void DrawMesh(Mesh* mesh, Vec3f position = {0, 0, 0}, Vec3f scale = {1, 1, 1}, Vec3f rotation = {0, 0, 0}) override;
    };
};

#endif