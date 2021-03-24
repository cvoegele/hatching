//
// Created by Christoph Vögele on 16/03/2021.
//

#include <glad/gl.h>
#include "Material.h"

Material::Material(Shader &vertexShader, Shader &fragmentShader) : fragmentShader(fragmentShader) , vertexShader(vertexShader), program(0) {
    createProgram();
}

void Material::createProgram() {
    program = glCreateProgram();
    glAttachShader(program, vertexShader.getShader());
    glAttachShader(program, fragmentShader.getShader());
    glLinkProgram(program);
}

void Material::useProgram() const {
    glUseProgram(program);
}

GLuint Material::getProgram() const {
    return program;
}

