//
// Created by Christoph Vögele on 21/03/2021.
//

#ifndef TEST_MESH_H
#define TEST_MESH_H


#include <vector>
#include <glm/mat4x4.hpp>
#include "Material.h"

class Mesh {
public:
    Mesh(Material material);

    Mesh(Material material, const std::string &path);

    void push();

    void draw();

    glm::mat4x4 getModelMatrix();

    GLuint getMVPLocation() const;

    Material &getMaterial();

private:
    bool isIndexed();
    void readFromFile(const std::string& path);

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> colors;
    std::vector<int> indices;
    Material material;
    GLuint uniformMvpPosition;
    GLuint vertexBuffer;
    GLuint colorBuffer;
    GLuint indexBuffer;

};

#endif //TEST_MESH_H
