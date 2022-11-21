#include "camera.hpp"
#include <math.h>
#include <glm/gtc/matrix_transform.hpp>

void Camera::computeProjectionMatrix(vec2 const &size) 
{
    proj = mat4(1.0f);
    auto const aspect{size.x / size.y};
    proj = perspective(radians(70.0f), aspect, 0.1f, 10.0f);
}

void Camera::computeViewMatrix() 
{
    view = lookAt(eye, at, up);
}

void Camera::dolly(float speed) 
{
    auto const forward{normalize(at - eye)};
    eye += forward * speed;
    if (!extremo()) at += forward * speed;
    travaCamera();
    computeViewMatrix();
}

void Camera::truck(float speed) 
{
    auto const forward{normalize(at - eye)};
    auto const left{cross(up, forward)};
    eye -= left * speed;
    if (!extremo()) at -= left * speed;
    travaCamera();
    computeViewMatrix();
}

void Camera::pan(float speed)
{
    mat4 transform{1.0f};
    transform = translate(transform, eye);
    transform = rotate(transform, -speed, up);
    transform = translate(transform, -eye);

    at = transform * vec4(at, 1.0f);
    travaCamera();
    computeViewMatrix();
}

// Impede que a câmera ultrapasse certos limites
void Camera::travaCamera()
{
    if (eye.x > 5.0f) eye.x = 5.0f;
    else if (eye.x < -5.0f) eye.x = -5.0f; 
    if (eye.y > 10.0f) eye.y = 10.0f;
    else if (eye.y < 0.0f) eye.y = 0.0f;
    if (eye.z > 5.0f) eye.z = 5.0f;
    else if (eye.z < -5.0f) eye.z = -5.0f;
}

// Verifica se a câmera alcançou os limites, visando impedir as outras movimentações
bool Camera::extremo()
{
    return abs(eye.x) >= 5.0f || abs(eye.z) >= 5.0f || eye.y <= 0.0f || eye.y >= 10.0f;
}