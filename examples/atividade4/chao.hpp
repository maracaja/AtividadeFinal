#ifndef CHAO_HPP
#define CHAO_HPP

#include "abcgOpenGL.hpp"

using namespace std;

class Chao 
{
    public:
        void create(GLuint prog);
        void paint();
        void destroy();

    private:
        GLuint VAO{};
        GLuint VBO{};
        GLint model{};
        GLint cor{};
        GLuint textura{};

        void loadTexture(string_view path);
};

#endif
