//
// Created by Christoph Vögele on 18/05/2021.
//

#include <OBJ_Loader.h>
#include "ObjMesh.h"


ObjMesh::ObjMesh(Material material, std::string path) : Mesh(material) {
    objl::Loader loader;
    loader.LoadFile(path);

    for (auto vertex: loader.LoadedVertices) {

        glm::vec3 pos = glm::vec3(vertex.Position.X, vertex.Position.Y, vertex.Position.Z);
        glm::vec3 textureCoordinate = glm::vec3(vertex.TextureCoordinate.X, vertex.TextureCoordinate.Y, 0.f);
        glm::vec3 normal = glm::vec3(vertex.Normal.X, vertex.Normal.Y, vertex.Normal.Z);

        vertices.push_back(pos);
        texCoords.push_back(textureCoordinate);
        normals.push_back(normal);

    }

    for (auto index : loader.LoadedIndices) {
        indices.push_back(index);
    }

}
