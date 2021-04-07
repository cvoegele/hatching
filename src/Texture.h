//
// Created by Christoph Vögele on 07/04/2021.
//

#ifndef HATCHING_TEXTURE_H
#define HATCHING_TEXTURE_H

#include <glad/gl.h>
#include "Image.h"

class Texture {
public:
    Texture(Image image);
    Texture();

    ~Texture();

    void setup();

    void generateMipMaps();

    GLuint getTextureBuffer() { return textureBuffer; };

private:
    GLuint textureBuffer;
    Image m_image;
};


#endif //HATCHING_TEXTURE_H
