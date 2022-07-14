#include "Controller.h"
#include "../initialization/initialization.h"
#include "glm/detail/type_mat4x4.hpp"
#include "glm/ext/matrix_transform.hpp"

const vec3 defaultCameraPosition = vec3(5.6f, 10.0f, 20.0f);
const vec3 defaultCameraLookAt = vec3(0.5f, 0.0f, -1.0f);
const vec3 defaultCameraUp = vec3(0.0f, 1.0f, 0.0f);

// Constructor that sets the camera position, look at, up vectors and projection matrix to default values.
Controller::Controller(int *shaderProgram) {
    this->shaderProgram = *shaderProgram;
    this->lastMouseState = "";
    this->setCameraPosition(defaultCameraPosition, defaultCameraLookAt, defaultCameraUp);
    this->setDefaultLookAt();
    glm::mat4 initialProjectionMatrix = setInitialProjectionMatrix(this->shaderProgram);
}

// Wrapper that sets the camera position, look at, up vectors and projection matrix.
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

//binds the state of the controller to the screen.
void Controller::bindCameraPosition() {
    mat4 viewMatrix = lookAt(this->cameraPosition,
                             this->cameraPosition + this->cameraLookAt,  // center
                             this->cameraUp); // up
    GLuint viewMatrixLocation = glGetUniformLocation(this->shaderProgram, "viewMatrix");
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
}

// resets the camera position, look at, up vectors to default values.
void Controller::reset() {
    this->cameraPosition = defaultCameraPosition;
    this->setDefaultLookAt();
    this->cameraUp = defaultCameraUp;
    this->setCameraPosition(defaultCameraPosition, defaultCameraLookAt, defaultCameraUp);
}

glm::mat4 Controller::rotateYAxis(float degreeOfRotation) {
    return glm::rotate(glm::mat4(1.0f),
                       glm::radians(degreeOfRotation),
                       glm::vec3(0, 1, 0));
}

// sets mouse position to passed in values.
void Controller::setMousePosition(GLFWwindow *window) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    this->mousePosition.x = xpos;
    this->mousePosition.y = ypos;
}

//called when the mouse right button is pressed. Sets the state for the release of the button
void Controller::handleMouseRightClick(GLFWwindow *window) {
    this->setMousePosition(window);
    this->lastMouseState = "right";
}

//called when the mouse left button is pressed. Sets the state for the release of the button
void Controller::handleMouseMiddleClick(GLFWwindow *window) {
    this->setMousePosition(window);
    this->lastMouseState = "middle";
}

// keeps the horizontal angle between 0 and 360 degrees.
void Controller::normalizeCameraHorizontalAngle() {
    if (this->cameraHorizontalAngle > 360) {
        this->cameraHorizontalAngle -= 360;
    } else if (cameraHorizontalAngle < -360) {
        this->cameraHorizontalAngle += 360;
    }
}

// from lab 3, it converts camera horizontal angle to a rotation matrix.
void Controller::setDefaultLookAt() {
    // default values in degrees
    this->cameraHorizontalAngle = 90.0f;
    this->cameraVerticalAngle = 0.0f;

    this->cameraVerticalAngle = std::max(-85.0f, std::min(85.0f, this->cameraVerticalAngle));
    this->normalizeCameraHorizontalAngle();

    // convert to radians
    float theta = radians(this->cameraHorizontalAngle);
    float phi = radians(this->cameraVerticalAngle);

    //conversion to spherical coordinates
    this->cameraLookAt = vec3(cosf(phi) * cosf(theta), sinf(phi), -cosf(phi) * sinf(theta));
    vec3 cameraSideVector = glm::cross(this->cameraLookAt, vec3(0.0f, 1.0f, 0.0f));
    glm::normalize(cameraSideVector);

    //sets the controller state base on the new values.
    this->cameraPosition -= cameraSideVector * 1.0f;
    this->setCameraPosition(this->cameraPosition, this->cameraLookAt, this->cameraUp);
}

// similar to setDefaultLookAt, but uses the delta vector of the mouse to rotate the camera.
void Controller::setCameraPositionFromMouse(GLFWwindow *window, float dt) {
    double mousePosX, mousePosY;
    glfwGetCursorPos(window, &mousePosX, &mousePosY);

    // calculate the change in mouse position
    double dx = mousePosX - this->mousePosition.x;
    double dy = mousePosY - this->mousePosition.y;

    //rotation speed, I prefer a lower speed
    const float cameraAngularSpeed = 6.0f;

    this->cameraHorizontalAngle -= dx * cameraAngularSpeed * dt;
    this->cameraVerticalAngle -= dy * cameraAngularSpeed * dt;

    this->cameraVerticalAngle = std::max(-85.0f, std::min(85.0f, this->cameraVerticalAngle));
    this->normalizeCameraHorizontalAngle();

    float theta = radians(this->cameraHorizontalAngle);
    float phi = radians(this->cameraVerticalAngle);

    this->cameraLookAt = vec3(cosf(phi) * cosf(theta), sinf(phi), -cosf(phi) * sinf(theta));
    vec3 cameraSideVector = glm::cross(this->cameraLookAt, vec3(0.0f, 1.0f, 0.0f));
    glm::normalize(cameraSideVector);

    this->cameraPosition -= cameraSideVector * 1.0f * dt;

    this->setCameraPosition(this->cameraPosition, this->cameraLookAt, this->cameraUp);

    this->mousePosition.x = mousePosX;
    this->mousePosition.y = mousePosY;
    this->lastMouseState = "";
}

void Controller::zoomOutFromMouse(GLFWwindow *window) {
    double mousePosX, mousePosY;
    glfwGetCursorPos(window, &mousePosX, &mousePosY);
    double dy = (mousePosY - this->mousePosition.y) * 0.025f;
    this->cameraPosition = vec3(this->cameraPosition.x - dy,
                                this->cameraPosition.y + dy,
                                this->cameraPosition.z + dy);
    this->bindCameraPosition();
    this->mousePosition.x = mousePosX;
    this->mousePosition.y = mousePosY;
    this->lastMouseState = "";
}
