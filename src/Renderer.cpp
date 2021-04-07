//
// Created by Christoph Vögele on 24/03/2021.
//

#include <glad/gl.h>
#include "glm/ext.hpp"
#include <iostream>
#include <imgui/imgui.h>
#include <imgui_glfw/imgui_impl_glfw.h>
#include <imgui_glfw/imgui_impl_opengl3.h>
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

bool show_demo_window = true;
bool show_another_window = false;

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

//    IMGUI_CHECKVERSION();
//    ImGui::CreateContext();
//    ImGuiIO &io = ImGui::GetIO();
//    // Setup Platform/Renderer bindings
//    ImGui_ImplGlfw_InitForOpenGL(window, true);
//    ImGui_ImplOpenGL3_Init("#version 400 core");
//    // Setup Dear ImGui style
//    ImGui::StyleColorsDark();
}

void Renderer::startRenderLoop() {
    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();
        glClearColor(1.f, 0.82f, .84f, 1.f);
        glViewport(0, 0, targetWidth, targetHeight);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//        ImGui_ImplOpenGL3_NewFrame();
//        ImGui_ImplGlfw_NewFrame();
//        ImGui::NewFrame();

        if (recompileShaders) {
            for (auto mesh : meshes) {
                mesh.getMaterial().reloadMaterial();
                mesh.push();
            }
            recompileShaders = false;

        }

        for (auto feature : enabledGLFeatures) {
            glEnable(feature);
        }

        for (auto mesh : meshes) {
            mesh.getMaterial().useProgram();

            auto meshModelMatrix = mesh.getModelMatrix();
            glUniformMatrix4fv(mesh.getMVPLocation(), 1, GL_FALSE,
                               &camera.projectModelMatrix(meshModelMatrix)[0][0]);
            glUniformMatrix4fv(mesh.getMLocation(), 1, GL_FALSE, &meshModelMatrix[0][0]);
            glUniformMatrix4fv(mesh.getMNormalLocation(), 1, GL_FALSE, &mesh.getNormalModelMatrix()[0][0]);
            glUniform3fv(mesh.getCameraLocation(), 1, &camera.getCameraPosition()[0]);

            mesh.draw();
        }

//        ImGui::Begin("Demo window");
//        ImGui::Button("Hello!");
//        ImGui::End();
//
//        ImGui::Render();
//        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

//        int display_w, display_h;
//        glfwGetFramebufferSize(window, &display_w, &display_h);
//        glViewport(0, 0, display_w, display_h);
        glfwSwapBuffers(window);

    }

//    ImGui_ImplOpenGL3_Shutdown();
//    ImGui_ImplGlfw_Shutdown();
//    ImGui::DestroyContext();

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



