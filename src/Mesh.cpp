//
// Created by Christoph Vögele on 21/03/2021.
//

#include <glad/gl.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <iostream>
#include <example-utils.hpp>
#include <tinyply.h>
#include "Mesh.h"
#include "Util.h"


void Mesh::push() {

    float *flatVertices = &vertices[0].x;
    float *flatColors = &colors[0].x;
    float *flatNormals = &normals[0].x;

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

    glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normals.size() * 3, flatNormals, GL_STATIC_DRAW);
    GLuint normalPosition = glGetAttribLocation(material.getProgram(), "vNor");
    glEnableVertexAttribArray(normalPosition);
    glVertexAttribPointer(normalPosition, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), indices.data(), GL_STATIC_DRAW);

    uniformMvpPosition = glGetUniformLocation(material.getProgram(), "MVP");
}

Mesh::Mesh(Material material)
        : vertices(std::vector<glm::vec3>()),
          colors(std::vector<glm::vec3>()),
          indices(std::vector<int>()),
          normals(std::vector<glm::vec3>()),
          material(material),
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

    for (int &vertexIndice : vertexIndices) {
        indices.push_back(vertexIndice);
    }

    computeNormals();

}

void Mesh::draw() {
    if (isIndexed()) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
    } else {
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    }

}

glm::mat4x4 Mesh::getModelMatrix() {
    double time = glfwGetTime();
    glm::mat4 s = glm::scale(glm::mat4(1.0), glm::vec3(3.f, 3.f, 3.f));
    glm::mat4 r = glm::rotate(glm::mat4(1.0), (float) time / 10.f, glm::vec3(1, -1, 1));
    return glm::mat4(1.0) * r * s;
}

GLuint Mesh::getMVPLocation() const {
    return uniformMvpPosition;
}

Material &Mesh::getMaterial() {
    return material;
}

Mesh::Mesh(Material material, const std::string &path) : material(material),
                                                         vertices(std::vector<glm::vec3>()),
                                                         colors(std::vector<glm::vec3>()),
                                                         normals(std::vector<glm::vec3>()),
                                                         indices(std::vector<int>()),
                                                         uniformMvpPosition(0),
                                                         indexBuffer(0),
                                                         vertexBuffer(0),
                                                         colorBuffer(0) {

    readFromFile(path);

    for (int i = 0; i < vertices.size(); ++i) {
        colors.emplace_back(1.f, 0.f, 0.f);
    }
    computeNormals();
}

bool Mesh::isIndexed() {
    return !indices.empty();
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

void Mesh::computeNormals() {

    this->normals = std::vector<glm::vec3>(vertices.size(),glm::vec3());

    for (int i = 0; i < indices.size(); i += 3) {
        auto i0 = indices[i];
        auto i1 = indices[i + 1];
        auto i2 = indices[i + 2];
        auto a = vertices[i0];
        auto b = vertices[i1];
        auto c = vertices[i2];

        auto ba = b - a;
        auto ca = c - a;

        auto normal = cross(ca, ba);
        normal = normalize(normal);

        normals[i0] = normal;
        normals[i1] = normal;
        normals[i2] = normal;
    }
}
