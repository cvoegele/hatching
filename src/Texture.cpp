//
// Created by Christoph Vögele on 07/04/2021.
//

#include <stb_image.h>
#include <iostream>
#include "Texture.h"

Texture::Texture(std::string imagePath) : imagePath(imagePath) {

}

Texture::Texture() {

}


Texture::~Texture() {
    glDeleteBuffers(1, &textureBuffer);
}

void Texture::setup() {

    unsigned char *imageData;
    int width;
    int height;
    int n;

    imageData = stbi_load(imagePath.c_str(), &width, &height, &n, STBI_rgb_alpha);

    glGenTextures(1, &textureBuffer);
    glBindTexture(GL_TEXTURE_2D, textureBuffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(imageData);
}

void Texture::generateMipMaps() {
    glGenerateMipmap(GL_TEXTURE_2D);
}





