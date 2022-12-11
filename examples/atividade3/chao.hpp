#ifndef CHAO_HPP
#define CHAO_HPP

#include "abcgOpenGL.hpp"

struct Vertex {
  glm::vec3 position{};
  glm::vec3 normal{};

  friend bool operator==(Vertex const &, Vertex const &) = default;
};

class Chao {
public:
  void create(GLuint prog);
  void paint();
  void destroy();

  [[nodiscard]] glm::vec4 getKa() const { return m_Ka; }
  [[nodiscard]] glm::vec4 getKd() const { return m_Kd; }
  [[nodiscard]] glm::vec4 getKs() const { return m_Ks; }
  [[nodiscard]] float getShininess() const { return m_shininess; }

private:
  GLuint VAO{};
  GLuint VBO{};
  GLint model{};
  GLint cor{};

  glm::vec4 m_Ka{};
  glm::vec4 m_Kd{};
  glm::vec4 m_Ks{};
  float m_shininess{};
};

#endif
