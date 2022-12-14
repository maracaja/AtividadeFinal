#include "chao.hpp"

using namespace std;
using namespace glm;

void Chao::create(GLuint prog)
{
    array<vec3, 4> vertices 
    {{  // Solo do cenário em um quadrado 20 x 20 com centro na origem
        {-10.0f, 0.0f, 10.0f},
        {-10.0f, 0.0f, -10.0f},
        {10.0f, 0.0f, 10.0f},
        {10.0f, 0.0f, -10.0f}
    }};

    // Criação do VBO
    abcg::glGenBuffers(1, &VBO);
    abcg::glBindBuffer(GL_ARRAY_BUFFER, VBO);
    abcg::glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
    abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Criação do VAO
    abcg::glGenVertexArrays(1, &VAO);
    abcg::glBindVertexArray(VAO);
    abcg::glBindBuffer(GL_ARRAY_BUFFER, VBO);

    auto const posicao{abcg::glGetAttribLocation(prog, "posicao")};
    abcg::glEnableVertexAttribArray(posicao);
    abcg::glVertexAttribPointer(posicao, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);
    abcg::glBindVertexArray(0);

    // Localização das variáveis Uniform do shader
    model = abcg::glGetUniformLocation(prog, "model");
    cor = abcg::glGetUniformLocation(prog, "cor");
}

void Chao::paint() 
{
    abcg::glBindVertexArray(VAO);
    mat4 matrizModel{1.0f};
    abcg::glUniformMatrix4fv(model, 1, GL_FALSE, &matrizModel[0][0]);
    abcg::glUniform4f(cor, 0.3f, 0.3f, 0.3f, 1.0f);
    abcg::glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    abcg::glBindVertexArray(0);
}

void Chao::destroy() 
{
    abcg::glDeleteBuffers(1, &VBO);
    abcg::glDeleteVertexArrays(1, &VAO);
}
