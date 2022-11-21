#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "abcgOpenGL.hpp"
#include "camera.hpp"
#include "chao.hpp"
#include <random>

#define N_PREDIOS 100

using namespace std;
using namespace glm;

struct Vertex {
  vec3 position;
  friend bool operator==(Vertex const &, Vertex const &) = default;
};

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

//   GLint viewLoc{};
//   GLint projLoc{};
//   GLint modelLoc{};
//   GLint colorLoc{};

  Camera camera;
  float m_zoom{};

  Chao chao;
  vector<Vertex> vertices;
  vector<GLuint> indices;

  default_random_engine r;
  vector<vec3> cores;
  vector<vec3> escalas;
  vector<vec3> centros;
  float m_FOV{30.0f};
  void loadModelFromFile(string_view path);

  // Matrix to change from world space to camera space
  glm::mat4 m_viewMatrix{1.0f};

  // Matrix to change from camera space to clip space
  glm::mat4 m_projMatrix{1.0f};

  glm::mat4 m_modelMatrix{1.0f};
};

#endif
