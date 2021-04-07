//
// Created by Christoph Vögele on 07/04/2021.
//

#include "Texture.h"

Texture::Texture(Image image) : m_image(image) {

}

Texture::Texture() {
}

Texture::~Texture() {
    glDeleteBuffers(1, &textureBuffer);
}

void Texture::setup() {
    glGenTextures(1, &textureBuffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, textureBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_image.width(), m_image.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, m_image.data);
}

void Texture::generateMipMaps() {
    glGenerateMipmap(GL_TEXTURE_2D);
}




