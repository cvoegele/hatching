//
// Created by Christoph Vögele on 21/05/2021.
//

#ifndef HATCHING_UNIFORMF_H
#define HATCHING_UNIFORMF_H


#include <string>
#include "UniformBase.h"

class UniformF : public UniformBase {
public:
    UniformF(const std::string &name, float value, float min, float max);

    virtual void upload(GLuint programId) override;

    virtual void ImGui(int &counter) override;

private:
    float value;
    float min;
    float max;
};

#endif //HATCHING_UNIFORMF_H
