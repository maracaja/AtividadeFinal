#include "asfalto.hpp"

using namespace glm;

void Asfalto::create(GLuint prog, int quant) 
{
    destroy();

    // Inicialização do gerador de números pseudoaleatórios e distribuições
    r.seed(chrono::steady_clock::now().time_since_epoch().count());
    uniform_real_distribution distPos(-1.0f, 1.0f);
    uniform_real_distribution distIntensity(0.0f, 0.1f);

    program = prog;

    // Localização das variáveis do programa
    tamLoc = abcg::glGetUniformLocation(program, "tamanho");
    auto const posicao{abcg::glGetAttribLocation(program, "posicao")};
    auto const cor{abcg::glGetAttribLocation(program, "cor")};

    for (auto &&[i, camada] : iter::enumerate(camadas)) 
    {
        camada.tamanho = 1.0f + i;
        camada.quantidade = quant / gsl::narrow<int>(i + 1);

        vector<vec3> data;
        for ([[maybe_unused]] auto _ : iter::range(0, camada.quantidade)) 
        {
            data.emplace_back(distPos(r), distPos(r), 0);
            data.push_back(vec3(distIntensity(r)));
        }

        // Criação do VBO
        abcg::glGenBuffers(1, &camada.VBO);
        abcg::glBindBuffer(GL_ARRAY_BUFFER, camada.VBO);
        abcg::glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(vec3), data.data(), GL_STATIC_DRAW);
        abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Criação do VAO
        abcg::glGenVertexArrays(1, &camada.VAO);
        abcg::glBindVertexArray(camada.VAO);

        abcg::glBindBuffer(GL_ARRAY_BUFFER, camada.VBO);
        abcg::glEnableVertexAttribArray(posicao);
        abcg::glVertexAttribPointer(posicao, 2, GL_FLOAT, GL_FALSE, sizeof(vec3) * 2, nullptr);
        abcg::glEnableVertexAttribArray(cor);
        abcg::glVertexAttribPointer(cor, 3, GL_FLOAT, GL_FALSE, sizeof(vec3) * 2, reinterpret_cast<void *>(sizeof(vec3)));

        abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);
        abcg::glBindVertexArray(0);
    }
}

void Asfalto::paint() 
{
    abcg::glUseProgram(program);
    abcg::glEnable(GL_BLEND);
    abcg::glBlendFunc(GL_ONE, GL_ONE);

    for (auto const &camada : camadas) 
    {
        abcg::glBindVertexArray(camada.VAO);
        abcg::glUniform1f(tamLoc, camada.tamanho);
        abcg::glDrawArrays(GL_POINTS, 0, camada.quantidade);
        abcg::glBindVertexArray(0);
    }

    abcg::glDisable(GL_BLEND);
    abcg::glUseProgram(0);
}

void Asfalto::destroy() 
{
    for (auto &camada : camadas) 
    {
        abcg::glDeleteBuffers(1, &camada.VBO);
        abcg::glDeleteVertexArrays(1, &camada.VAO);
    }
}