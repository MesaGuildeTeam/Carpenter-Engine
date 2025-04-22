/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "Camera.hpp"

Engine::Camera::Camera(std::string name, float fov) : Engine::GameObject(name) {
    m_FOV = fov;
}

float Engine::Camera::getFOV() const {
    return m_FOV;
}
