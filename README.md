# Atividade 4
#### Sérgio Maracajá Junior - RA 11000315
#### Vinícius Lacerda Gonsalez - RA 11126315

* * *

## Sobre a aplicação

A presente aplicação trata-se de uma atualização da Atividade 3, que apresenta um modelo simplificado de uma vista aérea de uma cidade, usando transformações de câmera baseadas no *LookAt* para navegar na visualização e paralelepípedos de diferentes dimensões baseados em um mesmo modelo simulando prédios. Os problemas de navegação apresentados na entrega anterior foram corrigidos e as distorções apresentadas anteriormente foram completamente sanadas.
O terreno onde estes edifícios simulados estão situados tem uma dimensão de 20 x 20 com centro na origem do sistema de coordenadas. Caso a câmera alcance um limite consistente com essas dimensões terrestres e altura 10 partindo da referência do solo, a aplicação não responderá até que seja inserido um comando que devolva a câmera para uma posição válida. A intenção neste caso foi evitar deslocamentos a distâncias que tendam ao infinito.

Para a utilização da navegação, temos os seguintes comandos:
-   **Seta para cima:** aumenta o zoom;
-   **Seta para baixo:** afasta o zoom;
-   **Seta para direita:** rotaciona no sentido horário;
-   **Seta para esquerda:** rotaciona no sentido anti-horário;
-   **Tecla 'A':** desloca-se lateralmente para a esquerda;
-   **Tecla 'D':** desloca-se lateralmente para a direita.

### Problemas

Apesar de diversas tentativas, não conseguimos aplicar de forma satisfatória os efeitos de iluminação e texturização propostos. Assumimos que apenas a interatividade, iniciada na entrega anterior, corresponde aos requisitos desta entrega. Preferimos manter uma versão final que fosse funcional e sem efeitos estranhos em vez de submeter uma tentativa (que muitas vezes, sequer rodou) ou mudar o projeto de última hora, o que muito provavelmente terminaria em um resultado insatisfatório.
Algumas questões, que envolveram a aplicação das texturas e luzes aos diversos objetos criados na aplicação, não foram bem entendidas. Quando muito, chegou-se a uma iluminação que refletiu apenas no solo (!) enquanto os prédios perdiam completamente a cor. As tentativas de apresentar uma textura, quando muito, simplesmente não apareceram ou resultavam em toda uma série de *crashes* cujas origens foram impossíveis de detectar.

* * *

## Shaders

### lookat.frag

Este shader realiza apenas uma operação importante: se a câmera em algum momento atravessar alguma estrutura, esta aparecerá mais escura, com metade da intensidade, permanecendo com a cor normal em qualquer outro caso (linhas 11 e 12).


### lookat.vert

Aqui, no `main` (linhas 12-18), a posição da câmera no cenário é refeita após a atualização dos valores de `model`, `view` e `posicao`, bem como esta posição calculada influencia na perda de intensidade (calculada se essa diferença vai até 20 unidades de distância), gerando um efeito de escurecimento gradual até uma perspectiva similar a uma sombra no horizonte, antes do desaparecimento.

### chao.vert e chao.frag

Buscou-se aqui, como uma última tentativa, realizar ao menos o mapeamento planar do recurso `asfalto.png` ao chão, mas o mesmo nem mesmo foi exibido nas versões que chegavam a ser executadas. Era pretendido repetir a textura de asfalto criada em atividade passada (<https://github.com/maracaja/Carros>), mas não ficou claro se isso era realmente possível. Em certo momento, chegou-se a "chuviscar" toda a tela, mas a ideia acabou também abandonada.

* * *

## Implementação

Segue abaixo a descrição do código-fonte, contido na pasta do projeto como mais um exemplo na pasta `examples`, sob o título `atividade1`. Além dos arquivos C++ que serão descritos mais adiante, foram realizadas as seguintes adições ao projeto:

-   Em `examples/CMakeLists.txt`, há apenas a linha de código `add_subdirectory(atividade4)`;
-   Em `public`, além dos arquivos gerados pela compilação do WASM, a página `helloworld.html` foi modificada a linha 258 para que a página execute o arquivo `atividade4.js`;
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

A aplicação da câmera se tratou de uma variação do lookAt, com complementos que impedem que a câmera exceda limites de distância, sempre estando sobre o terreno delimitado pela classe `Chao`.
-   Assim como no original, são declarados nas linhas 12 a 16 os métodos públicos que comandam a movimentação e os cálculos de matrizes de transformações. Os retornos dessas matrizes (declaradas de forma privada nas linhas 26 e 27) são apresentados pelos métodos presentes nas linhas 18 e 19;
-   A câmera, localizada pela variável `eye` (linha 22), inicia com altura 3.0, valor pouco acima da altura máxima configurada para um edifício. Também a posição apresenta-se deslocada a um quarto da distância máxima em relação à origem, em -2.5 no eixo z;
-   O ponto de visualização `at` é configurada como metade da altura máxima de um prédio (1.25), o que proporciona uma visualização vista com uma componente "para baixo", tal como seria em uma vista aérea como a de um drone ou helicóptero;
-   Na linha 29, é declarado o método privado `extremo()` testa se a câmera já alcançou algum dos limites para a visualização: as configurações do chão estabelecidas anteriormente definem que as coordenadas de x e z devem manter-se entre -10 e 10. Já para a altura, definiu-se uma altura máxima 10 enquando a coordenada mínima para y é rente ao chão, ou seja, 0.


### camera.cpp

Utilizando o princípio do LookAt que, com o novo ângulo de observação, converte o deslocamento para frente e para trás em um *zoom*, na prática. A distância da perspectiva foi configurada em 28.3 (linha 9), aproximadamente 10√2, permitindo uma visualização integral dos elementos em todas as posições.
Temos a adição aos métodos originais do método privado abaixo, que impede o movimento da câmera para uma distância exagerada:

#### extremo – linhas 53 a 56

Este método verifica se a câmera atingiu uma das situações extremas listadas no método `travaCamera` após um dos cálculos realizados, impedindo que algum movimento impróprio ocorra nestas posições. Ele estabelece uma condição que limita os cálculos de `at` e `eye` nos casos em que os deslocamentos de `dolly` ou `truck` são acionados e gerariam uma posição de `eye` futura que saísse do espaço delimitado , enquanto comandos que levem a posição da câmera para uma posicao válida não são bloqueados. Eventuais distorções nas bordas do terreno também não ocorrem mais devido à correta aplicação deste método dentro de `dolly` e `truck`.
O método `pan` não foi afetado neste caso pois é uma rotação simples.


### window.hpp

Este arquivo de cabeçalho reúne todos as variáveis e métodos que centralizam as funcionalidades da aplicação. Logo na linha 9, é definido um total de 500 "prédios" no cenário.
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
    -   `distPos` define os valores de coordenadas no terreno entre -9 e +9 em ambas as direções. Com o limite de tamanho em superfície, é garantido que todos os elementos estarão dispostos sobre o quadrado de coordenadas -10 a +10 em ambas as direções;
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
