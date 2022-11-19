#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <random>
#include "abcgOpenGL.hpp"

#include "camera.hpp"
#include "ground.hpp"

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
  ivec2 m_viewportSize{};

  GLuint m_VAO{};
  GLuint m_VBO{};
  GLuint m_EBO{};
  GLuint m_program{};

  GLint m_viewMatrixLocation{};
  GLint m_projMatrixLocation{};
  GLint m_modelMatrixLocation{};
  GLint m_colorLocation{};

  Camera m_camera;
  float m_dollySpeed{};
  float m_truckSpeed{};
  float m_panSpeed{};

  Ground m_ground;

  vector<Vertex> m_vertices;
  vector<GLuint> m_indices;

  void loadModelFromFile(string_view path);

  default_random_engine r;
  vector<vec3> cores;
  vector<vec3> escalas;
  vector<vec3> centros;
};

#endif