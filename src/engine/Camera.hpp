#ifndef ENGINE_UIElement_hpp
#define ENGINE_UIElement_hpp

#include "../Node.hpp"
#include "../Utils.hpp"

class Camera : public Engine::Node {
    protected:

    mat3 m_projectionMatrix;
    vec3 m_position;
    vec3 m_direction;
    float m_fov;
    float rotation;

    public:

    Camera();

    vec3 getPosition();
    void setPosition(vec3 position);

    vec3 getDirection();
    void setDirection(vec3 direction);

    // horizontal fov in radians
    // < 0 : reverse perspective, = 0 : orthographic, > 0 : perspective
    // see https://www.desmos.com/calculator/zz2v1m0pxw
    // may have to provide for vertical fov too later on
    float getFov();
    void setFov(float fov);

    float getRotation();
    void setRotation(float angle);

    mat3 getProjectionMatrix();
    void setProjectionMatrix(mat3 projectionMatrix);
};

#endif