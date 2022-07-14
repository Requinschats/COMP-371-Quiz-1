#include "../Grid/Grid.h"
#include "glm/glm.hpp"
#include "inputs.h"
#include <iostream>

using namespace glm;
float cameraSpeed = 5.0f;

void handleViewInputs(GLFWwindow *window,
                      int shaderProgram,
                      Controller *controller,
                      TranslateMatrix *translateMatrix,
                      float dt) {
    handleViewKeyboardInputs(window, shaderProgram, controller, translateMatrix, dt);
    handleViewMouseInputs(window, controller, translateMatrix, dt);
}

void handleViewKeyboardInputs(GLFWwindow *window,
                              int shaderProgram,
                              Controller *controller,
                              TranslateMatrix *translateMatrix,
                              float dt) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        glm::mat4 viewMatrix = glm::mat4(1.0f);

        GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        controller->cameraPosition.x -= cameraSpeed * dt;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        controller->cameraPosition.x += cameraSpeed * dt;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        controller->cameraPosition.z -= cameraSpeed * dt;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        controller->cameraPosition.z += cameraSpeed * dt;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        translateMatrix->setWorldRotationAngle(translateMatrix->worldRotationAngle + 5.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        translateMatrix->setWorldRotationAngle(translateMatrix->worldRotationAngle - 5.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
        translateMatrix->setObjectRotationAngle(translateMatrix->objectRotationAngle + 5.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
        translateMatrix->setObjectRotationAngle(translateMatrix->objectRotationAngle - 5.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS) {
        controller->reset();
        translateMatrix->resetDefault();
    }
}

void handleViewMouseInputs(GLFWwindow *window,
                           Controller *controller,
                           TranslateMatrix *translateMatrix,
                           float dt) {
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS && controller->lastMouseState != "right") {
        controller->handleMouseRightClick(window);
    }
    if (controller->lastMouseState == "right" && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
        controller->setCameraPositionFromMouse(window, dt);
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS && controller->lastMouseState != "middle") {
        controller->handleMouseMiddleClick(window);
    }
    if (controller->lastMouseState == "middle" &&
        glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_RELEASE) {
        controller->zoomOutFromMouse(window);
    }
}

void handleActionInputs(
        GLFWwindow *window,
        TranslateMatrix *translateMatrix,
        Controller *controller,
        float *olafXPosition,
        float *olafZPosition,
        float *olafScale,
        RenderMode *renderMode,
        int *selectedCharacterIndex
) {
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        *olafXPosition = Grid::getRandomGridCoordinate();
        *olafZPosition = Grid::getRandomGridCoordinate();
    }
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
        *olafScale += 0.1f;
    }
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
        *olafScale -= 0.1f;
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        *renderMode = RenderMode::points;
    }
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        *renderMode = RenderMode::lines;
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
        *renderMode = RenderMode::triangles;
    }
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
        translateMatrix->objectRotationAngle = 0.0f;
        *selectedCharacterIndex = 0;
        controller->reset();
    }
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        translateMatrix->objectRotationAngle = 0.0f;
        controller->cameraPosition = vec3(-10.0f, 20.0f, 20.0f);
        controller->cameraLookAt = vec3(0, -0.5f, -1.0f);
        controller->bindCameraPosition();
        translateMatrix->resetDefault();
        *selectedCharacterIndex = 1;
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        translateMatrix->objectRotationAngle = 0.0f;
        controller->cameraPosition = vec3(-3.0f, 10.0f, 20.0f);
        controller->bindCameraPosition();
        translateMatrix->resetDefault();
        *selectedCharacterIndex = 2;
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
        translateMatrix->objectRotationAngle = 0.0f;
        controller->cameraPosition = vec3(4.0f, 20.0f, 20.0f);
//        controller->cameraLookAt = vec3(0, -0.5f, -1.0f);
        controller->bindCameraPosition();
        translateMatrix->resetDefault();
        *selectedCharacterIndex = 3;
    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
        translateMatrix->objectRotationAngle = 0.0f;
        controller->cameraPosition = vec3(11.0f, 10.0f, 20.0f);
        controller->bindCameraPosition();
        translateMatrix->resetDefault();
        *selectedCharacterIndex = 4;
    }
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
        translateMatrix->objectRotationAngle = 0.0f;
        controller->cameraPosition = vec3(18.0f, 10.0f, 20.0f);
        controller->bindCameraPosition();
        translateMatrix->resetDefault();
        *selectedCharacterIndex = 5;
    }
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {
        translateMatrix->objectRotationAngle = 0.0f;
        controller->cameraPosition = vec3(25.0f, 10.0f, 20.0f);
        controller->bindCameraPosition();
        translateMatrix->resetDefault();
        *selectedCharacterIndex = 6;
    }
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS) {
        translateMatrix->objectRotationAngle = 0.0f;
        controller->cameraPosition = vec3(32.0f, 10.0f, 20.0f);
        controller->bindCameraPosition();
        translateMatrix->resetDefault();
        *selectedCharacterIndex = 7;
    }
    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS) {
        translateMatrix->objectRotationAngle = 0.0f;
        controller->cameraPosition = vec3(39.0f, 10.0f, 20.0f);
        controller->bindCameraPosition();
        translateMatrix->resetDefault();
        *selectedCharacterIndex = 8;
    }
}