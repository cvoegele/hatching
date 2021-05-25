//
// Created by Christoph Vögele on 21/05/2021.
//

#include "UniformI.h"

void UniformI::upload(GLuint programId) {
    auto location = glGetUniformLocation(programId, name.c_str());
    glUniform1i(location, value);
}

void UniformI::ImGui() {
    UniformBase::ImGui();
}

UniformI::UniformI(const std::string &name, GLuint value) : UniformBase(name), value(value) {}
