#include <iostream>

#define GLEW_STATIC 1

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "./initialization/initialization.h"
#include "Cube/Cube.h"
#include "Shaders/shaders.h"
#include "sources/generalShader/GeneralShader.h"
#include "Olaf/Olaf.h"
#include "ArrowAxis/ArrowAxis.h"
#include "Grid/Grid.h"
#include "inputs/inputs.h"
#include "WorldCube/WorldCube.h"

using namespace glm;

int main(int argc, char *argv[]) {

    GLFWwindow *window = initializeWindow();

    int shaderProgram = compileAndLinkShaders(getVertexShaderSource(), getFragmentShaderSource());
    glUseProgram(shaderProgram);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    Controller *controller = new Controller(&shaderProgram);
    TranslateMatrix *translateMatrix = new TranslateMatrix(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
    RenderMode renderMode = RenderMode::triangles;

    float olafXPosition = 0.0f;
    float olafZPosition = 0.0f;
    float olafScale = 1.0f;

    float lastFrameTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        controller->setCameraPosition();
//        glClearColor(0.5, 0.5, 1, 1.0);

        float dt = glfwGetTime() - lastFrameTime;
        lastFrameTime += dt;


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        (new Grid(shaderProgram))->Draw(translateMatrix);
        (new ArrowAxis())->Draw(translateMatrix, shaderProgram);
        (new WorldCube(shaderProgram))->Draw(translateMatrix);
//        (new Olaf(shaderProgram))->Draw(
//                renderMode,
//                translateMatrix,
//                olafXPosition,
//                olafZPosition,
//                olafScale);

        handleViewInputs(window,
                         shaderProgram,
                         controller,
                         translateMatrix,
                         dt);
        handleActionInputs(
                window,
                &olafXPosition,
                &olafZPosition,
                &olafScale,
                &renderMode
        );
        glfwSwapBuffers(window);
        glfwWaitEvents();
    }

    glfwTerminate();

    return 0;
}
