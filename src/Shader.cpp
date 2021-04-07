//
// Created by Christoph Vögele on 16/03/2021.
//

#include "commonincludes.h"
#include "Shader.h"
#include "Util.h"

static const char *vertex_shader_text =
        "#version 110\n"
        "uniform mat4 MVP;\n"
        "attribute vec3 vCol;\n"
        "attribute vec2 vPos;\n"
        "varying vec3 color;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
        "    color = vCol;\n"
        "}\n";

static const char *fragment_shader_text =
        "#version 110\n"
        "varying vec3 color;\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = vec4(color, 1.0);\n"
        "}\n";

Shader::Shader(std::string path, bool vertex) : shader(0) , path(path), source("") {
    type = vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;
    shader = glCreateShader(type);
    compile();
}

void Shader::compile() {
    std::string s = Util::readFile2(path);
    source = s.c_str();
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
}

Shader::Shader(bool vertex) {
    type = vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;
    source = vertex ? vertex_shader_text : fragment_shader_text;
    shader = glCreateShader(type);
    compile();
}

GLuint Shader::getShader() const {
    return shader;
}
