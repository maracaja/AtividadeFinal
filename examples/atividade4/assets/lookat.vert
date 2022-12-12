#version 300 es

layout(location = 0) in vec3 posicao;

uniform vec4 cor;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec4 fragColor;

void main() 
{
    vec4 posEye = view * model * vec4(posicao, 1);
    float i = 1.0 + 0.05 * posEye.z;
    fragColor = vec4(i, i, i, 1) * cor;
    gl_Position = proj * posEye;
}
