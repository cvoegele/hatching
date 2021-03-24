//
// Created by Christoph Vögele on 21/03/2021.
//

#include <glad/gl.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Mesh.h"


void Mesh::push() {

    float *flatVertices = &vertices[0].x;
    float *flatColors = &colors[0].x;

    //save as member, all glGen- Calls
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size() * 3, flatVertices, GL_STATIC_DRAW);
    GLuint verticesPosition = glGetAttribLocation(material.getProgram(), "vPos");
    glEnableVertexAttribArray(verticesPosition);
    glVertexAttribPointer(verticesPosition, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * colors.size() * 3, flatColors, GL_STATIC_DRAW);
    GLuint colorPosition = glGetAttribLocation(material.getProgram(), "vCol");
    glEnableVertexAttribArray(colorPosition);
    glVertexAttribPointer(colorPosition, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), indices.data(), GL_STATIC_DRAW);

    uniformMvpPosition = glGetUniformLocation(material.getProgram(), "MVP");
}

Mesh::Mesh(Material material)
        : vertices(std::vector<glm::vec3>()),
          colors(std::vector<glm::vec3>()),
          indices(std::vector<int>()),
          material(material),
          modelMatrix(glm::mat4x4()),
          uniformMvpPosition(0),
          indexBuffer(0),
          vertexBuffer(0),
          colorBuffer(0) {

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

    for (int & vertexIndice : vertexIndices) {
        indices.push_back(vertexIndice);
    }

}

void Mesh::draw() {
    int width, height;
    width = 640;
    height = 480;

    glm::mat4 v = glm::lookAt(glm::vec3(0, 0, -3),
                              glm::vec3(0, 0, 0),
                              glm::vec3(0, 1, 0));

    glm::mat4x4 m, p, mvp;
    m = getModelMatrix();
    glm::rotate(m, (float) glfwGetTime(), glm::vec3(0.f, 0.f, 1.f));
    p = glm::perspective(45.f,
                         (float) width / (float) height,
                         0.1f, 1000.f);

    mvp = p * v * m;

    material.useProgram();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

    glUniformMatrix4fv(uniformMvpPosition, 1, GL_FALSE, &mvp[0][0]);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
}

glm::mat4x4 Mesh::getModelMatrix() {
    double time = glfwGetTime();
    glm::mat4 r = glm::rotate(glm::mat4(1.0), (float) time / 10.f, glm::vec3(1, -1, 1));
    return glm::mat4(1.0) * r;
}
