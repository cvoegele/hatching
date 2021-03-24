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
#include "src/Renderer.h"

static void error_callback(int error, const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main() {

    Renderer renderer(640, 480);
    renderer.setup();
    renderer.enableGLFeature(GL_CULL_FACE);
    //renderer.disableGLFeature(GL_CULL_FACE);

    Shader vertexShader("../src/vertex.glsl",true);
    Shader fragmentShader("../src/fragment.glsl",false);

    Material material(vertexShader, fragmentShader);
    material.useProgram();

    Mesh mesh(material);

    mesh.push();

    renderer.addMesh(mesh);
    renderer.startRenderLoop();

}