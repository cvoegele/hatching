
#include "src/commonincludes.h"
#include <glm/matrix.hpp>
#include <iostream>
#include "src/Shader.h"
#include "src/Material.h"
#include "src/Mesh.h"
#include "src/Renderer.h"
#include "src/Cube.h"
#include "src/Screen.h"
#include "src/Sphere.h"
#include "src/ObjMesh.h"
#include "src/UniformI.h"
#include "src/UniformF.h"

int main() {

    Renderer renderer1(1020, 720);

    Camera camera1;
    renderer1.setCamera(camera1);
    renderer1.setup();

    RenderPass renderPassTexture(512, 512, 0);
    renderPassTexture.disableGLFeature(GL_DEPTH_TEST);

    Camera cameraNoProjection;

    renderPassTexture.setCamera(cameraNoProjection);
    renderPassTexture.setup();

    Shader flatVertex("../src/shaders/vertex.glsl", true);
    Shader brushFragment("../src/shaders/brushFragment.glsl", false);

    Material brushMaterial(flatVertex, brushFragment);

    Screen brushScreen(brushMaterial);
    brushScreen.push();

    Texture brushTexture("../data/image/Brush.png");
    brushTexture.setup();

    brushScreen.addTexture(brushTexture, 1);


    renderPassTexture.addMesh(brushScreen);

    renderer1.pushRenderPass(renderPassTexture);


    RenderPass renderPass(1020, 720, 2);
    renderPass.enableGLFeature(GL_DEPTH_TEST);
    renderPass.enableGLFeature(GL_CULL_FACE);
    renderPass.enableGLFeature(GL_BLEND);
    ///Camera renderPassCamera;
    Camera camera(45.f,
                  renderPass.getAspectRatio(),
                  0.1f,
                  1000.f,
                  glm::vec3(0, 0.1f, 0),
                  glm::vec3(0, 0.2f, 0.3f));

    renderPass.setCamera(camera);
    renderPass.setup();

    Shader vertexShader("../src/shaders/vertexScaledTextures.glsl", true);
    Shader fragmentShader("../src/shaders/hatching0.glsl", false);

    Material material(vertexShader, fragmentShader);

    UniformF base = UniformF("contrast",1);
    //UniformF* f = &base;

    material.addUniform(&base);

    ObjMesh mesh(material, "../data/obj/bunny_tex.obj");
    //Mesh mesh(material, "../data/ply/bun_zipper.ply");

//    mesh.push();
//    mesh.setRotationX(0.7f);

//    Screen screen1(material);
//    screen1.push();

//    Sphere mesh(material);
//    Cube mesh(material);
    mesh.push();
//    mesh.setRotationX(2.f);
    mesh.setRotationY(2.f);
//    mesh.setRotationZ(2.f);

    Texture texture("../data/image/tiled/layer0.png");
    texture.setup();

    Texture texture1("../data/image/tiled/layer1.png");
    texture1.setup();
//
    Texture texture2("../data/image/tiled/layer2.png");
    texture2.setup();

    Texture texture3("../data/image/tiled/layer3.png");
    texture3.setup();

    Texture texture4("../data/image/tiled/layer4.png");
    texture4.setup();

    mesh.addTexture(texture, 3);
    mesh.addTexture(texture1, 4);
    mesh.addTexture(texture2, 5);
    mesh.addTexture(texture3, 6);
    mesh.addTexture(texture4, 7);

    renderPass.addMesh(mesh);

    renderer1.pushRenderPass(renderPass);


    renderer1.disableGLFeature(GL_CULL_FACE);
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
//    Mesh mesh(material, "../data/ply/bun_zipper.ply");
//    mesh.push();
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
////    cubus.addTexture(texture);
////    cubus.addTexture(texture1);
//
//    renderer.addMesh(mesh);
//    renderer.addMesh(cubus);
//
//    renderer.startRenderLoop();

}