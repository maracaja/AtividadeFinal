# Atividade 3
#### Sérgio Maracajá Junior - RA 11000315
#### Vinícius Lacerda Gonsalez - RA 11126315

* * *

## Sobre a aplicação

A presente aplicação apresenta um modelo simplificado de uma vista aérea de uma cidade, usando transformações de câmera baseadas no *LookAt* para navegar na visualização e paralelepípedos de diferentes dimensões baseados em um mesmo modelo simulando prédios.
O terreno onde estes edifícios simulados estão situados tem uma dimensão de 10 x 10 com centro na origem do sistema de coordenadas. Caso a câmera alcance um limite consistente em um cubo de lado 10 partindo da referência do solo, a aplicação não responderá até que seja inserido um comando que devolva a câmera para uma posição válida. A intenção neste caso foi evitar deslocamentos a distâncias que tendam ao infinito.

Para a utilização da navegação, temos os seguintes comandos:
-   **Seta para cima:** aumenta o zoom;
-   **Seta para baixo:** afasta o zoom;
-   **Seta para direita:** rotaciona no sentido horário;
-   **Seta para esquerda:** rotaciona no sentido anti-horário;
-   **Tecla 'A':** desloca-se lateralmente para a esquerda;
-   **Tecla 'D':** desloca-se lateralmente para a direita.

* * *

## Shaders

### lookat.frag

Este shader realiza apenas uma operação importante: se a câmera em algum momento atravessar algumas estrutura, esta aparecerá mais escura, com metade da intensidade, permanecendo com a cor normal em qualquer outro caso (linhas 11 e 12).


### lookat.vert

Aqui, no `main` (linhas 12-18), a posição da câmera no cenário é refeita após a atualização dos valores de `model`, `view` e `posicao`, bem como esta posição calculada influencia na perda de intensidade (calculada se essa diferença vai até 10 unidades de distância), gerando um efeito de escurecimento gradual até uma perspectiva similar a uma sombra no horizonte, antes do desaparecimento.


* * *

## Implementação

Segue abaixo a descrição do código-fonte, contido na pasta do projeto como mais um exemplo na pasta `examples`, sob o título `atividade1`. Além dos arquivos C++ que serão descritos mais adiante, foram realizadas as seguintes adições ao projeto:

-   Em `examples/CMakeLists.txt`, há apenas a linha de código `add_subdirectory(atividade3)`;
-   Em `public`, além dos arquivos gerados pela compilação do WASM, a página `helloworld.html` foi modificada a linha 258 para que a página execute o arquivo `atividade3.js`;
-   A pasta `docs` foi criada com os arquivos compilados pelo `build-wasm` e o `helloworld.html`, visando a criação do site no GitHub Pages;
-   Na pasta `atividade3`:
    -   Em `CMakeLists.txt`, foi definido o nome do projeto na linha 1. Na linha seguinte estão listados os arquivos `.cpp` utilizados;
    -   Em `assets`, além dos shaders, é incluído o arquivo `box.obj` das notas de aula, modificado de forma a deixar suas coordenadas de origem sob sua face inferior.


### main.cpp

Este arquivo acabou por ser, na prática, uma repetição do código apresentado no LookAt, com o método `main` instanciando a aplicação (linha 7), gerando e configurando a janela onde a aplicação reside (linhas 8-16), e chamando seu método `run` (linha 17), tudo isso dentro de uma estrutura `try-catch`. O botão de tela cheia foi retirado (linha 14), para acessar diretamente os comandos do teclado.


### chao.hpp

Este arquivo de cabeçalho define a classe `Chao`, com seus métodos públicos `create`, `paint` e `destroy` (linhas 9 a 11), e as variáveis privadas que intermediam sua renderização (linhas 14-17).
O chão do cenário é cinza-escuro (aparentando mais um preto, visando lembrar asfalto) e contrasta um pouco com a cor de fundo da aplicação.


### chao.cpp

Neste arquivo-fonte, são implementados os métodos públicos declarados em `chao.hpp`, baseados em outros códigos vistos nas notas de aula.

#### create – linhas 6 a 36

Inicia-se o código com a declaração dos quatro vértices da superfície do cenário (linhas 8-14). Como se trata de uma única cor, não é necessária outra estrutura adicional.
Na sequência, as estruturas que geram o VBO e VAO são geradas e, em seguida, utilizadas. Por fim, as referências `model` e `cor`, que endereçam variáveis do shader.

#### paint – linhas 38 a 46

Com uma cor de fundo em cinza 30%, os triângulos que formam o quadrado são desenhados.

#### destroy – linhas 48 a 52

Neste método, são eliminadas as estruturas VAO e VBO, com uso dos métodos dedicados da biblioteca `abcg`.


### camera.hpp

A aplicação da câmera acabou por ser uma adaptação do LookAt, uma vez que algumas tentativas de implementar o *trackball* ou deixar as movimentações automáticas tiveram resultados insatisfatórios. Assim, uma adaptação ao código original do lookAt é apresentada, com complementos que impedem que a câmera exceda limites de distância, sempre estando sobre o terreno delimitado pela classe `Chao`.
-   Assim como no original, são declarados nas linhas 12 a 16 os métodos públicos que comandam a movimentação e os cálculos de matrizes de transformações. Os retornos dessas matrizes (declaradas de forma privada nas linhas 26 e 27) são apresentados pelos métodos presentes nas linhas 18 e 19;
-   A câmera, localizada pela variável `eye` (linha 22), inicia com altura 2.5, valor compatível com a altura máxima configurada para um edifício. Também a posição apresenta-se deslocada à metade da distância máxima em relação à origem, também em 2.5, mas no eixo z;
-   O ponto de visualização `at` é configurada como metade da altura inicial da câmera (1.25), o que proporciona uma visualização vista com uma componente "para baixo", tal como seria em uma vista aérea como a de um drone ou helicóptero;
-   São declarados dois métodos privados nas linhas 29 e 30: `travaCamera()` impede o deslocamento da câmera para além dos limites do terreno; `extremo()` testa se a câmera já alcançou algum desses limites.


### camera.cpp

Utilizando o princípio do LookAt que, com o novo ângulo de observação, converte o deslocamento para frente e para trás em um *zoom*, na prática. A distância da perspectiva foi configurada em 10.0 (linha 9), permitindo uma visualização praticamente integral dos elementos em todas as posições, exceto nos pontos mais próximos aos extremos das diagonais.
Temos a adição aos métodos originais dos métodos privados listados abaixo, que impedem o movimento da câmera para uma distância exagerada:

#### travaCamera – linhas 49 a 57

Aqui, é testado se as coordenadas de superfície não ultrapassam as coordenadas do chão estabelecidas anteriormente. Logo, devem manter-se entre -5 e 5. Já para a altura, os limites têm a mesma dimensão, mas partem do 0 (altura do solo) à altura máxima 10, formando um cubo de posições viáveis.
Este método é invocado antes de `computeViewMatrix` nos métodos `dolly`, `truck` e `pan`, impedindo que a visualização da câmera se afaste demais no resultado final.

#### extremo – linhas 60 a 63

Este método verifica se a câmera atingiu uma das situações extremas listadas no método `travaCamera` após um dos cálculos realizados, impedindo que algum movimento impróprio ocorra nestas posições. Ele é uma condição que limita o cálculo de `at` nos casos em que os deslocamentos de `dolly` ou `truck` são acionados. `pan` não se encaixa neste caso pois é uma rotação simples.


### window.hpp

Este arquivo de cabeçalho reúne todos as variáveis e métodos que centralizam as funcionalidades da aplicação. Logo na linha 9, é definido um total de 100 "prédios" no cenário.
-   Entre as linhas 14 a 18, é definida a mesma `struct Vertex` definida nas notas de aula;
-   Na sequência, é definida a classe `Window` (linhas 20 a 59):
    -   Entre as linhas 23 e 29, são criados os métodos da classe `abcg::OpenGLWindow` que são sobrescritos – e detalhados na seção de `window.cpp`;
    -   Na linha 32, a variável `tamanhoTela` é declarada. Ela será útil para o caso de redimensionamento da janela;
    -   Nas linhas 34 a 37, os arrays e buffers são inicializados, bem como a variável que armazena o programa;
    -   A localização das variáveis dos shaders estão inicializadas no trecho de linhas 39-42;
    -   Entre as linhas 44 e 47, são instanciadas a câmera e as variáveis que definem as três velocidades que definem seu movimento;
    -   O objeto `chao` é declarado na linha 49, seguindo a implementação descrita anteriormente;
    -   Nas linhas 50 e 51, vetores de vértices e índices dos entes que serão desenhados são declarados;
    -   Na linha 53, é declarado um gerador de números pseudo-aleatórios. Os vetores de linhas 54 a 56 definem os dados para a confecção de cada um dos 100 prédios (ou o valor que for alterado no `define` da linha 9):
        -   `cores` armazena os valores dos canais RGB para cada um dos prédios;
        -   `escalas` define os valores de escala em cada uma das três dimensões, que converterá o cubo de `box.obj` em paralelepípedos de diferentes proporções;
        -   `centros` armazena as coordenadas espaciais do centro da face inferior de cada um desses paralelepípedos.
    -   Por último, é declarado o método `loadModelFromFile`, extraído diretamente das notas de aula, com alterações pontuais.


### window.cpp

Este código-fonte implementa o definido em `window.hpp`. No início, a definição da Hash de `Vertex` segue o implementado em exemplos de aula (linhas 5-12).

#### onCreate – linhas 14 a 74

O código deste método inicia-se carregando o endereço lógico da pasta `assets` (linha 16). A seguir, o gerador pseudo-aleatório `r` é semeado com o relógio do computador (linha 18).
-   Quatro distribuições uniformes são inicializadas (linhas 19 a 22):
    -   `distSup` define os valores das escalas de largura e comprimento dos edifícios, delimitado entre 25% e 75% da medida original do modelo;
    -   `distAlt` define os valores possíveis da escala de altura dos edifícios, entre 0,5x e 2,5x a altura do modelo original;
    -   `distPos` define os valores de coordenadas no terreno entre -4 e +4 em ambas as direções. Com o limite de tamanho em superfície, é garantido que todos os elementos estarão dispostos sobre o quadrado de coordenadas -5 a +5 em ambas as direções;
    -   `distCor` define os canais RGB como sendo pelo menos 70% do valor máximo, gerando cores claras, visando atrasar o escurecimento gradual com a distância.
-   Os dados dos prédios são armazenados nos vetores carregando os valores aleatórios (laço `for` das linhas 25 a 30);
-   O fundo da aplicação é configurado como sendo cinza 20% (linha 32);
-   O programa dos shaders é carregado no trecho de linhas 35-39, e suas variáveis uniformes são referenciadas no bloco de linhas 42-45;
-   Nas linhas 47 e 48, temos a criação do objeto `chao` e, em seguida, o modelo `box.obj` é carregado;
-   Na sequência (linhas 51 a 73), temos os algoritmos de criação e preenchimento do VBO, do EBO e do VAO com os dados gerados.

#### onPaint – linhas 76 a 102

O destaque da implementação deste método é o laço `for` (linhas 88-97) que desenha os elementos que representam os prédios percorrendo os três vetores (`centros`, `escalas` e `cores`). Na linha 100, temos a chamada ao método `paint()` de `chao`, completando a criação dos elementos gráficos.

#### onPaintUI (linha 104) e onResize (linhas 106 a 110)

O primeiro trata-se apenas da chamada a `onPaintUI` da classe mãe. `onResize` faz a variável `tamanhoTela` receber o novo tamanho e recalcula a matriz de projeção da câmera sob os novos parâmetros.

#### onUpdate – linhas 112 a 118

Usando o valor de `deltaTime`, atualiza a posição e a orientação da câmera usando `dolly`, `speed` e `truck` de acordo com as entradas do usuário armazenadas nas respectivas variáveis *Speed*.

#### onEvent – linhas 120 a 147

Por meio dos eventos de pressionamento e liberação das teclas, é possível configurar as velocidades em valores unitários de acordo com o descrito nos comandos listados em "**Sobre a aplicação**", no início deste relatório.

#### onDestroy – linhas 149 a 156

Neste método, temos a chamada do método `destroy` do chão, bem como o apagamento do programa e a liberação do VBO, do EBO e do VAO.
