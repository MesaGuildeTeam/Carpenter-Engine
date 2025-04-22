#ifndef ENGINE_CAMERA
#define ENGINE_CAMERA

#include "../GameObject.hpp"

namespace Engine {
    /**
     * @brief Camera class for the game engine.
     *
     * This class represents a camera in the game engine. It inherits from the
     * GameObject class.
     */
    class Camera : public GameObject {
        private:
        float m_FOV;

        public:

        /**
         * @brief Default constructor for Camera.
         *
         * Initializes a camera with an FOV of 60 degrees. if orthographic,
         * that just means everything in the environment is scaled down by
         * a factor of the FOV.
         *
         * @param name The name of the camera gameobject.
         * @param fov The field of view of the camera in degrees.
         */
        Camera(std::string name, float fov = 60.0f);

        /**
         * @brief Getter for the field of view of the camera.
         *
         * @return The field of view of the camera in degrees.
         */
        float getFOV() const;
    };
}

#endif
