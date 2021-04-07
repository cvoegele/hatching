//
// Created by Christoph Vögele on 07/04/2021.
//

#ifndef HATCHING_IMAGE_H
#define HATCHING_IMAGE_H

#include <string>
#include <glm/vec3.hpp>

class Image {
public:
    Image(const std::string &path);
    Image();

    unsigned char *data;

    int width() const { return m_width; }

    int height() const { return m_height; }

    int channels() const { return m_channels; }

    int size() const { return width() * height(); }


private:
    int m_width;
    int m_height;
    int m_channels;
};


#endif //HATCHING_IMAGE_H
