#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

void Camera::computeProjectionMatrix(vec2 const &size) {
  m_projMatrix = mat4(1.0f);
  auto const aspect{size.x / size.y};
  m_projMatrix = perspective(radians(70.0f), aspect, 0.1f, 10.0f);
}

void Camera::computeViewMatrix() {
  m_viewMatrix = lookAt(m_eye, m_at, m_up);
}

void Camera::dolly(float speed) {
  // Compute forward vector (view direction)
  auto const forward{normalize(m_at - m_eye)};

  // Move eye and center forward (speed > 0) or backward (speed < 0)
  m_eye += forward * speed;
  m_at += forward * speed;

  computeViewMatrix();
}

void Camera::truck(float speed) {
  // Compute forward vector (view direction)
  auto const forward{normalize(m_at - m_eye)};
  // Compute vector to the left
  auto const left{cross(m_up, forward)};

  // Move eye and center to the left (speed < 0) or to the right (speed > 0)
  m_at -= left * speed;
  m_eye -= left * speed;

  computeViewMatrix();
}

void Camera::pan(float speed) {
  mat4 transform{1.0f};

  // Rotate camera around its local y axis
  transform = translate(transform, m_eye);
  transform = rotate(transform, -speed, m_up);
  transform = translate(transform, -m_eye);

  m_at = transform * vec4(m_at, 1.0f);

  computeViewMatrix();
}