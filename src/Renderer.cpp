//
// Created by Christoph Vögele on 24/03/2021.
//

#include <glad/gl.h>
#include "Renderer.h"

static void error_callback(int error, const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}


Renderer::Renderer(int targetWidth, int targetHeight) :
        meshes(std::vector<Mesh>()),
        window(nullptr),
        targetHeight(targetHeight),
        targetWidth(targetWidth),
        enabledGLFeatures(std::vector<int>()) {
}

void Renderer::setup() {
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(targetWidth, targetHeight, "OpenGL Interface 9000", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);
}

void Renderer::startRenderLoop() {
    while (!glfwWindowShouldClose(window)) {
        float ratio;
        int width, height;
        glm::mat4x4 m, p, mvp;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        for (auto feature : enabledGLFeatures) {
            glEnable(feature);
        }

        for (auto mesh : meshes) {
            mesh.draw();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void Renderer::addMesh(const Mesh &mesh) {
    meshes.push_back(mesh);
}

void Renderer::enableGLFeature(const int &attribute) {
    enabledGLFeatures.push_back(attribute);
}

void Renderer::disableGLFeature(const int &attribute) {
    enabledGLFeatures.erase(std::remove(enabledGLFeatures.begin(), enabledGLFeatures.end(), attribute),
                            enabledGLFeatures.end());
}



