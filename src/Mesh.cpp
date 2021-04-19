//
// Created by Christoph Vögele on 21/03/2021.
//

#include "commonincludes.h"
#include <memory>
#include <string>
#include <iostream>
#include <example-utils.hpp>
#include <tinyply.h>
#include <glm/ext.hpp>
#include <stb_image.h>
#include "Mesh.h"
#include "Util.h"

void Mesh::push() {

    glGenVertexArrays(1, &vaoVertexArray);
    glBindVertexArray(vaoVertexArray);

    //Does this do anything????
    material.createProgram();
    glBindAttribLocation(material.getProgram(), 0, "vPos");
    glBindAttribLocation(material.getProgram(), 1, "vCol");
    glBindAttribLocation(material.getProgram(), 2, "vNor");
    glBindAttribLocation(material.getProgram(), 3, "vTexCoord");
    material.linkProgram();

    if (!vertices.empty()) {
        float *flatVertices = &vertices[0].x;
        //save as member, all glGen- Calls
        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size() * 3, flatVertices, GL_STATIC_DRAW);
        GLuint verticesPosition = glGetAttribLocation(material.getProgram(), "vPos");
        glEnableVertexAttribArray(verticesPosition);
        glVertexAttribPointer(verticesPosition, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    }

    if (!colors.empty()) {
        float *flatColors = &colors[0].x;
        glGenBuffers(1, &colorBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * colors.size() * 3, flatColors, GL_STATIC_DRAW);
        GLuint colorPosition = glGetAttribLocation(material.getProgram(), "vCol");
        glEnableVertexAttribArray(colorPosition);
        glVertexAttribPointer(colorPosition, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    }

    if (!normals.empty()) {
        float *flatNormals = &normals[0].x;
        glGenBuffers(1, &normalBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normals.size() * 3, flatNormals, GL_STATIC_DRAW);
        GLuint normalPosition = glGetAttribLocation(material.getProgram(), "vNor");
        glEnableVertexAttribArray(normalPosition);
        glVertexAttribPointer(normalPosition, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    }

    if (!texCoords.empty()) {
        float *flatTexCoords = &texCoords[0].x;
        glGenBuffers(1, &texCoordinateBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, texCoordinateBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * texCoords.size() * 3, flatTexCoords, GL_STATIC_DRAW);
        GLuint texCoordPosition = glGetAttribLocation(material.getProgram(), "vTexCoord");
        glEnableVertexAttribArray(texCoordPosition);
        glVertexAttribPointer(texCoordPosition, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    }

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), indices.data(), GL_STATIC_DRAW);

    uniformMvpPosition = glGetUniformLocation(material.getProgram(), "MVP");
    uniformMPosition = glGetUniformLocation(material.getProgram(), "M");
    uniformCameraPosition = glGetUniformLocation(material.getProgram(), "cameraPos");
    uniformMNormalPosition = glGetUniformLocation(material.getProgram(), "MNor");
    uniformIsTextured = glGetUniformLocation(material.getProgram(), "isTex");
    uniformWidthPosition = glGetUniformLocation(material.getProgram(), "width");
    uniformHeightPosition = glGetUniformLocation(material.getProgram(), "height");

}

Mesh::Mesh(Material material)
        : vertices(std::vector<glm::vec3>()),
          colors(std::vector<glm::vec3>()),
          indices(std::vector<int>()),
          normals(std::vector<glm::vec3>()),
          texCoords(std::vector<glm::vec3>()),
          m_textures(std::vector<std::shared_ptr<Texture>>()),
          material(material) {
}

Mesh::Mesh(Material material, const std::string &path) : material(material),
                                                         vertices(std::vector<glm::vec3>()),
                                                         colors(std::vector<glm::vec3>()),
                                                         normals(std::vector<glm::vec3>()),
                                                         texCoords(std::vector<glm::vec3>()),
                                                         indices(std::vector<int>()),
                                                         m_textures(std::vector<std::shared_ptr<Texture>>()) {

    readFromFile(path);

    for (int i = 0; i < vertices.size(); ++i) {
        colors.emplace_back(1.f, 0.f, 0.f);
    }
    computeNormals();
}

void Mesh::draw() {

    int unit = 0;
    if (isTextured()) {
        for (auto &texture : m_textures) {
            glUniform1i(getIsTexturedLocation(), 1);
            glActiveTexture(GL_TEXTURE0 + unit);
            glBindTexture(GL_TEXTURE_2D, texture->getTextureBuffer());
            unit++;
        }
    } else {
        glUniform1i(getIsTexturedLocation(), 0);
    }

    if (isIndexed()) {
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBindVertexArray(vaoVertexArray);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
    } else {
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        glBindBuffer(GL_ARRAY_BUFFER, GL_ZERO);
    }


}

glm::mat4x4 Mesh::getModelMatrix() {
    return translateMatrix * rotateMatrix * scaleMatrix * getRotationX() * getRotationY() * getRotationZ();
}

GLuint Mesh::getMVPLocation() const {
    return uniformMvpPosition;
}

Material &Mesh::getMaterial() {
    return material;
}

bool Mesh::isIndexed() {
    return !indices.empty();
}

void Mesh::computeNormals() {

    this->normals = std::vector<glm::vec3>(vertices.size(), glm::vec3());

    for (int i = 0; i < indices.size(); i += 3) {
        auto i0 = indices[i];
        auto i1 = indices[i + 1];
        auto i2 = indices[i + 2];
        auto a = vertices[i0];
        auto b = vertices[i1];
        auto c = vertices[i2];

        auto ba = a - c;
        auto ca = a - b;

        auto normal = cross(ca, ba);
        normal = normalize(normal);

        normals[i0] = normal;
        normals[i1] = normal;
        normals[i2] = normal;
    }
}

void Mesh::readFromFile(const std::string &filepath) {
    std::cout << "........................................................................\n";
    std::cout << "Now Reading: " << filepath << std::endl;

    std::unique_ptr<std::istream> file_stream;
    std::vector<uint8_t> byte_buffer;
    std::vector<glm::vec3> verticesAll;

    try {
        // For most files < 1gb, pre-loading the entire file upfront and wrapping it into a
        // stream is a net win for parsing speed, about 40% faster.

        byte_buffer = read_file_binary(filepath);
        file_stream.reset(new memory_stream((char *) byte_buffer.data(), byte_buffer.size()));


        if (!file_stream || file_stream->fail()) throw std::runtime_error("file_stream failed to open " + filepath);

        file_stream->seekg(0, std::ios::end);
        const float size_mb = file_stream->tellg() * float(1e-6);
        file_stream->seekg(0, std::ios::beg);

        tinyply::PlyFile file;
        file.parse_header(*file_stream);

        std::cout << "\t[ply_header] Type: " << (file.is_binary_file() ? "binary" : "ascii") << std::endl;
        for (const auto &c : file.get_comments()) std::cout << "\t[ply_header] Comment: " << c << std::endl;
        for (const auto &c : file.get_info()) std::cout << "\t[ply_header] Info: " << c << std::endl;

        for (const auto &e : file.get_elements()) {
            std::cout << "\t[ply_header] element: " << e.name << " (" << e.size << ")" << std::endl;
            for (const auto &p : e.properties) {
                std::cout << "\t[ply_header] \tproperty: " << p.name << " (type="
                          << tinyply::PropertyTable[p.propertyType].str << ")";
                if (p.isList) std::cout << " (list_type=" << tinyply::PropertyTable[p.listType].str << ")";
                std::cout << std::endl;
            }
        }

        // Because most people have their own mesh types, tinyply treats parsed data as structured/typed byte buffers.
        // See examples below on how to marry your own application-specific data structures with this one.
        std::shared_ptr<tinyply::PlyData> vertices, normals, colors, texcoords, faces, tripstrip;

        // The header information can be used to programmatically extract properties on elements
        // known to exist in the header prior to reading the data. For brevity of this sample, properties
        // like vertex position are hard-coded:
        try { vertices = file.request_properties_from_element("vertex", {"x", "y", "z"}); }
        catch (const std::exception &e) { std::cerr << "tinyply exception: " << e.what() << std::endl; }

        try { normals = file.request_properties_from_element("vertex", {"nx", "ny", "nz"}); }
        catch (const std::exception &e) { std::cerr << "tinyply exception: " << e.what() << std::endl; }

        try { colors = file.request_properties_from_element("vertex", {"red", "green", "blue", "alpha"}); }
        catch (const std::exception &e) { std::cerr << "tinyply exception: " << e.what() << std::endl; }

        try { colors = file.request_properties_from_element("vertex", {"r", "g", "b", "a"}); }
        catch (const std::exception &e) { std::cerr << "tinyply exception: " << e.what() << std::endl; }

        try { texcoords = file.request_properties_from_element("vertex", {"u", "v"}); }
        catch (const std::exception &e) { std::cerr << "tinyply exception: " << e.what() << std::endl; }

        // Providing a list size hint (the last argument) is a 2x performance improvement. If you have
        // arbitrary ply files, it is best to leave this 0.
        try { faces = file.request_properties_from_element("face", {"vertex_indices"}, 0); }
        catch (const std::exception &e) { std::cerr << "tinyply exception: " << e.what() << std::endl; }

        // Tristrips must always be read with a 0 list size hint (unless you know exactly how many elements
        // are specifically in the file, which is unlikely);
        try { tripstrip = file.request_properties_from_element("tristrips", {"vertex_indices"}, 0); }
        catch (const std::exception &e) { std::cerr << "tinyply exception: " << e.what() << std::endl; }

        manual_timer read_timer;

        read_timer.start();
        file.read(*file_stream);
        read_timer.stop();

        const float parsing_time = static_cast<float>(read_timer.get()) / 1000.f;
        std::cout << "\tparsing " << size_mb << "mb in " << parsing_time << " seconds [" << (size_mb / parsing_time)
                  << " MBps]" << std::endl;

        if (vertices) std::cout << "\tRead " << vertices->count << " total vertices " << std::endl;
        if (normals) std::cout << "\tRead " << normals->count << " total vertex normals " << std::endl;
        if (colors) std::cout << "\tRead " << colors->count << " total vertex colors " << std::endl;
        if (texcoords) std::cout << "\tRead " << texcoords->count << " total vertex texcoords " << std::endl;
        if (faces) std::cout << "\tRead " << faces->count << " total faces (triangles) " << std::endl;
        if (tripstrip)
            std::cout << "\tRead " << (tripstrip->buffer.size_bytes() / tinyply::PropertyTable[tripstrip->t].stride)
                      << " total indicies (tristrip) " << std::endl;

        // Example One: converting to your own application types
        {
            const size_t numVerticesBytes = vertices->buffer.size_bytes();
            std::vector<float3> verts(vertices->count);
            std::memcpy(verts.data(), vertices->buffer.get(), numVerticesBytes);

            //Mesh plyMesh(verts);

            for (auto vert : verts) {
                glm::vec3 vertex(vert.x, vert.y, vert.z);
                this->vertices.push_back(vertex);
            }

            const size_t numIndicesBytes = faces->buffer.size_bytes();
            std::vector<int> facces(faces->count * 3);
            std::memcpy(facces.data(), faces->buffer.get(), numIndicesBytes);

            for (auto face : facces) {
                indices.push_back(face);
            }
        }
    }
    catch (const std::exception &e) {
        std::cerr << "Caught tinyply exception: " << e.what() << std::endl;
    }

}

GLuint Mesh::getMLocation() const {
    return uniformMPosition;
}

GLuint Mesh::getCameraLocation() const {
    return uniformCameraPosition;
}

glm::mat4x4 Mesh::getNormalModelMatrix() {
    auto m = getModelMatrix();
    return determinant(m) * transpose(inverse(m));
}

GLuint Mesh::getMNormalLocation() const {
    return uniformMNormalPosition;
}


void Mesh::setRotation(glm::vec3 axis, float value) {
    rotateMatrix = glm::rotate(glm::mat4(1.0), value, axis);
}

void Mesh::setTranslate(glm::vec3 translate) {
    translateMatrix = glm::translate(glm::mat4(1.0), translate);
}

void Mesh::setScale(glm::vec3 scale) {
    scaleMatrix = glm::scale(glm::mat4(1.0), scale);
}

glm::mat4 Mesh::getRotationX() {
    if (rotationX == 0) return glm::mat4(1.0);
    float time = glfwGetTime();
    return glm::rotate(glm::mat4(1.0), (float) time / rotationX, glm::vec3(1, 0, 0));
}

glm::mat4 Mesh::getRotationY() {
    if (rotationY == 0) return glm::mat4(1.0);
    float time = glfwGetTime();
    return glm::rotate(glm::mat4(1.0), (float) time / rotationY, glm::vec3(0, 1, 0));
}


glm::mat4 Mesh::getRotationZ() {
    if (rotationZ == 0) return glm::mat4(1.0);
    float time = glfwGetTime();
    return glm::rotate(glm::mat4(1.0), (float) time / rotationZ, glm::vec3(0, 0, 1));
}






