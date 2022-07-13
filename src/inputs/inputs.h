#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "../Controller/Controller.h"
#include "../Cube/Cube.h"

void handleViewInputs(GLFWwindow *window,
                      int shaderProgram,
                      Controller *controller,
                      TranslateMatrix *translateMatrix,
                      float dt);

void handleViewKeyboardInputs(GLFWwindow *window,
                              int shaderProgram,
                              Controller *controller,
                              TranslateMatrix *translateMatrix,
                              float dt);

void handleViewMouseInputs(GLFWwindow *window, Controller *controller, TranslateMatrix *translateMatrix, float dt);

void handleActionInputs(
        GLFWwindow *window,
        float *olafXPosition,
        float *olafZPosition,
        float *olafScale,
        RenderMode *renderMode,
        int *selectedCharacterIndex
);