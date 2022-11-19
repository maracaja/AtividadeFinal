#ifndef ASFALTO_HPP
#define ASFALTO_HPP

#include <array>
#include <random>
#include "abcgOpenGL.hpp"

using namespace std;

class Asfalto 
{
    public:
        void create(GLuint prog, int quant);
        void paint();
        void destroy();

    private:
        GLuint program{};
        GLint tamLoc{};

        struct Camada 
        {
            GLuint VAO{};
            GLuint VBO{};
            float tamanho{};
            int quantidade{};
        };

        array<Camada, 2> camadas;
        default_random_engine r;
};

#endif