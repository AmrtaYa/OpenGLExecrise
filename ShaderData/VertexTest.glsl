#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 FragPos;
out vec2 TexCoord;
out vec3 Normal;

uniform mat4 transform;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

void main()
{
    gl_Position = projMat * viewMat * modelMat * vec4(aPos, 1.0f);
    FragPos = vec3(modelMat * vec4(aPos, 1.0f));
    Normal =  mat3(transpose(inverse(modelMat))) *aNormal;
    TexCoord= aTexCoord;

}