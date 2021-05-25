//
// Created by Christoph Vögele on 21/05/2021.
//

#ifndef HATCHING_UNIFORMI_H
#define HATCHING_UNIFORMI_H


#include <string>
#include "UniformBase.h"

class UniformI : UniformBase {
public:
    UniformI(const std::string &name, int value, int min, int max);

    void upload(GLuint programId) override;

    void ImGui() override;

private:
    int value;
    int min;
    int max;
};


#endif //HATCHING_UNIFORMI_H
