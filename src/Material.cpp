//
// Created by Christoph Vögele on 16/03/2021.
//

#include <glad/gl.h>
#include "Material.h"

Material::Material(Shader &vertexShader, Shader &fragmentShader) : fragmentShader(fragmentShader) , vertexShader(vertexShader), program(0),  uniforms(std::vector<UniformBase*>()) {
}

void Material::createProgram() {
    program = glCreateProgram();
    glAttachShader(program, vertexShader.getShader());
    glAttachShader(program, fragmentShader.getShader());

}

void Material::useProgram() {
    glUseProgram(program);

    for (auto& uniform : uniforms) {
        uniform->upload(getProgram());
    }
}

GLuint Material::getProgram() const {
    return program;
}

void Material::reloadMaterial() {
    vertexShader.compile();
    fragmentShader.compile();
    glAttachShader(program, vertexShader.getShader());
    glAttachShader(program, fragmentShader.getShader());
    glLinkProgram(program);
}

Material::Material() : vertexShader(Shader(true)), fragmentShader(Shader(false)), program(0) {
    createProgram();
}

void Material::linkProgram() {
    glLinkProgram(program);
}

void Material::ImGui() {
    for (auto& uniform : uniforms) {

        uniform->ImGui();
    }
}


