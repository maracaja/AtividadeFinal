#include "window.hpp"

#include <unordered_map>

// Explicit specialization of std::hash for Vertex
template <> struct hash<Vertex> 
{
    size_t operator()(Vertex const &vertex) const noexcept 
    {
        auto const h1{hash<vec3>()(vertex.position)};
        return h1;
    }
};

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

void Window::onCreate() 
{
    auto const &assetsPath{abcg::Application::getAssetsPath()};

    r.seed(chrono::steady_clock::now().time_since_epoch().count()); // Gerador de números pseudo-aleatórios
    uniform_real_distribution distSup(0.25f, 0.75f); // Valores de largura e comprimento dos prédios
    uniform_real_distribution distAlt(0.5f, 2.5f); // Valores de altura dos prédios
    uniform_real_distribution distPos(-4.0f, 4.0f); // Valores de posicionamento dos prédios
    uniform_real_distribution distCor(0.7f, 1.0f); // Valores dos canais RGB das cores dos prédios

    for ([[maybe_unused]] auto _ : iter::range(0, N_PREDIOS))
    {
        cores.emplace_back(vec3(distCor(r), distCor(r), distCor(r)));
        escalas.emplace_back(vec3(distSup(r), distAlt(r), distSup(r)));
        centros.emplace_back(vec3(distPos(r), 0.0f, distPos(r)));    
    }

    abcg::glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // Cor padrão do fundo (cinza escuro)
    abcg::glEnable(GL_DEPTH_TEST);

    prog = abcg::createOpenGLProgram
    ({
        {.source = assetsPath + "lookat.vert", .stage = abcg::ShaderStage::Vertex},
        {.source = assetsPath + "lookat.frag", .stage = abcg::ShaderStage::Fragment}
    });
  
    // Localização das variáveis uniformes
    viewLoc = abcg::glGetUniformLocation(m_program, "view");
    projLoc = abcg::glGetUniformLocation(m_program, "proj");
    modelLoc = abcg::glGetUniformLocation(m_program, "model");
    colorLoc = abcg::glGetUniformLocation(m_program, "cor");

    chao.create(prog); // Cria o chão do cenário
    loadModelFromFile(assetsPath + "box.obj"); // Carrega modelo box.obj

    // Criação do VBO
    abcg::glGenBuffers(1, &VBO);
    abcg::glBindBuffer(GL_ARRAY_BUFFER, VBO);
    abcg::glBufferData(GL_ARRAY_BUFFER, sizeof(vertices.at(0)) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Criação do EBO
    abcg::glGenBuffers(1, &EBO);
    abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    abcg::glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices.at(0)) * indices.size(), indices.data(), GL_STATIC_DRAW);
    abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Criação do VAO
    abcg::glGenVertexArrays(1, &VAO);
    abcg::glBindVertexArray(VAO);

    abcg::glBindBuffer(GL_ARRAY_BUFFER, VBO);
    auto const posicao{abcg::glGetAttribLocation(m_program, "posicao")};
    abcg::glEnableVertexAttribArray(posicao);
    abcg::glVertexAttribPointer(posicao, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);
    abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    abcg::glBindVertexArray(0);
}

void Window::loadModelFromFile(std::string_view path) {
  tinyobj::ObjReader reader;

  if (!reader.ParseFromFile(path.data())) {
    if (!reader.Error().empty()) {
      throw abcg::RuntimeError(
          fmt::format("Failed to load model {} ({})", path, reader.Error()));
    }
    throw abcg::RuntimeError(fmt::format("Failed to load model {}", path));
  }

  if (!reader.Warning().empty()) {
    fmt::print("Warning: {}\n", reader.Warning());
  }

  auto const &attributes{reader.GetAttrib()};
  auto const &shapes{reader.GetShapes()};

  m_vertices.clear();
  m_indices.clear();

  // A key:value map with key=Vertex and value=index
  std::unordered_map<Vertex, GLuint> hash{};

  // Loop over shapes
  for (auto const &shape : shapes) {
    // Loop over indices
    for (auto const offset : iter::range(shape.mesh.indices.size())) {
      // Access to vertex
      auto const index{shape.mesh.indices.at(offset)};

      // Vertex position
      auto const startIndex{3 * index.vertex_index};
      auto const vx{attributes.vertices.at(startIndex + 0)};
      auto const vy{attributes.vertices.at(startIndex + 1)};
      auto const vz{attributes.vertices.at(startIndex + 2)};

      Vertex const vertex{.position = {vx, vy, vz}};

      // If map doesn't contain this vertex
      if (!hash.contains(vertex)) {
        // Add this index (size of m_vertices)
        hash[vertex] = m_vertices.size();
        // Add this vertex
        m_vertices.push_back(vertex);
      }

      m_indices.push_back(hash[vertex]);
    }
  }
}

void Window::onPaint() {


  // Clear color buffer and depth buffer
  abcg::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  abcg::glViewport(0, 0, m_viewportSize.x, m_viewportSize.y);

  abcg::glUseProgram(m_program);

  // Set uniform variables for viewMatrix and projMatrix
  // These matrices are used for every scene object
  abcg::glUniformMatrix4fv(m_viewMatrixLocation, 1, GL_FALSE, &m_camera.getViewMatrix()[0][0]);
  abcg::glUniformMatrix4fv(m_projMatrixLocation, 1, GL_FALSE, &m_camera.getProjMatrix()[0][0]);

  abcg::glBindVertexArray(m_VAO);


  mat4 model;
  for (auto i : iter::range(0, N_PREDIOS))
  {
      model = mat4(1.0f);
      model = translate(model, centros.at(i));
      // não tem rotate
      model = scale(model, escalas.at(i));

      abcg::glUniformMatrix4fv(m_modelMatrixLocation, 1, GL_FALSE, &model[0][0]);
      abcg::glUniform4f(m_colorLocation, cores.at(i).x, cores.at(i).y, cores.at(i).z, 1.0f);
      abcg::glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
  }
  abcg::glBindVertexArray(0);

  // Draw ground
  m_ground.paint();


  abcg::glUseProgram(0);
}

void Window::onPaintUI() { abcg::OpenGLWindow::onPaintUI(); }

void Window::onResize(glm::ivec2 const &size) 
{
    tamanhoTela = size;
    m_camera.computeProjectionMatrix(size);
}

void Window::onUpdate() {
  auto const deltaTime{gsl::narrow_cast<float>(getDeltaTime())};

  // Update LookAt camera
  m_camera.dolly(m_dollySpeed * deltaTime);
  m_camera.truck(m_truckSpeed * deltaTime);
  m_camera.pan(m_panSpeed * deltaTime);
}

void Window::onDestroy() 
{
    chao.destroy();
    abcg::glDeleteProgram(prog);
    abcg::glDeleteBuffers(1, &EBO);
    abcg::glDeleteBuffers(1, &VBO);
    abcg::glDeleteVertexArrays(1, &VAO);
}
