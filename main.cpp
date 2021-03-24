#include <glad/gl.h>

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>


#include <cstdlib>
#include <cstdio>
#include <glm/matrix.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include "src/Shader.h"
#include "src/Material.h"
#include "src/Mesh.h"

static const struct {
    float x, y;
    float r, g, b;
} vertices[3] =
        {
                {-0.6f, -0.4f, 1.f, 0.f, 0.f},
                {0.6f,  -0.4f, 0.f, 1.f, 0.f},
                {0.f,   0.6f,  0.f, 0.f, 1.f}
        };

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

static void error_callback(int error, const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main() {
    GLFWwindow *window;
    GLuint vertex_buffer, vertex_shader, fragment_shader, program;
    GLint mvp_location, vpos_location, vcol_location;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(640, 480, "OpenGL Interface 9000", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);

    // NOTE: OpenGL error checks have been omitted for brevity

//    glGenBuffers(1, &vertex_buffer);
//    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    Shader vertexShader("../src/vertex.glsl",true);
    Shader fragmentShader("../src/fragment.glsl",false);

    Material program1(vertexShader, fragmentShader);
    program1.useProgram();

    program = program1.getProgram();

    Mesh mesh(program1);

    mesh.push();

    glEnable(GL_CULL_FACE);
    //glEnable(GL_DEPTH_TEST);

//    mvp_location = glGetUniformLocation(program, "MVP");
//    vpos_location = glGetAttribLocation(program, "vPos");
//    vcol_location = glGetAttribLocation(program, "vCol");
//
//    glEnableVertexAttribArray(vpos_location);
//    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
//                          sizeof(vertices[0]), (void *) 0);
//    glEnableVertexAttribArray(vcol_location);
//    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
//                          sizeof(vertices[0]), (void *) (sizeof(float) * 2));

    while (!glfwWindowShouldClose(window)) {
        float ratio;
        int width, height;
        glm::mat4x4 m, p, mvp;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);


        mesh.draw();

//        m = glm::mat4(1.0);
//        glm::rotate(m, (float) glfwGetTime(), glm::vec3(0.f, 0.f, 1.f));
//        p = glm::ortho(-1.f, 1.f, 1.f, -1.f);
//
//        mvp = p * m;
//
//        glUseProgram(program);
//        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, &mvp[0][0]);
//        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}