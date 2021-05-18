//
// Created by Christoph Vögele on 29/04/2021.
//

#include "Sphere.h"

Sphere::Sphere(Material material) : Mesh(material, "../data/ply/sphere.ply") {

    normals.clear();
    texCoords.clear();

    for (auto& vertex : vertices) {
        auto normal = glm::normalize(vertex);
        auto texCoordinate = glm::vec3(normal.x, normal.y, 0);
        normals.push_back(normal);
        texCoords.push_back(texCoordinate);
    }
}
