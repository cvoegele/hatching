//
// Created by Christoph Vögele on 21/05/2021.
//

#include "UniformF.h"


void UniformF::ImGui() {
    ImGui::SliderFloat(name.c_str(), &value, min,max);
}

void UniformF::upload(GLuint programId) {
    auto location = glGetUniformLocation(programId, name.c_str());
    glUniform1f(location, value);
}

UniformF::UniformF(const std::string &name, float value, float min, float max) : UniformBase(name), value(value) , min(min), max(max) {

}
