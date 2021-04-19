//
// Created by Christoph Vögele on 09/04/2021.
//

#include "RenderPass.h"


RenderPass::RenderPass(int width, int height) : width(width), height(height), meshes(std::vector<Mesh>()),
                                                enabledGLFeatures(std::vector<int>()) {

}

void RenderPass::setup() {
    glGenTextures(1, &renderTextureBuffer);
    glBindTexture(GL_TEXTURE_2D, renderTextureBuffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    glGenRenderbuffers(1, &renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);

    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderTextureBuffer, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);
    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
}

void RenderPass::preRender() {
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
}

void RenderPass::render() {

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.f, 0, 0, 1.f);

    for (auto &feature : enabledGLFeatures) {
        glEnable(feature);
    }

    for (auto &mesh : meshes) {
        mesh.getMaterial().useProgram();

        auto meshModelMatrix = mesh.getModelMatrix();
        glUniformMatrix4fv(mesh.getMVPLocation(), 1, GL_FALSE,
                           &camera.projectModelMatrix(meshModelMatrix)[0][0]);
        glUniformMatrix4fv(mesh.getMLocation(), 1, GL_FALSE, &meshModelMatrix[0][0]);
        glUniformMatrix4fv(mesh.getMNormalLocation(), 1, GL_FALSE, &mesh.getNormalModelMatrix()[0][0]);
        glUniform3fv(mesh.getCameraLocation(), 1, &camera.getCameraPosition()[0]);
        glUniform1f(mesh.getHeightLocation(), height);
        glUniform1f(mesh.getWidthLocation(), width);

        mesh.draw();
    }
}

void RenderPass::afterRender() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, renderTextureBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderPass::recompileShaders() {
    for (auto& mesh : meshes) {
        mesh.getMaterial().reloadMaterial();
        mesh.push();
    }
}





