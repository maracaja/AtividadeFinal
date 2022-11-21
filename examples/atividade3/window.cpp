#include "window.hpp"

#include <unordered_map>

template <> struct std::hash<Vertex> 
{
    size_t operator()(Vertex const &vertex) const noexcept 
    {
        auto const h1{hash<vec3>()(vertex.position)};
        return h1;
    }
};

void Window::onCreate() 
{
    auto const &assetsPath{abcg::Application::getAssetsPath()};

    r.seed(chrono::steady_clock::now().time_since_epoch().count()); // Gerador de números pseudo-aleatórios
    uniform_real_distribution distSup(0.25f, 0.75f); // Valores de largura e comprimento dos prédios
    uniform_real_distribution distAlt(0.5f, 2.5f); // Valores de altura dos prédios
    uniform_real_distribution distPos(-4.0f, 4.0f); // Valores de posicionamento dos prédios
    uniform_real_distribution distCor(0.7f, 1.0f); // Valores dos canais RGB das cores dos prédios
=======
// Explicit specialization of std::hash for Vertex
template <> struct std::hash<Vertex> {
  size_t operator()(Vertex const &vertex) const noexcept {
    auto const h1{hash<vec3>()(vertex.position)};
    return h1;
  }
};

void Window::onEvent(SDL_Event const &event) {
  glm::ivec2 mousePosition;
  SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

  if (event.type == SDL_MOUSEMOTION) {
    camera.mouseMove(mousePosition);
  }
  if (event.type == SDL_MOUSEBUTTONDOWN &&
      event.button.button == SDL_BUTTON_LEFT) {
    camera.mousePress(mousePosition);
  }
  if (event.type == SDL_MOUSEBUTTONUP &&
      event.button.button == SDL_BUTTON_LEFT) {
    camera.mouseRelease(mousePosition);
  }
  if (event.type == SDL_MOUSEWHEEL) {
    m_zoom += (event.wheel.y > 0 ? -1.0f : 1.0f) / 5.0f;
    m_zoom = glm::clamp(m_zoom, -1.5f, 1.0f);
  }
}

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
    cores.emplace_back(vec3(distCor(r), distCor(r), distCor(r)));
    escalas.emplace_back(vec3(distSup(r), distAlt(r), distSup(r)));
    centros.emplace_back(vec3(distPos(r), 0.0f, distPos(r)));
  }
>>>>>>> Stashed changes

  abcg::glClearColor(0.2f, 0.2f, 0.2f,
                     1.0f); // Cor padrão do fundo (cinza escuro)
  abcg::glEnable(GL_DEPTH_TEST);

  prog = abcg::createOpenGLProgram({{.source = assetsPath + "lookat.vert",
                                     .stage = abcg::ShaderStage::Vertex},
                                    {.source = assetsPath + "lookat.frag",
                                     .stage = abcg::ShaderStage::Fragment}});

  chao.create(prog);                         // Cria o chão do cenário
  loadModelFromFile(assetsPath + "box.obj"); // Carrega modelo box.obj

  // Camera at (0,0,0) and looking towards the negative z
  glm::vec3 const eye{0.0f, 0.0f, 0.0f};
  glm::vec3 const at{0.0f, 0.0f, -1.0f};
  glm::vec3 const up{0.0f, 1.0f, 0.0f};
  m_viewMatrix = glm::lookAt(eye, at, up);

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

  auto const viewLoc {abcg::glGetUniformLocation(prog, "view")};
  auto const projLoc {abcg::glGetUniformLocation(prog, "proj")};
  auto const modelLoc {abcg::glGetUniformLocation(prog, "model")};
  auto const colorLoc{abcg::glGetUniformLocation(prog, "cor")};

  abcg::glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &m_viewMatrix[0][0]);
  abcg::glUniformMatrix4fv(projLoc, 1, GL_FALSE, &m_projMatrix[0][0]);
  abcg::glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &m_modelMatrix[0][0]);
  abcg::glBindVertexArray(VAO);

  // Desenha os prédios
  mat4 model;
  for (auto i : iter::range(0, N_PREDIOS)) {
    model = mat4(1.0f);
    model = translate(model, centros.at(i));
    model = scale(model, escalas.at(i));

    abcg::glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
    abcg::glUniform4f(colorLoc, cores.at(i).x, cores.at(i).y, cores.at(i).z,
                      1.0f);
    abcg::glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT,
                         nullptr);
  }

  abcg::glBindVertexArray(0);
  chao.paint(); // Desenha o chão
  abcg::glUseProgram(0);
}

void Window::onPaintUI() {
  abcg::OpenGLWindow::onPaintUI();

  {
    auto const widgetSize{ImVec2(218, 62)};
    ImGui::SetNextWindowPos(ImVec2(tamanhoTela.x - widgetSize.x - 5, 5));
    ImGui::SetNextWindowSize(widgetSize);
    ImGui::Begin("Widget window", nullptr, ImGuiWindowFlags_NoDecoration);

    {
      ImGui::PushItemWidth(120);
      static std::size_t currentIndex{};
      std::vector<std::string> const comboItems{"Perspective", "Orthographic"};

      if (ImGui::BeginCombo("Projection",
                            comboItems.at(currentIndex).c_str())) {
        for (auto const index : iter::range(comboItems.size())) {
          auto const isSelected{currentIndex == index};
          if (ImGui::Selectable(comboItems.at(index).c_str(), isSelected))
            currentIndex = index;
          if (isSelected)
            ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
      }
      ImGui::PopItemWidth();

      ImGui::PushItemWidth(170);
      auto const aspect{gsl::narrow<float>(tamanhoTela.x) /
                        gsl::narrow<float>(tamanhoTela.y)};
      if (currentIndex == 0) {
        m_projMatrix =
            glm::perspective(glm::radians(m_FOV), aspect, 0.01f, 100.0f);

        ImGui::SliderFloat("FOV", &m_FOV, 5.0f, 179.0f, "%.0f degrees");
      } else {
        m_projMatrix = glm::ortho(-20.0f * aspect, 20.0f * aspect, -20.0f,
                                  20.0f, 0.01f, 100.0f);
      }
      ImGui::PopItemWidth();
    }

<<<<<<< Updated upstream
void Window::onResize(ivec2 const &size) 
{
    tamanhoTela = size;
    camera.computeProjectionMatrix(size);
=======
    ImGui::End();
  }
>>>>>>> Stashed changes
}

void Window::onResize(glm::ivec2 const &size) {
  tamanhoTela = size;
  camera.resizeViewport(size);
}

void Window::onUpdate() {
  m_viewMatrix = camera.getRotation();
  
  m_viewMatrix = glm::mat4{ m_viewMatrix[0], m_viewMatrix[1] ,m_viewMatrix[2],m_viewMatrix[3]+ m_zoom};
  // m_viewMatrix =
  //     glm::lookAt(glm::vec3(0.0f, 0.0f, 2.0f + m_zoom),
  //                 glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

<<<<<<< Updated upstream
void Window::onEvent(SDL_Event const &event) {
  if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
      m_dollySpeed = 1.0f;
    if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
      m_dollySpeed = -1.0f;
    if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a)
      m_panSpeed = -1.0f;
    if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)
      m_panSpeed = 1.0f;
    if (event.key.keysym.sym == SDLK_q)
      m_truckSpeed = -1.0f;
    if (event.key.keysym.sym == SDLK_e)
      m_truckSpeed = 1.0f;
  }
  if (event.type == SDL_KEYUP) {
    if ((event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w) &&
        m_dollySpeed > 0)
      m_dollySpeed = 0.0f;
    if ((event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) &&
        m_dollySpeed < 0)
      m_dollySpeed = 0.0f;
    if ((event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a) &&
        m_panSpeed < 0)
      m_panSpeed = 0.0f;
    if ((event.key.keysym.sym == SDLK_RIGHT ||
         event.key.keysym.sym == SDLK_d) &&
        m_panSpeed > 0)
      m_panSpeed = 0.0f;
    if (event.key.keysym.sym == SDLK_q && m_truckSpeed < 0)
      m_truckSpeed = 0.0f;
    if (event.key.keysym.sym == SDLK_e && m_truckSpeed > 0)
      m_truckSpeed = 0.0f;
  }
}

void Window::onDestroy() 
{
    chao.destroy();
    abcg::glDeleteProgram(prog);
    abcg::glDeleteBuffers(1, &EBO);
    abcg::glDeleteBuffers(1, &VBO);
    abcg::glDeleteVertexArrays(1, &VAO);
=======
void Window::onDestroy() {
  chao.destroy();
  abcg::glDeleteProgram(prog);
  abcg::glDeleteBuffers(1, &EBO);
  abcg::glDeleteBuffers(1, &VBO);
  abcg::glDeleteVertexArrays(1, &VAO);
>>>>>>> Stashed changes
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
