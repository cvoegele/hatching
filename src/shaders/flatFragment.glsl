#version 400 core

out vec4 colour;

in vec3 color;
in vec3 normal;
in vec3 worldPos;
in vec2 texCoord;

uniform sampler2D texture0;

void main() {

    vec2 uv = (((vec4(worldPos, 1.0) + vec4(1,1,0.0,0.0)) / 2.0).xy);

    colour = texture(texture0, uv);
}
