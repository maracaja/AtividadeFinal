#version 300 es

precision mediump float;

in vec2 fragTexCoord;
in vec3 fragP;

uniform vec4 Kd;
uniform sampler2D diffuseTex;

out vec4 outColor;

vec2 planarMappingY(vec3 P) 
{ return vec2(P.x, 1.0 - P.z); }

void main()
{
    vec3 offset = vec3(-0.5, 0.0, -0.5);
    vec2 texCoord = planarMappingY(fragP + offset);
    vec4 map_Kd = texture(diffuseTex, texCoord);
    outColor = map_Kd * Kd;
}