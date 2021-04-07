//
// Created by Christoph Vögele on 21/03/2021.
//

#ifndef TEST_MESH_H
#define TEST_MESH_H

#include "Material.h"
#include "Texture.h"

class Mesh {
public:
    Mesh(Material material, const std::string &path);

    void push();

    void draw();

    glm::mat4x4 getModelMatrix();

    glm::mat4x4 getNormalModelMatrix() { return determinant(getModelMatrix()) * transpose(inverse(getModelMatrix())); };

    GLuint getMVPLocation() const { return uniformMvpPosition; };

    GLuint getMLocation() const { return uniformMPosition; };

    GLuint getMNormalLocation() const { return uniformMNormalPosition; };

    GLuint getCameraLocation() const { return uniformCameraPosition; };

    Material &getMaterial() { return material; };

    void setTexture(Texture texture) {
        this->texture = texture;
        textured = true;
    };

    bool isTextured() { return textured; }

private:
    bool isIndexed() { return !indices.empty(); };

    void readFromFile(const std::string &path);

    GLuint uniformMvpPosition;
    GLuint uniformMPosition;
    GLuint uniformCameraPosition;
    GLuint uniformMNormalPosition;
    GLuint vertexBuffer;
    GLuint colorBuffer;
    GLuint indexBuffer;
    GLuint normalBuffer;
    GLuint texCoordBuffer;
    bool textured = false;

protected:
    explicit Mesh(Material material);

    Material material;
    Texture texture;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> colors;
    std::vector<glm::vec3> texCoords;
    std::vector<int> indices;

    void computeNormals();
};

#endif //TEST_MESH_H
