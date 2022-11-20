#version 300 es

layout(location = 0) in vec2 posicao;
layout(location = 1) in vec3 cor;

uniform float tamanho;

out vec4 fragColor;

void main() 
{
    gl_PointSize = tamanho;
    gl_Position = vec4(posicao.xy, 0, 1);
    fragColor = vec4(cor, 1);
}