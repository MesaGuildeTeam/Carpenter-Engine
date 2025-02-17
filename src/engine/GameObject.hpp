#ifndef ENGINE_GAMEOBJECT
#define ENGINE_GAMEOBJECT

#include "Node.hpp"

namespace Engine {
    class GameObject : public Node {
        private:
        vec3 position;
    };
}

#endif