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
#include "Camera.h"

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

    GLuint getWidthLocation() const { return uniformWidthPosition; };

    GLuint getHeightLocation() const { return uniformHeightPosition; };

    GLuint getIsTexturedLocation() const { return uniformIsTextured; };

    GLuint getTextureBuffer() const { return texCoordinateBuffer; };

    Material &getMaterial();

    void addTexture(Texture &texture, int textureLayout) {
        m_textures.push_back(std::make_shared<Texture>(texture));
        m_texturesLayout.push_back(std::make_shared<int>(textureLayout));
    };

    bool isTextured() { return (m_textures.size() > 0); }

    void setRotation(glm::vec3 axis, float value);

    void setTranslate(glm::vec3 rotation);

    void setScale(glm::vec3 scale);

    void setRotationX(float value) { rotationX = value; };

    void setRotationY(float value) { rotationY = value; };

    void setRotationZ(float value) { rotationZ = value; };

private:
    bool isIndexed();

    void readFromFile(const std::string &path);

    glm::mat4 getRotationX();

    glm::mat4 getRotationY();

    glm::mat4 getRotationZ();

    glm::mat4 modelMatrix = glm::mat4(1.0);
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
    GLuint vaoVertexArray;
    GLuint uniformWidthPosition;
    GLuint uniformHeightPosition;
    std::vector<std::shared_ptr<Texture>> m_textures;
    std::vector<std::shared_ptr<int>> m_texturesLayout;
    bool isRotating = false;
    glm::mat4 translateMatrix = glm::mat4(1.0);
    glm::mat4 rotateMatrix = glm::mat4(1.0);
    glm::mat4 scaleMatrix = glm::mat4(1.0);
    float rotationX = 0.f;
    float rotationY = 0.f;
    float rotationZ = 0.f;

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
