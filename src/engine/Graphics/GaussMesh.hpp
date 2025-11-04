#ifndef ENGINE_GAUSSMESH
#define ENGINE_GAUSSMESH

#include "Mesh.hpp"

namespace Engine::Graphics {
    class GaussMesh: public Mesh {
        Success AddTriangle(Vertex v1, Vertex v2, Vertex v3) override;

        float* GetVertices() override;
    };
};

#endif