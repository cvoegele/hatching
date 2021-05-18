//
// Created by Christoph Vögele on 08/04/2021.
//

#include "Screen.h"

Screen::Screen(Material material) : Mesh(material) {

    vertices.push_back(glm::vec3(-1, 1, 0));
    vertices.push_back(glm::vec3(1, 1, 0));
    vertices.push_back(glm::vec3(1, -1, 0));

    vertices.push_back(glm::vec3(-1, 1, 0));
    vertices.push_back(glm::vec3(1, -1, 0));
    vertices.push_back(glm::vec3(-1, -1, 0));

    texCoords.push_back(glm::vec3(0, 0, 0));

    texCoords.push_back(glm::vec3(0, 1, 0));
    texCoords.push_back(glm::vec3(1, 0, 0));




    texCoords.push_back(glm::vec3(1, 0, 0));
    texCoords.push_back(glm::vec3(1, 1, 0));
    texCoords.push_back(glm::vec3(0, 1, 0));

    indices.emplace_back(0);
    indices.emplace_back(2);
    indices.emplace_back(1);
    indices.emplace_back(3);
    indices.emplace_back(5);
    indices.emplace_back(4);

}
