#version 300 es

layout(location = 0) in vec3 posicao;
layout(location = 1) in vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec2 fragTexCoord;
out vec3 fragP;

void main()
{
    vec3 P = (view * model * vec4(posicao, 1.0)).xyz;
    fragTexCoord = texCoord;
    fragP = posicao;
    gl_Position = proj * vec4(P, 1.0);
}
