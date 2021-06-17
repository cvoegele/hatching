//
// Created by Christoph Vögele on 21/05/2021.
//

#include "UniformI.h"

void UniformI::upload(GLuint programId) {
    auto location = glGetUniformLocation(programId, name.c_str());
    glUniform1i(location, value);
}

void UniformI::ImGui(int &counter) {
    ImGui::SliderInt(Util::paramName(name, counter).c_str(), &value, min, max);
}

UniformI::UniformI(const std::string &name, int value, int min, int max) : UniformBase(name), value(value), min(min), max(max) {

}
