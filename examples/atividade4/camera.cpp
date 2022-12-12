#include "camera.hpp"
#include <math.h>
#include <glm/gtc/matrix_transform.hpp>

void Camera::computeProjectionMatrix(vec2 const &size) 
{
    proj = mat4(1.0f);
    auto const aspect{size.x / size.y};
    proj = perspective(radians(70.0f), aspect, 0.1f, 28.3f);
}

void Camera::computeViewMatrix() 
{
    view = lookAt(eye, at, up);
}

void Camera::dolly(float speed) 
{
    auto const forward{normalize(at - eye)};
    auto futuro = eye + forward * speed;
    if (!extremo(futuro)) 
    {
        eye = futuro;
        at += forward * speed;
    }
    computeViewMatrix();
}

void Camera::truck(float speed) 
{
    auto const forward{normalize(at - eye)};
    auto const left{cross(up, forward)};
    auto futuro = eye - left * speed;
    if (!extremo(futuro)) 
    {
        eye = futuro;
        at -= left * speed;
    }
    computeViewMatrix();
}

void Camera::pan(float speed)
{
    mat4 transform{1.0f};
    transform = translate(transform, eye);
    transform = rotate(transform, -speed, up);
    transform = translate(transform, -eye);
    at = transform * vec4(at, 1.0f);
    computeViewMatrix();
}

// Verifica se a câmera alcançou os limites, visando impedir movimentações para muito longe
bool Camera::extremo(vec3 cam)
{
    return abs(cam.x) >= 10.0f || abs(cam.z) >= 10.0f || cam.y <= 0.0f || cam.y >= 10.0f;
}
