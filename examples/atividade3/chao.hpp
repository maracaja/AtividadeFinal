#ifndef CHAO_HPP
#define CHAO_HPP

#include "abcgOpenGL.hpp"

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
};

#endif
