
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
    renderer1.disableGLFeature(GL_CULL_FACE);
    glDepthFunc(GL_LESS);
    renderer1.enableGLFeature(GL_DEPTH_TEST);

    Shader vertexShader1("../src/shaders/vertex.glsl", true);
    Shader fragmentShader1("../src/shaders/flatFragment.glsl", false);

    Material material1(vertexShader1, fragmentShader1);

    Screen screen(material1);
    screen.push();

    Texture texture("../data/image/tree.png");
    texture.setup();
    screen.setTexture(texture);

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
//
//
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
////    Mesh plyMesh(material, "../data/ply/happy_vrip.ply");
////    plyMesh.push();
//
////    Texture texture( "../data/image/tree.png");
////    texture.setup();
////
////    Texture texture1( "../data/image/dirt.png");
////    texture.setup();
//
//    Cube cubus(material);
//    cubus.push();
//
////    cubus.setTexture(texture);
////    cubus.setTexture(texture1);
//
//    renderer.addMesh(cubus);
//    renderer.startRenderLoop();

}