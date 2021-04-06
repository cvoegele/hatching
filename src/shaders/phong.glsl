#version 400 core

out vec4 colour;
in vec3 worldPos;
in vec4 color;
in vec3 outNormal;
in vec3 cameraPosition;
in vec2 outTexCoord;

uniform sampler2D aTexture;
uniform int readFromTexture;
uniform int alpha;

//Declaration
vec4 lambertDiffuse(vec3 n, vec3 lightToPoint);
vec4 specular(vec3 n, vec3 lightToPoint, vec3 eyeToPoint);

void main()
{
    if (alpha == 1) {
        colour = color;
    } else if (readFromTexture == 1) {
        colour = texture(aTexture, outTexCoord.xy);
    }
    else {
        vec3 lightPosition = vec3(-10, 50, -10);
        vec3 lightToPoint = normalize(lightPosition - worldPos);
        vec3 n = normalize(outNormal);
        vec3 eyeToPoint = normalize(cameraPosition - worldPos);

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


