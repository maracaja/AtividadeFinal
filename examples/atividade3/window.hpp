#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <random>
#include "abcgOpenGL.hpp"
#include "camera.hpp"
#include "chao.hpp"

#define N_PREDIOS 100

using namespace std;
using namespace glm;

struct Vertex 
{
    vec3 position;
    friend bool operator==(Vertex const &, Vertex const &) = default;
};

class Window : public abcg::OpenGLWindow 
{
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
        float m_dollySpeed{};
        float m_truckSpeed{};
        float m_panSpeed{};

        Chao chao;
        vector<Vertex> vertices;
        vector<GLuint> indices;

        default_random_engine r;
        vector<vec3> cores;
        vector<vec3> escalas;
        vector<vec3> centros;

        void loadModelFromFile(string_view path);
};

#endif
