#version 400 core

in vec3 vPos;
in vec3 vCol;
in vec3 vNor;
in vec3 vTexCoord;

uniform mat4 MVP;
uniform mat4 M;
uniform mat4 MNor;

out vec3 color;
out vec3 normal;
out vec3 worldPos;
out vec2 texCoord;
out vec2 screenPos;

void main()
{
    vec4 projected = MVP * vec4(vPos, 1.0);
    screenPos = projected.xy;
    gl_Position = projected;
    color = vCol;
    worldPos = (M * vec4(vPos, 1.0)).xyz;
    normal = ((MNor) * vec4(vNor, 1.0)).xyz;
    texCoord = vTexCoord.xy;
}