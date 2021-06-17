//
// Created by Christoph Vögele on 07/04/2021.
//

#include <stb_image.h>
#include <iostream>
#include "Texture.h"

Texture::Texture(std::string imagePath) : imagePath(imagePath) {
    minFilter = GL_NEAREST;
    maxFilter = GL_NEAREST;
    wrapS = GL_REPEAT;
    wrapT = GL_REPEAT;
}

Texture::Texture() {
    minFilter = GL_NEAREST;
    maxFilter = GL_NEAREST;
    wrapS = GL_REPEAT;
    wrapT = GL_REPEAT;
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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, maxFilter);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

    //glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(imageData);
}

void Texture::generateMipMaps() {
    glBindTexture(GL_TEXTURE_2D, textureBuffer);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}





