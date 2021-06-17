//
// Created by Christoph Vögele on 25/05/2021.
//

#include "UniformVec3.h"

UniformVec3::UniformVec3(const std::string &name, const glm::vec3 &value, const float &min, const float &max)
        : UniformBase(name), value(value), min(min), max(max) {}

void UniformVec3::upload(GLuint programId) {
    auto location = glGetUniformLocation(programId, name.c_str());
    glUniform3fv(location, 1, &value[0]);
}

void UniformVec3::ImGui(int &counter) {
    ImGui::SliderFloat3(Util::paramName(name, counter).c_str(), &value[0], min, max);
}
