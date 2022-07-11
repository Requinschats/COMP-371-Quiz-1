#include "Controller.h"
#include "../initialization/initialization.h"
#include "glm/detail/type_mat4x4.hpp"
#include "glm/ext/matrix_transform.hpp"

const vec3 defaultCameraPosition = vec3(-5.6f, 10.0f, 10.0f);
const vec3 defaultCameraLookAt = vec3(0.5f, 0.0f, -1.0f);
const vec3 defaultCameraUp = vec3(0.0f, 1.0f, 0.0f);

Controller::Controller(int *shaderProgram) {
    this->shaderProgram = *shaderProgram;
    glm::mat4 initialProjectionMatrix = setInitialProjectionMatrix(this->shaderProgram);
    this->setCameraPosition(defaultCameraPosition, defaultCameraLookAt, defaultCameraUp);
}

void Controller::setCameraPosition(vec3 cameraPosition, vec3 cameraLookAt, vec3 cameraUp) {
    this->cameraPosition = cameraPosition;
    this->cameraLookAt = cameraLookAt;
    this->cameraUp = cameraUp;

    mat4 viewMatrix = lookAt(this->cameraPosition,
                             this->cameraPosition + this->cameraLookAt,  // center
                             this->cameraUp); // up
    GLuint viewMatrixLocation = glGetUniformLocation(this->shaderProgram, "viewMatrix");
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
}

void Controller::setCameraPosition() {
    mat4 viewMatrix = lookAt(this->cameraPosition,
                             this->cameraPosition + this->cameraLookAt,  // center
                             this->cameraUp); // up
    GLuint viewMatrixLocation = glGetUniformLocation(this->shaderProgram, "viewMatrix");
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
}

void Controller::reset() {
    this->cameraPosition = defaultCameraPosition;
    this->cameraLookAt = defaultCameraLookAt;
    this->cameraUp = defaultCameraUp;
    this->setCameraPosition(defaultCameraPosition, defaultCameraLookAt, defaultCameraUp);
}

glm::mat4 Controller::rotateYAxis(float degreeOfRotation) {
    return glm::rotate(glm::mat4(1.0f),
                       glm::radians(degreeOfRotation),
                       glm::vec3(0, 1, 0));
}