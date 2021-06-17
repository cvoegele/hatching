//
// Created by Christoph Vögele on 21/05/2021.
//

#ifndef HATCHING_UNIFORMBASE_H
#define HATCHING_UNIFORMBASE_H


#include "commonincludes.h"
#include "Util.h"

class UniformBase {
public:
    UniformBase(std::string name) : name(name) {
    }

    virtual void upload(GLuint programId) {

    };

    virtual void ImGui(int &counter) {

    };
protected:
    std::string name;
};

#endif //HATCHING_UNIFORMBASE_H
