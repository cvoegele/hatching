//
// Created by Christoph Vögele on 25/05/2021.
//

#ifndef HATCHING_UNIFORMVEC3_H
#define HATCHING_UNIFORMVEC3_H


#include <glm/vec3.hpp>
#include <string>
#include "UniformBase.h"

class UniformVec3 : public UniformBase {
public:
    UniformVec3(const std::string &name, const glm::vec3 &value, const float &min, const float &max);

    void upload(GLuint programId) override;

    void ImGui(int &counter) override;

private:
    glm::vec3 value;
   float min;
    float max;
};


#endif //HATCHING_UNIFORMVEC3_H
