#include <glad/gl.h>

#include <GLFW/glfw3.h>

#include <glm/matrix.hpp>
#include "src/Shader.h"
#include "src/Material.h"
#include "src/Mesh.h"
#include "src/Renderer.h"
#include "src/Util.h"

int main() {


    Renderer renderer(640, 480);

    Camera camera(45.f,
                  renderer.getAspectRatio(),
                  1.f,
                  1000.f,
                  glm::vec3(0, 0, 0),
                  glm::vec3(0, 0, -3));

    renderer.setCamera(camera);

    renderer.setup();
    renderer.enableGLFeature(GL_CULL_FACE);
    //renderer.disableGLFeature(GL_CULL_FACE);

    Shader vertexShader("../src/shaders/vertex.glsl", true);
    Shader fragmentShader("../src/shaders/fragment.glsl", false);

    Material material(vertexShader, fragmentShader);
    material.useProgram();
    Mesh mesh(material);

    //mesh.push();
    Mesh plyMesh(material, "../data/ply/bun_zipper.ply");
    plyMesh.push();

    renderer.addMesh(plyMesh);
    renderer.startRenderLoop();

}