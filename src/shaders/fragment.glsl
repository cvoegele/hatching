#version 400 core

in vec3 color;
in vec3 normal;

void main()
{
    //gl_FragColor = vec4(color, 1.0);
    gl_FragColor = vec4((normalize(normal)  + 0.5), 1.0);
}