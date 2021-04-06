//
// Created by Christoph Vögele on 24/03/2021.
//

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtx/dual_quaternion.hpp>
#include "Camera.h"

Camera::Camera(float FOV, float aspect, float zNear, float zFar, glm::vec3 lookAtPosition, glm::vec3 cameraPosition)
        : FOV(FOV), aspect(aspect), zNear(zNear), zFar(zFar), lookAtPosition(lookAtPosition),
          cameraPosition(cameraPosition), viewMatrix(glm::mat4()), projectionMatrix(glm::mat4()),
          viewProjectionMatrix(glm::mat4()) {

    viewMatrix = glm::lookAt(cameraPosition, lookAtPosition, glm::vec3(0.f, 1.f, 0.f));
    projectionMatrix = glm::perspective(FOV, aspect, zNear, zFar);
    viewProjectionMatrix = projectionMatrix * viewMatrix;
}

glm::mat4 Camera::projectModelMatrix(glm::mat4 modelMatrix) {
    return viewProjectionMatrix * modelMatrix;
}

Camera::Camera() : FOV(0), aspect(0), zNear(0), zFar(0), lookAtPosition(0),
                   cameraPosition(0), viewMatrix(glm::mat4(1.0)), projectionMatrix(glm::mat4(1.0)),
                   viewProjectionMatrix(glm::mat4(1.0)) {
}

glm::vec3 Camera::getCameraPosition() {
    return (inverse(viewMatrix) * glm::vec4(0,0,0,1));
}
