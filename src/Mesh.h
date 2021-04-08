//
// Created by Christoph Vögele on 21/03/2021.
//

#ifndef TEST_MESH_H
#define TEST_MESH_H


#include <vector>
#include <memory>
#include <glm/mat4x4.hpp>
#include "Material.h"
#include "Texture.h"

class Mesh {
public:
    Mesh(Material material, const std::string &path);

    void push();

    void draw();

    glm::mat4x4 getModelMatrix();

    glm::mat4x4 getNormalModelMatrix();

    GLuint getMVPLocation() const;

    GLuint getMLocation() const;

    GLuint getMNormalLocation() const;

    GLuint getCameraLocation() const;

    GLuint getIsTexturedLocation() const { return uniformIsTextured; };

    GLuint getTextureBuffer() const { return texCoordinateBuffer; };

    Material &getMaterial();

    void setTexture(Texture &texture) { m_textures.push_back(std::make_shared<Texture>(texture)); };

    bool isTextured() { return (m_textures.size() > 0); }

private:
    bool isIndexed();

    void readFromFile(const std::string &path);


    GLuint uniformMvpPosition;
    GLuint uniformMPosition;
    GLuint uniformCameraPosition;
    GLuint uniformMNormalPosition;
    GLuint uniformIsTextured;
    GLuint vertexBuffer;
    GLuint colorBuffer;
    GLuint indexBuffer;
    GLuint normalBuffer;
    GLuint texCoordinateBuffer;
    std::vector<std::shared_ptr<Texture>> m_textures;

protected:
    explicit Mesh(Material material);


    Material material;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> colors;
    std::vector<glm::vec3> texCoords;
    std::vector<int> indices;

    void computeNormals();
};

#endif //TEST_MESH_H
