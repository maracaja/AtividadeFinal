# Atividade 3
#### Sérgio Maracajá Junior - RA 11000315
#### Vinícius Lacerda Gonsalez - RA 11____15

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

### window.cpp
