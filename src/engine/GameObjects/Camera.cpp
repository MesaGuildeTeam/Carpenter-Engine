#include "Camera.hpp"

Engine::Camera::Camera(std::string name, float fov) : Engine::GameObject(name) {
    m_FOV = fov;
}

float Engine::Camera::getFOV() const {
    return m_FOV;
}
