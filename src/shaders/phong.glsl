#version 420 core

out vec4 colour;

in vec3 worldPos;
in vec4 color;
in vec3 normal;
in vec2 texCoord;

uniform vec3 cameraPos;

layout (binding = 0) uniform sampler2D texture0;
layout (binding = 1) uniform sampler2D texture1;
//uniform sampler2D texture0;
//uniform sampler2D texture1;

uniform int isTex;

//Declaration
vec4 lambertDiffuse(vec3 n, vec3 lightToPoint);
vec4 specular(vec3 n, vec3 lightToPoint, vec3 eyeToPoint);

void main()
{
    if (isTex == 1) {
        colour =  texture(texture1, texCoord) * texture(texture0, texCoord);
        //colour = vec4(texCoord, 0.0, 1.0);
    } else {

        vec3 lightPosition = vec3(-10, 50, -10);
        vec3 lightToPoint = normalize(lightPosition - worldPos);
        vec3 n = normalize(normal);
        vec3 eyeToPoint = normalize(cameraPos - worldPos);

        colour = lambertDiffuse(n, lightToPoint) + specular(n, lightToPoint, eyeToPoint);
    }
}

//Definition
vec4 lambertDiffuse(vec3 n, vec3 lightToPoint) {
    float angle = dot(n, lightToPoint);
    vec4 diffuse = color * angle;

    if (angle > 0) {
        return diffuse;
    } else {
        return vec4(0.0, 0.0, 0.0, 1.0f);
    }
}

vec4 specular(vec3 n, vec3 lightToPoint, vec3 eyeToPoint) {
    vec3 r = ((dot(lightToPoint, n) * 2) * n) - lightToPoint;
    float k = 10.0;
    float rr = dot(normalize(r), eyeToPoint);
    vec3 specular = vec3(1, 1, 1) * pow(rr, k);

    if (dot(n, lightToPoint) > 0 && rr > 0) {
        return vec4(specular, 1.0f);
    } else {
        return vec4(0.0, 0.0, 0.0, 1.0f);
    }
}


