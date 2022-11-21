#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

using namespace glm;

class Camera 
{
    public:
        void computeViewMatrix();
        void computeProjectionMatrix(vec2 const &size);
        void dolly(float speed);
        void truck(float speed);
        void pan(float speed);

        mat4 const &getViewMatrix() const { return view; }
        mat4 const &getProjMatrix() const { return proj; }

    private:
        vec3 eye{0.0f, 2.5f, 2.5f}; // Posição de partida da câmera
        vec3 at{0.0f, 1.25f, 0.0f}; // Ponto de partida na metade da altura máxima
        vec3 up{0.0f, 1.0f, 0.0f};

        mat4 view;
        mat4 proj;

        void travaCamera();
        bool extremo();
};

#endif
