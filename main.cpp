
#include "src/commonincludes.h"
#include <glm/matrix.hpp>
#include <iostream>
#include "src/Shader.h"
#include "src/Material.h"
#include "src/Mesh.h"
#include "src/Renderer.h"
#include "src/Cube.h"

int main() {


    Renderer renderer(640 * 2, 480 * 2);

    Camera camera(45.f,
                  renderer.getAspectRatio(),
                  0.1f,
                  1000.f,
                  glm::vec3(0, 0, 0),
                  glm::vec3(0, 2, 2.f));

    std::cout << camera.getCameraPosition().z << std::endl;

    renderer.setCamera(camera);

    renderer.setup();
    renderer.enableGLFeature(GL_CULL_FACE);
    glDepthFunc(GL_LESS);
    renderer.enableGLFeature(GL_DEPTH_TEST);
    //renderer.disableGLFeature(GL_CULL_FACE);

    Shader vertexShader("../src/shaders/vertex.glsl", true);
    Shader fragmentShader("../src/shaders/phong.glsl", false);

    Material material(vertexShader, fragmentShader);

//    Mesh plyMesh(material, "../data/ply/happy_vrip.ply");
//    plyMesh.push();

    Texture texture(Image("../data/image/dirt.png"));
    texture.setup();

    Cube cubus(material);
    cubus.push();

    renderer.addMesh(cubus);
    renderer.startRenderLoop();

}