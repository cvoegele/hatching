//
// Created by Christoph Vögele on 06/04/2021.
//

#include "Cube.h"

Cube::Cube(Material material) : Mesh(material) {

    this->material = material;

    float vert[12 * 3 * 3] = {
            -0.5f, 0.5f, 0.5f, //front
            0.5f, 0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,

            -0.5f, 0.5f, 0.5f,
            -0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,

            0.5f, 0.5f, 0.5f,  //right
            0.5f, 0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,

            0.5f, 0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, -0.5f,

            -0.5f, 0.5f, 0.5f, //left
            -0.5f, 0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, 0.5f, 0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, 0.5f,

            -0.5f, -0.5f, -0.5f, //back
            -0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,

            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,

            -0.5f, 0.5f, -0.5f, //top
            0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, 0.5f,

            -0.5f, 0.5f, -0.5f,
            -0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,

            -0.5f, -0.5f, -0.5f,  //bot
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, 0.5f,

            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f
    };

    for (int i = 0; i < 36 * 3; i += 3) {
        glm::vec3 vertex(vert[i], vert[i + 1], vert[i + 2]);
        vertices.push_back(vertex);
    }

    float vertexColors[12 * 3 * 3] = {
            1.f, 0.f, 0.f,
            1.f, 0.f, 1.f,
            0.f, 1.f, 1.f,

            1.f, 0.f, 0.f,
            0.f, 0.f, 1.f,
            0.f, 1.f, 0.f,

            1.f, 0.f, 0.f,
            0.f, 0.f, 1.f,
            0.f, 1.f, 0.f,

            1.f, 0.f, 0.f,
            0.f, 0.f, 1.f,
            0.f, 1.f, 0.f,

            1.f, 0.f, 0.f,
            0.f, 0.f, 1.f,
            0.f, 1.f, 0.f,

            1.f, 0.f, 0.f,
            0.f, 0.f, 1.f,
            0.f, 1.f, 0.f,

            1.f, 0.f, 0.f,
            0.f, 0.f, 1.f,
            0.f, 1.f, 0.f,

            1.f, 0.f, 0.f,
            0.f, 0.f, 1.f,
            0.f, 1.f, 0.f,

            1.f, 0.f, 0.f,
            1.f, 0.f, 1.f,
            0.f, 1.f, 1.f,

            1.f, 0.f, 0.f,
            0.f, 0.f, 1.f,
            0.f, 1.f, 0.f,

            1.f, 0.f, 0.f,
            0.f, 0.f, 1.f,
            0.f, 1.f, 0.f,

            1.f, 0.f, 0.f,
            0.f, 0.f, 1.f,
            0.f, 1.f, 0.f
    };


    for (int i = 0; i < 36 * 3; i += 3) {
        glm::vec3 color(vertexColors[i], vertexColors[i + 1], vertexColors[i + 2]);
        colors.push_back(color);
    }

    float textureCoordinates[12*3*3] =
            {
                    0.f, 1.f, 0.f,
                    1.f, 1.f, 0.f,
                    1.f, 0.f, 0.f,

                    0.f, 1.f, 0.f,
                    0.f, 0.f, 0.f,
                    1.f, 0.f, 0.f,

                    0.f, 1.f, 0.f,
                    1.f, 1.f, 0.f,
                    1.f, 0.f, 0.f,

                    0.f, 1.f, 0.f,
                    0.f, 0.f, 0.f,
                    1.f, 0.f, 0.f,

                    0.f, 1.f, 0.f,
                    1.f, 1.f, 0.f,
                    1.f, 0.f, 0.f,

                    0.f, 1.f, 0.f, //15
                    1.f, 0.f, 0.f,
                    0.f, 0.f, 0.f,

                    0.f, 1.f, 0.f,
                    1.f, 1.f, 0.f,
                    1.f, 0.f, 0.f,

                    0.f, 1.f, 0.f,
                    0.f, 0.f, 0.f,
                    1.f, 0.f, 0.f,

                    0.f, 1.f, 0.f,
                    1.f, 1.f, 0.f,
                    1.f, 0.f, 0.f,

                    0.f, 1.f, 0.f,
                    0.f, 0.f, 0.f,
                    1.f, 0.f, 0.f,

                    0.f, 1.f, 0.f,
                    1.f, 1.f, 0.f,
                    1.f, 0.f, 0.f,

                    0.f, 1.f, 0.f,
                    0.f, 0.f, 0.f,
                    1.f, 0.f, 0.f,

            };

    for (int i = 0; i < 36 * 3; i += 3) {
        glm::vec3 texCoordinate(textureCoordinates[i], textureCoordinates[i + 1], textureCoordinates[i + 2]);
        texCoords.push_back(texCoordinate);
    }

    int vertexIndices[12 * 3] = {
            0, 2, 1,
            3, 4, 5,
            6, 8, 7,
            9, 10, 11,
            12, 13, 14,
            15, 16, 17,
            18, 19, 20,
            21, 23, 22,
            24, 26, 25,
            27, 28, 29,
            30, 31, 32,
            33, 35, 34
    };

    for (int &vertexIndice : vertexIndices) {
        indices.push_back(vertexIndice);
    }

    computeNormals();
}
