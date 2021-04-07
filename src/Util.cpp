//
// Created by Christoph Vögele on 16/03/2021.
//

#include "Util.h"
#include "example-utils.hpp"
#include "Mesh.h"
#include <tinyply.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <glm/vec3.hpp>
#include <stb_image.h>

std::string Util::readFile2(const std::string &fileName) {
    constexpr auto read_size = std::size_t{4096};
    auto stream = std::ifstream{fileName};
    stream.exceptions(std::ios_base::badbit);

    auto out = std::string{};
    auto buf = std::string(read_size, '\0');
    while (stream.read(&buf[0], read_size)) {
        out.append(buf, 0, stream.gcount());
    }
    out.append(buf, 0, stream.gcount());
    return out;
}

unsigned char* Util::readImage(const std::string &imagePath) {

    int sx, sy, n;

    unsigned char *imageData = stbi_load(imagePath.c_str(), &sx, &sy, &n, 0);

    return imageData;
}

