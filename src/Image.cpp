//
// Created by Christoph Vögele on 07/04/2021.
//

#include <stb_image.h>
#include <iostream>
#include "Image.h"

Image::Image(const std::string &path) {

    int sx, sy, n;

    unsigned char *imageData = stbi_load(path.c_str(), &sx, &sy, &n, STBI_rgb_alpha);

    m_width = sx;
    m_height = sy;
    m_channels = n;
    data = imageData;
}

Image::Image() {

}
