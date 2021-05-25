//
// Created by Christoph Vögele on 21/05/2021.
//

#include "UniformF.h"

void UniformF::ImGui() {
    UniformBase::ImGui();
}

UniformF::UniformF(const std::string &name, float value) : UniformBase(name), value(value) {}

void UniformF::upload(GLuint programId) {
    auto location = glGetUniformLocation(programId, name.c_str());
    glUniform1f(location, value);
}
