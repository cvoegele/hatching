#version 400 core

out vec4 colour;

in vec3 color;
in vec3 normal;
in vec3 worldPos;
in vec2 texCoord;

uniform sampler2D texture0;

void main() {

    vec4 newT = -(vec4(worldPos, 1.0) - vec4(1,1,0.0,0.0)) / 2.0;

    colour = texture(texture0, newT.xy);
}
