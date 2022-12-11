#include "window.hpp"

#include <unordered_map>

template <> struct std::hash<Vertex> {
  size_t operator()(Vertex const &vertex) const noexcept {
    auto const h1{hash<vec3>()(vertex.position)};
    return h1;
  }
};

void Window::onCreate() {
  auto const &assetsPath{abcg::Application::getAssetsPath()};

  r.seed(chrono::steady_clock::now()
             .time_since_epoch()
             .count()); // Gerador de números pseudo-aleatórios
  uniform_real_distribution distSup(
      0.25f, 0.75f); // Valores de largura e comprimento dos prédios
  uniform_real_distribution distAlt(0.5f,
                                    2.5f); // Valores de altura dos prédios
  uniform_real_distribution distPos(
      -4.0f, 4.0f); // Valores de posicionamento dos prédios
  uniform_real_distribution distCor(
      0.7f, 1.0f); // Valores dos canais RGB das cores dos prédios

  // Criação dos dados dos prédios
  for ([[maybe_unused]] auto _ : iter::range(0, N_PREDIOS)) {
    //cores.emplace_back(vec3(distCor(r), distCor(r), distCor(r)));
    escalas.emplace_back(vec3(distSup(r), distAlt(r), distSup(r)));
    centros.emplace_back(vec3(distPos(r), 0.0f, distPos(r)));
  }

  abcg::glClearColor(0.2f, 0.2f, 0.2f,
                     1.0f); // Cor padrão do fundo (cinza escuro)
  abcg::glEnable(GL_DEPTH_TEST);

  prog = abcg::createOpenGLProgram({{.source = assetsPath + "lookat.vert",
                                     .stage = abcg::ShaderStage::Vertex},
                                    {.source = assetsPath + "lookat.frag",
                                     .stage = abcg::ShaderStage::Fragment}});

  // Localização das variáveis uniformes
  viewLoc = abcg::glGetUniformLocation(prog, "view");
  projLoc = abcg::glGetUniformLocation(prog, "proj");
  modelLoc = abcg::glGetUniformLocation(prog, "model");
  //colorLoc = abcg::glGetUniformLocation(prog, "cor");

  chao.create(prog);                         // Cria o chão do cenário
  loadModelFromFile(assetsPath + "box.obj"); // Carrega modelo box.obj

  // Criação do VBO
  abcg::glGenBuffers(1, &VBO);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, VBO);
  abcg::glBufferData(GL_ARRAY_BUFFER, sizeof(vertices.at(0)) * vertices.size(),
                     vertices.data(), GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Criação do EBO
  abcg::glGenBuffers(1, &EBO);
  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  abcg::glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     sizeof(indices.at(0)) * indices.size(), indices.data(),
                     GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // Criação do VAO
  abcg::glGenVertexArrays(1, &VAO);
  abcg::glBindVertexArray(VAO);

  abcg::glBindBuffer(GL_ARRAY_BUFFER, VBO);
  auto const posicao{abcg::glGetAttribLocation(prog, "posicao")};
  abcg::glEnableVertexAttribArray(posicao);
  abcg::glVertexAttribPointer(posicao, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              nullptr);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);
  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

  abcg::glBindVertexArray(0);
}

void Window::onPaint() {
  abcg::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  abcg::glViewport(0, 0, tamanhoTela.x, tamanhoTela.y);
  abcg::glUseProgram(prog);

  auto const normalMatrixLoc{abcg::glGetUniformLocation(prog, "normal")};
  auto const lightDirLoc{
      abcg::glGetUniformLocation(prog, "lightDirWorldSpace")};
  auto const shininessLoc{abcg::glGetUniformLocation(prog, "shininess")};
  auto const IaLoc{abcg::glGetUniformLocation(prog, "Ia")};
  auto const IdLoc{abcg::glGetUniformLocation(prog, "Id")};
  auto const IsLoc{abcg::glGetUniformLocation(prog, "Is")};
  auto const KaLoc{abcg::glGetUniformLocation(prog, "Ka")};
  auto const KdLoc{abcg::glGetUniformLocation(prog, "Kd")};
  auto const KsLoc{abcg::glGetUniformLocation(prog, "Ks")};

  abcg::glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &camera.getViewMatrix()[0][0]);
  abcg::glUniformMatrix4fv(projLoc, 1, GL_FALSE, &camera.getProjMatrix()[0][0]);
  abcg::glBindVertexArray(VAO);

  auto const lightDirRotated{camera.getProjMatrix() * m_lightDir};

  // Desenha os prédios
  mat4 model;
  for (auto i : iter::range(0, N_PREDIOS)) {
    model = mat4(1.0f);
    model = translate(model, centros.at(i));
    model = scale(model, escalas.at(i));

    abcg::glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
    // abcg::glUniform4f(colorLoc, cores.at(i).x, cores.at(i).y, cores.at(i).z,
    //                   1.0f);
    abcg::glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT,
                         nullptr);
    abcg::glDrawArrays(GL_TRIANGLE_STRIP, 0, indices.size());

  }

  abcg::glUniform4fv(lightDirLoc, 1, &lightDirRotated.x);
  abcg::glUniform4fv(IaLoc, 1, &m_Ia.x);
  abcg::glUniform4fv(IdLoc, 1, &m_Id.x);
  abcg::glUniform4fv(IsLoc, 1, &m_Is.x);

  // Set uniform variables for the current model
  abcg::glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
  abcg::glUniform4fv(KaLoc, 1, &m_Ka.x);
  abcg::glUniform4fv(KdLoc, 1, &m_Kd.x);
  abcg::glUniform4fv(KsLoc, 1, &m_Ks.x);
  abcg::glUniform1f(shininessLoc, m_shininess);

  auto const modelViewMatrix{glm::mat3(viewLoc * modelLoc)};
  auto const normalMatrix{glm::inverseTranspose(modelViewMatrix)};
  abcg::glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, &normalMatrix[0][0]);

  abcg::glBindVertexArray(0);
  chao.paint(); // Desenha o chão
  abcg::glUseProgram(0);
}

void Window::onPaintUI() {
  abcg::OpenGLWindow::onPaintUI();

  auto const widgetSize{ImVec2(222, 244)};
  ImGui::SetNextWindowPos(ImVec2(tamanhoTela.x - widgetSize.x - 5,
                                 tamanhoTela.y - widgetSize.y - 5));
  ImGui::SetNextWindowSize(widgetSize);
  ImGui::Begin(" ", nullptr, ImGuiWindowFlags_NoDecoration);

  ImGui::Text("Light properties");

  // Slider to control light properties
  ImGui::PushItemWidth(widgetSize.x - 36);
  ImGui::ColorEdit3("Ia", &m_Ia.x, ImGuiColorEditFlags_Float);
  ImGui::ColorEdit3("Id", &m_Id.x, ImGuiColorEditFlags_Float);
  ImGui::ColorEdit3("Is", &m_Is.x, ImGuiColorEditFlags_Float);
  ImGui::PopItemWidth();

  ImGui::Spacing();

  ImGui::Text("Material properties");

  // Slider to control material properties
  ImGui::PushItemWidth(widgetSize.x - 36);
  ImGui::ColorEdit3("Ka", &m_Ka.x, ImGuiColorEditFlags_Float);
  ImGui::ColorEdit3("Kd", &m_Kd.x, ImGuiColorEditFlags_Float);
  ImGui::ColorEdit3("Ks", &m_Ks.x, ImGuiColorEditFlags_Float);
  ImGui::PopItemWidth();

  // Slider to control ligth
  ImGui::PushItemWidth(widgetSize.x - 36);
  ImGui::ColorEdit3("x", &m_lightDir.x, ImGuiColorEditFlags_Float);
  ImGui::ColorEdit3("y", &m_lightDir.y, ImGuiColorEditFlags_Float);
  ImGui::ColorEdit3("z", &m_lightDir.z, ImGuiColorEditFlags_Float);
  ImGui::PopItemWidth();

  // Slider to control the specular shininess
  ImGui::PushItemWidth(widgetSize.x - 16);
  ImGui::SliderFloat(" ", &m_shininess, 0.0f, 500.0f, "shininess: %.1f");
  ImGui::PopItemWidth();

  ImGui::End();
}

void Window::onResize(ivec2 const &size) {
  tamanhoTela = size;
  camera.computeProjectionMatrix(size);
}

void Window::onUpdate() {
  auto const deltaTime{gsl::narrow_cast<float>(getDeltaTime())};
  camera.dolly(dollySpeed * deltaTime);
  camera.truck(truckSpeed * deltaTime);
  camera.pan(panSpeed * deltaTime);
}

void Window::onEvent(SDL_Event const &event) {
  if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_UP)
      dollySpeed = 1.0f;
    if (event.key.keysym.sym == SDLK_DOWN)
      dollySpeed = -1.0f;
    if (event.key.keysym.sym == SDLK_LEFT)
      panSpeed = -1.0f;
    if (event.key.keysym.sym == SDLK_RIGHT)
      panSpeed = 1.0f;
    if (event.key.keysym.sym == SDLK_a)
      truckSpeed = -1.0f;
    if (event.key.keysym.sym == SDLK_d)
      truckSpeed = 1.0f;
  }

  if (event.type == SDL_KEYUP) {
    if (event.key.keysym.sym == SDLK_UP && dollySpeed > 0)
      dollySpeed = 0.0f;
    if (event.key.keysym.sym == SDLK_DOWN && dollySpeed < 0)
      dollySpeed = 0.0f;
    if (event.key.keysym.sym == SDLK_LEFT && panSpeed < 0)
      panSpeed = 0.0f;
    if (event.key.keysym.sym == SDLK_RIGHT && panSpeed > 0)
      panSpeed = 0.0f;
    if (event.key.keysym.sym == SDLK_a && truckSpeed < 0)
      truckSpeed = 0.0f;
    if (event.key.keysym.sym == SDLK_d && truckSpeed > 0)
      truckSpeed = 0.0f;
  }
}

void Window::onDestroy() {
  chao.destroy();
  abcg::glDeleteProgram(prog);
  abcg::glDeleteBuffers(1, &EBO);
  abcg::glDeleteBuffers(1, &VBO);
  abcg::glDeleteVertexArrays(1, &VAO);
}

// Importado diretamente das aulas
void Window::loadModelFromFile(string_view path) {
  tinyobj::ObjReader reader;

  if (!reader.ParseFromFile(path.data()))
    throw abcg::RuntimeError(
        fmt::format("Falha ao carregar modelo {} {}\n", path,
                    reader.Error().empty() ? "" : "(" + reader.Error() + ")"));
  if (!reader.Warning().empty())
    fmt::print("Warning: {}\n", reader.Warning());

  auto const &attributes{reader.GetAttrib()};
  auto const &shapes{reader.GetShapes()};

  vertices.clear();
  indices.clear();

  unordered_map<Vertex, GLuint> hash{};

  for (auto const &shape : shapes) {
    for (auto const offset : iter::range(shape.mesh.indices.size())) {

      auto const index{shape.mesh.indices.at(offset)};
      auto const startIndex{3 * index.vertex_index};
      auto const vx{attributes.vertices.at(startIndex + 0)};
      auto const vy{attributes.vertices.at(startIndex + 1)};
      auto const vz{attributes.vertices.at(startIndex + 2)};
      Vertex const vertex{.position = {vx, vy, vz}};

      if (!hash.contains(vertex)) {
        hash[vertex] = vertices.size();
        vertices.push_back(vertex);
      }

      indices.push_back(hash[vertex]);
    }
  }
}
