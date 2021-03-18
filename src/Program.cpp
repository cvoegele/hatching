//
// Created by Christoph Vögele on 16/03/2021.
//

#include <glad/gl.h>
#include "Program.h"

Program::Program(Shader &vertexShader, Shader &fragmentShader) : fragmentShader(fragmentShader) , vertexShader(vertexShader), program(0) {
    createProgram();
}

void Program::createProgram() {
    program = glCreateProgram();
    glAttachShader(program, vertexShader.getShader());
    glAttachShader(program, fragmentShader.getShader());
    glLinkProgram(program);
}

void Program::useProgram() const {
    glUseProgram(program);
}

GLuint Program::getProgram() const {
    return program;
}

