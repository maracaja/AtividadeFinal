#version 300 es

layout(location = 0) in vec3 posicao;
layout(location = 1) in vec3 inNormal;

uniform vec4 cor;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform mat3 normal;


// Light properties
uniform vec4 lightDirWorldSpace;
uniform vec4 Ia, Id, Is;

// Material properties
uniform vec4 Ka, Kd, Ks;
uniform float shininess;

out vec4 fragColor;


vec4 Phong(vec3 N, vec3 L, vec3 V) {
  N = normalize(N);
  L = normalize(L);

  // Compute lambertian term
  float lambertian = max(dot(N, L), 0.0);

  // Compute specular term
  float specular = 0.0;
  if (lambertian > 0.0) {
    // vec3 R = normalize(2.0 * dot(N, L) * N - L);
    vec3 R = reflect(-L, N);
    V = normalize(V);
    float angle = max(dot(R, V), 0.0);
    specular = pow(angle, shininess);
  }

  vec4 diffuseColor = Kd * Id * lambertian;
  vec4 specularColor = Ks * Is * specular;
  vec4 ambientColor = Ka * Ia;

  return ambientColor + diffuseColor + specularColor;
}



void main() 
{
    vec4 posEye = view * model * vec4(posicao, 1);
    float i = 1.0 + 0.1 * posEye.z;
    //fragColor = vec4(i, i, i, 1) * cor;

    vec3 P = (view * model * vec4(posicao, 1.0)).xyz;
    vec3 N = normal * inNormal;
    vec3 L = -(view * lightDirWorldSpace).xyz;
    vec3 V = -P;
    fragColor = Phong(N, L, V);


    gl_Position = proj * posEye;
}