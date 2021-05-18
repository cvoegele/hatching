//
// Created by Christoph Vögele on 24/03/2021.
//

#ifndef TEST_RENDERER_H
#define TEST_RENDERER_H


#include <vector>
#include "Mesh.h"
#include "Camera.h"
#include "RenderPass.h"

class Renderer {
public:
    Renderer(int targetWidth, int targetHeight);

    void setup();

    void startRenderLoop();

    void addMesh(const Mesh &mesh);

    void enableGLFeature(const int& attribute);

    void disableGLFeature(const int& attribute);

    float getAspectRatio() const;

    void setCamera(Camera& camera);

    void pushRenderPass(RenderPass& renderPass1) {
        renderPasses.push_back(std::make_shared<RenderPass>(renderPass1));
    }

    void popRenderPass() {
        renderPasses.pop_back();
    }


private:
    std::vector<Mesh> meshes;
    Camera camera;
    GLFWwindow *window;
    int targetWidth;
    int targetHeight;
    std::vector<int> enabledGLFeatures;
    float* clear_color;
    std::vector<std::shared_ptr<RenderPass>> renderPasses;

};


#endif //TEST_RENDERER_H
