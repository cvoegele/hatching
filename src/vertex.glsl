#version 400 core

in vec3 vPos;
in vec3 vCol;
uniform mat4 MVP;
out vec3 color;

void main()
{
    gl_Position = MVP * vec4(vPos, 1.0);
    color = vCol;
}