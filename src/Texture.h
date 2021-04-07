//
// Created by Christoph Vögele on 07/04/2021.
//

#ifndef HATCHING_TEXTURE_H
#define HATCHING_TEXTURE_H

#include <string>
#include "commonincludes.h"

class Texture {
public:
    Texture(std::string imagePath);

    Texture();

    ~Texture();

    void setup();

    void generateMipMaps();

    GLuint getTextureBuffer() { return textureBuffer; };

private:
    GLuint textureBuffer;
    std::string imagePath;
};


#endif //HATCHING_TEXTURE_H
