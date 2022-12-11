#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "abcgOpenGL.hpp"
#include "camera.hpp"
#include "chao.hpp"
#include <random>

#define N_PREDIOS 100

using namespace std;
using namespace glm;

class Window : public abcg::OpenGLWindow {
protected:
  void onEvent(SDL_Event const &event) override;
  void onCreate() override;
  void onPaint() override;
  void onPaintUI() override;
  void onResize(ivec2 const &size) override;
  void onDestroy() override;
  void onUpdate() override;

private:
  ivec2 tamanhoTela{};

  GLuint VAO{};
  GLuint VBO{};
  GLuint EBO{};
  GLuint prog{};

  GLint viewLoc{};
  GLint projLoc{};
  GLint modelLoc{};
  GLint colorLoc{};

  Camera camera;
  float dollySpeed{};
  float truckSpeed{};
  float panSpeed{};

  Chao chao;
  vector<Vertex> vertices;
  vector<GLuint> indices;

  // Light and material properties
  glm::vec4 m_lightDir{1.0f, 1.0f, 1.0f, 0.0f};
  glm::vec4 m_Ia{1.0f};
  glm::vec4 m_Id{1.0f};
  glm::vec4 m_Is{1.0f};
  glm::vec4 m_Ka{0.1f, 0.1f, 0.1f, 1.0f};
  glm::vec4 m_Kd{0.7f, 0.7f, 0.7f, 1.0f};
  glm::vec4 m_Ks{1.0f};
  float m_shininess{25.0f};

  default_random_engine r;
  vector<vec3> cores;
  vector<vec3> escalas;
  vector<vec3> centros;

  void loadModelFromFile(string_view path);
};

#endif
