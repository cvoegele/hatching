//
// Created by Christoph Vögele on 09/04/2021.
//

#ifndef HATCHING_RENDERPASS_H
#define HATCHING_RENDERPASS_H

#include "commonincludes.h"
#include "Mesh.h"
#include "Camera.h"

class RenderPass {
public:
    RenderPass(int width, int height, int textureLayout);

    void recompileShaders();

    void setup();

    void preRender();

    void render();

    void afterRender();

    void addMesh(const Mesh &mesh) { meshes.push_back(mesh); };

    void enableGLFeature(const int &attribute) { enabledGLFeatures.push_back(attribute); };

    void disableGLFeature(const int &attribute) {
        enabledGLFeatures.erase(std::remove(enabledGLFeatures.begin(), enabledGLFeatures.end(), attribute),
                                enabledGLFeatures.end());
    };

    float getAspectRatio() const { return (float) width / (float) height; };

    void setCamera(Camera &camera) { this->camera = camera; };

    GLuint getRenderTextureBuffer() { return renderTextureBuffer; };

    GLuint getRenderBuffer() { return renderBuffer; };

    GLuint getFrameBuffer() { return frameBuffer; };

private:
    int width;
    int height;
    GLuint renderTextureBuffer;
    GLuint renderBuffer;
    GLuint frameBuffer;
    int textureLayout;

    std::vector<Mesh> meshes;
    Camera camera;
    std::vector<int> enabledGLFeatures;
};


#endif //HATCHING_RENDERPASS_H
