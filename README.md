# Atividade 3
#### Sérgio Maracajá Junior - RA 11000315
#### Vinícius Lacerda Gonsalez - RA 11126315

* * *

## Sobre a aplicação

A presente aplicação apresenta um modelo simplificado de uma vista aérea de uma cidade, usando transformações de câmera para navegar na visualização e paralelepípedos de diferentes dimensões baseados em um mesmo modelo simulando prédios.

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

Este arquivo acabou por ser, na prática, uma repetição do código apresentado no LookAt, com o método `main` instanciando a aplicação (linha 7), gerando e configurando a janela onde a aplicação reside (linhas 8-15), e chamando seu método `run` (linha 16), tudo isso dentro de uma estrutura `try-catch`.


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

### camera.cpp


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

O código deste método inicia-se carregando o endereço lógico da pasta `assets`. A seguir, o gerador pseudo-aleatório `r` é semeado com o relógio do computador.
-   Quatro distribuições uniformes são inicializadas:
    -   `distSup` define os valores das escalas de largura e comprimento dos edifícios, delimitado entre 25% e 75% da medida original do modelo;
    -   `distAlt` define os valores possíveis da escala de altura dos edifícios, entre 0,5x e 2,5x a altura do modelo original;
    -   `distPos` define os valores de coordenadas no terreno entre -4 e +4 em ambas as direções. Com o limite de tamanho em superfície, é garantido que todos os elementos estarão dispostos sobre o quadrado de coordenadas -5 a +5 em ambas as direções;
    -   `distCor` define os canais RGB como sendo pelo menos 70% do valor máximo, gerando
