#version 420 core

out vec4 colour;

in vec3 worldPos;
in vec4 color;
in vec3 normal;
in vec2 texCoord;
in vec2 screenPos;

uniform vec3 cameraPos;

layout (binding = 3) uniform sampler2D texture0;
layout (binding = 4) uniform sampler2D texture1;
layout (binding = 5) uniform sampler2D texture2;
layout (binding = 6) uniform sampler2D texture3;
layout (binding = 7) uniform sampler2D texture4;


uniform int isTex;

//Declaration
vec4 lambertDiffuse(vec3 n, vec3 lightToPoint, vec4 colorX);
vec4 specular(vec3 n, vec3 lightToPoint, vec3 eyeToPoint, float k);
vec4 modifiyTextureColor(float modifier, float brightness, vec4 texture);

void main()
{
    if (isTex == 1) {
        vec4 lightTexture =  texture(texture0, texCoord);
        vec4 mediumTexture =  texture(texture1, texCoord);
        vec4 darkTexture =  texture(texture2, texCoord);
        vec4 reallyDarkTexture =  texture(texture3, texCoord);
        vec4 reallyReallyDarkTexture =  texture(texture4, texCoord);

        vec3 lightPosition = vec3(5, 5, 2);
        vec3 lightToPoint = normalize(lightPosition - worldPos);
        vec3 n = normalize(normal);
        vec3 eyeToPoint = normalize(cameraPos - worldPos);

        vec4 color = 0.9 * lambertDiffuse(n, lightToPoint, vec4(1, 1, 1, 1)) + 0.1 * specular(n, lightToPoint, eyeToPoint, 50);

        float brightness = 0.299 * color.r + 0.587 * color.g + 0.114 * color.b;

        //colour = color;

        //colour = vec4(brightness, brightness, brightness, 1.0);
        colour = clamp((modifiyTextureColor(0.6, brightness, reallyReallyDarkTexture)
        + modifiyTextureColor(0.4, brightness, reallyDarkTexture)
        + modifiyTextureColor(1, brightness, lightTexture)
        + modifiyTextureColor(0.8, brightness, mediumTexture)
        + modifiyTextureColor(0.1, brightness, reallyReallyDarkTexture)), 0, 1);
        colour.xyz = vec3(1 - colour.a);

        float c = 0;
        float f = (c + 1) / (1 - c);

        float a = 0.8;
        float b = 0.0;

        colour.xyz = f * (colour.xyz - 0.5) +0.5;

        colour.xyz = colour.xyz * vec3(0,0.5,1);

        colour.a = 1;

        // +  mediumTexture * vec4(1, 1, 1, 0.5);// + darkTexture * vec4(1, 1, 1, 0.8 - brightness) +  reallyDarkTexture * vec4(1, 1, 1, 1 - brightness);
        //        vec4 lightest = lightTexture * (brightness) * vec4(1.0, 1.0, 1.0, 1.0);
        //        vec4 darkes = darkTextures * (1 - brightness) + vec4(1.0, 1.0, 1.0, 1.0) * (brightness);
        //        colour = lightest;
        //colour = darkTexture * (1 - brightness);

        //colour = clamp(lightTexture * vec4(1, 1, 1, 1 - brightness), 0, 1f);// + mediumTexture + darkTexture + reallyDarkTexture;

    }
    else {
        colour = vec4(1.0, 0, 0, 1.0);
    }
}

//Definition
vec4 lambertDiffuse(vec3 n, vec3 lightToPoint, vec4 colorX) {
    float angle = dot(n, lightToPoint);
    vec3 diffuse = colorX.xyz * angle;

    if (angle > 0) {
        return vec4(diffuse, colorX.w);
    } else {
        return vec4(0.0, 0.0, 0.0, 1f);
    }
}

vec4 specular(vec3 n, vec3 lightToPoint, vec3 eyeToPoint, float k) {
    vec3 r = ((dot(lightToPoint, n) * 2) * n) - lightToPoint;
    float rr = dot(normalize(r), eyeToPoint);
    vec3 specular = vec3(1, 1, 1) * pow(rr, k);

    if (dot(n, lightToPoint) > 0 && rr > 0) {
        return vec4(specular, 1f);
    } else {
        return vec4(0.0, 0.0, 0.0, 1f);
    }
}

vec4 modifiyTextureColor(float modifier, float brightness, vec4 texture) {
    return vec4(texture.xyz, clamp(texture.w * (modifier - brightness), 0, 1) / modifier);
}


