#version 420 core

out vec4 colour;

in vec3 worldPos;
in vec4 color;
in vec3 normal;
in vec2 texCoord;

uniform vec3 cameraPos;
uniform vec3 lightPos;

layout (binding = 0) uniform sampler2D baseTexture;
layout (binding = 1) uniform sampler2D normalMap;
//uniform sampler2D texture0;
//uniform sampler2D texture1;

uniform int isTex;
uniform int isNormalMapped;

//Declaration
vec4 lambertDiffuse(vec3 n, vec3 lightToPoint, vec4 colorAtPixel);
vec4 specular(vec3 n, vec3 lightToPoint, vec3 eyeToPoint);

void main()
{
    vec4 colorAtPixel = color;
    if (isTex == 1) {
        colorAtPixel =  texture(baseTexture, texCoord);
        //colour = vec4(texCoord, 0.0, 1.0)
    }
    vec3 normalAtPixel = normal;
    if (isNormalMapped == 1){
        normalAtPixel = vec3(texture(normalMap, texCoord));
    }

    vec3 lightPosition = lightPos;
    vec3 lightToPoint = normalize(lightPosition - worldPos);
    vec3 n = normalize(normalAtPixel);
    vec3 eyeToPoint = normalize(cameraPos - worldPos);

    colour = lambertDiffuse(n, lightToPoint, colorAtPixel) + specular(n, lightToPoint, eyeToPoint);

}

//Definition
vec4 lambertDiffuse(vec3 n, vec3 lightToPoint, vec4 colorAtPixel) {
    float angle = dot(n, lightToPoint);
    vec4 diffuse = colorAtPixel * angle;

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


