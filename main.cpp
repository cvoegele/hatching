
#include "src/commonincludes.h"
#include <glm/matrix.hpp>
#include <iostream>
#include "src/Shader.h"
#include "src/Material.h"
#include "src/Mesh.h"
#include "src/Renderer.h"
#include "src/Cube.h"
#include "src/Screen.h"

int main() {

    Renderer renderer1(640, 480);

    Camera camera1;
    renderer1.setCamera(camera1);
    renderer1.setup();

        GLint units = 0;
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &units);
    std::cout << units << std::endl;

    RenderPass renderPass(640, 480);

    ///Camera renderPassCamera;
    Camera camera(45.f,
                  renderPass.getAspectRatio(),
                  0.1f,
                  1000.f,
                  glm::vec3(0, 0, 0),
                  glm::vec3(0, 0, 0.5f));

    renderPass.setCamera(camera);
    renderPass.setup();

    Shader vertexShader("../src/shaders/vertex.glsl", true);
    Shader fragmentShader("../src/shaders/phong.glsl", false);

    Material material(vertexShader, fragmentShader);

    Mesh plyMesh(material, "../data/ply/bun_zipper.ply");
    plyMesh.push();
    plyMesh.setRotationX(0.7f);

//    Screen screen1(material);
//    screen1.push();

//    Cube cub0(material);
//    cub0.push();
//    cub0.setRotationX(0.7f);
//    cub0.setRotationY(0.8f);
//    cub0.setRotationZ(0.8f);
//
//    Texture texture("../data/image/dirt.png");
//    texture.setup();
//
//    Texture texture1("../data/image/tree.png");
//    texture1.setup();

//    cub0.setTexture(texture);
//    cub0.setTexture(texture1);

    renderPass.addMesh(plyMesh);

    renderer1.renderPass = std::make_shared<RenderPass>(renderPass);


    renderer1.disableGLFeature(GL_CULL_FACE);
    glDepthFunc(GL_LESS);
    renderer1.enableGLFeature(GL_DEPTH_TEST);

    Shader vertexShader1("../src/shaders/vertex.glsl", true);
    Shader fragmentShader1("../src/shaders/flatFragment.glsl", false);

    Material material1(vertexShader1, fragmentShader1);

    Screen screen(material1);
    screen.push();

//    Cube cube(material1);
//    cube.push();

    renderer1.addMesh(screen);
    renderer1.startRenderLoop();

//    Renderer renderer(640 * 2, 480 * 2);
//
//    Camera camera(45.f,
//                  renderer.getAspectRatio(),
//                  0.1f,
//                  1000.f,
//                  glm::vec3(0, 0, 0),
//                  glm::vec3(0, 2, 5.f));
//
//    renderer.setCamera(camera);
//
//    renderer.setup();
//    renderer.enableGLFeature(GL_CULL_FACE);
//    glDepthFunc(GL_LESS);
//    renderer.enableGLFeature(GL_DEPTH_TEST);
//    //renderer.disableGLFeature(GL_CULL_FACE);
//
//    Shader vertexShader("../src/shaders/vertex.glsl", true);
//    Shader fragmentShader("../src/shaders/phong.glsl", false);
//
//    Material material(vertexShader, fragmentShader);
//
//    Mesh plyMesh(material, "../data/ply/bun_zipper.ply");
//    plyMesh.push();
//
////    Texture texture( "../data/image/tree.png");
////    texture.setup();
////
////    Texture texture1( "../data/image/dirt.png");
////    texture.setup();
//
//    Cube cubus(material);
//    cubus.push();
//    cubus.setTranslate(glm::vec3(1,1,0));
//
////    cubus.setTexture(texture);
////    cubus.setTexture(texture1);
//
//    renderer.addMesh(plyMesh);
//    renderer.addMesh(cubus);
//
//    renderer.startRenderLoop();

}