//
// Created by Christoph Vögele on 21/05/2021.
//

#ifndef HATCHING_UNIFORMI_H
#define HATCHING_UNIFORMI_H


#include <string>
#include "UniformBase.h"

class UniformI : UniformBase {
public:
    UniformI(const std::string &name, GLuint value);

    void upload(GLuint programId) override;

    void ImGui() override;

private:
    GLuint value;
};


#endif //HATCHING_UNIFORMI_H
