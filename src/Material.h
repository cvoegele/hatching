//
// Created by Christoph Vögele on 16/03/2021.
//

#ifndef TEST_MATERIAL_H
#define TEST_MATERIAL_H


#include <vector>
#include "Shader.h"
#include "UniformBase.h"

class Material {
public:
    Material(Shader &vertexShader, Shader &fragmentShader);
    Material();

    void createProgram();

    void linkProgram();

    void useProgram();

    GLuint getProgram() const;

    void reloadMaterial();

    void addUniform(UniformBase* uniformBase) { uniforms.push_back(uniformBase); }

    void ImGui();

private:
    Shader vertexShader;
    Shader fragmentShader;
    GLuint program;
    std::vector<UniformBase*> uniforms;
};


#endif //TEST_MATERIAL_H
