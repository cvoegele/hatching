//
// Created by Christoph Vögele on 16/03/2021.
//

#include <glad/gl.h>
#include "Shader.h"
#include "util.h"

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

Shader::Shader(std::string path, bool vertex) : shader(0)  {
    std::string s = Util::readFile2(path);
    source = s.c_str();
    type = vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;
    compile();
}

void Shader::compile() {
    shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
}

Shader::Shader(bool vertex) {
    type = vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;
    source = vertex ? vertex_shader_text : fragment_shader_text;
    compile();
}

GLuint Shader::getShader() const {
    return shader;
}
