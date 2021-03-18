//
// Created by Christoph Vögele on 16/03/2021.
//

#ifndef TEST_PROGRAM_H
#define TEST_PROGRAM_H


#include "Shader.h"

class Program {
public:
    Program(Shader &vertexShader, Shader &fragmentShader);
    void createProgram();
    void useProgram() const;
    GLuint getProgram() const;


private:
    Shader vertexShader;
    Shader fragmentShader;
    GLuint program;
};


#endif //TEST_PROGRAM_H
