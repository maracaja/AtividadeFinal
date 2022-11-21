#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

using namespace glm;

class Camera {
public:
  void computeViewMatrix();
  void computeProjectionMatrix(vec2 const &size);

  void dolly(float speed);
  void truck(float speed);
  void pan(float speed);

  mat4 const &getViewMatrix() const { return m_viewMatrix; }
  mat4 const &getProjMatrix() const { return m_projMatrix; }

private:
  vec3 m_eye{0.0f, 2.5f, 2.5f}; // Camera position
  vec3 m_at{0.0f, 1.5f, 0.0f};  // Look-at point
  vec3 m_up{0.0f, 1.0f, 0.0f};  // "up" direction

  // Matrix to change from world space to camera space
  mat4 m_viewMatrix;

  // Matrix to change from camera space to clip space
  mat4 m_projMatrix;
};

#endif