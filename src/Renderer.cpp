//
// Created by Christoph Vögele on 24/03/2021.
//

#include <glad/gl.h>
#include <iostream>
#include "Renderer.h"

static void error_callback(int error, const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

bool recompileShaders;

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        std::cout << "activated shader reload" << std::endl;
        recompileShaders = true;
    }
}


Renderer::Renderer(int targetWidth, int targetHeight) :
        meshes(std::vector<Mesh>()),
        window(nullptr),
        targetHeight(targetHeight),
        targetWidth(targetWidth),
        enabledGLFeatures(std::vector<int>()), camera(Camera()) {
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

        if (recompileShaders) {
            for (auto mesh : meshes) {
                mesh.getMaterial().reloadMaterial();
                mesh.push();
            }
            recompileShaders = false;

        }


        glViewport(0, 0, targetWidth, targetHeight);
        glClear(GL_COLOR_BUFFER_BIT);

        for (auto feature : enabledGLFeatures) {
            glEnable(feature);
        }

        for (auto mesh : meshes) {
            glUniformMatrix4fv(mesh.getMVPLocation(), 1, GL_FALSE,
                               &camera.projectModelMatrix(mesh.getModelMatrix())[0][0]);
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

float Renderer::getAspectRatio() const {
    return (float) targetWidth / (float) targetHeight;
}

void Renderer::setCamera(Camera &camera) {
    this->camera = camera;
}



