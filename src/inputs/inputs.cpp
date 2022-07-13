#include "../Grid/Grid.h"
#include "glm/glm.hpp"
#include "inputs.h"

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
        float *olafXPosition,
        float *olafZPosition,
        float *olafScale,
        RenderMode *renderMode
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
}