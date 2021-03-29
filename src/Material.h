//
// Created by Christoph Vögele on 16/03/2021.
//

#ifndef TEST_MATERIAL_H
#define TEST_MATERIAL_H


#include "Shader.h"

class Material {
public:
    Material(Shader &vertexShader, Shader &fragmentShader);
    Material();

    void createProgram();

    void useProgram() const;

    GLuint getProgram() const;

    void reloadMaterial();


private:
    Shader vertexShader;
    Shader fragmentShader;
    GLuint program;
};


#endif //TEST_MATERIAL_H
