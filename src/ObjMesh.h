//
// Created by Christoph Vögele on 18/05/2021.
//

#ifndef HATCHING_OBJMESH_H
#define HATCHING_OBJMESH_H


#include "Mesh.h"

class ObjMesh : public Mesh {
public:
    ObjMesh(Material material, std::string path);
};


#endif //HATCHING_OBJMESH_H
