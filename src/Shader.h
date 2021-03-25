//
// Created by Christoph Vögele on 16/03/2021.
//

#ifndef TEST_SHADER_H
#define TEST_SHADER_H


#include <string>
#include <GLFW/glfw3.h>

class Shader {
public:

    Shader(std::string path, bool vertex);
    Shader(bool vertex);
    void compile();
    GLuint getShader() const;

private:
    GLuint shader{};
    const char* source;
    int type;
    std::string path;
};


#endif //TEST_SHADER_H
