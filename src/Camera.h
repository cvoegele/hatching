//
// Created by Christoph Vögele on 24/03/2021.
//

#ifndef HATCHING_CAMERA_H
#define HATCHING_CAMERA_H

#include <glm/glm.hpp>

class Camera {
public:
    Camera(float FOV, float aspect, float zNear, float zFar, glm::vec3 lookAtPosition, glm::vec3 cameraPosition);
    Camera();

    glm::mat4 projectModelMatrix(glm::mat4 modelMatrix);

    glm::vec3 getCameraPosition();

private:
    float FOV;
    float aspect;
    float zNear;
    float zFar;
    glm::vec3 lookAtPosition;
    glm::vec3 cameraPosition;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    glm::mat4 viewProjectionMatrix;
};


#endif //HATCHING_CAMERA_H
