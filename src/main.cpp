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
#include "skateboard/Skateboard.h"
#include "characters/Characters.h"

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

    float charactersXPosition = -10.0f;
    float charactersZPosition = 0.0f;
    float olafScale = 1.0f;

    int selectedCharacterIndex = 0;

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
        (new Skateboard(shaderProgram))->Draw(translateMatrix, charactersXPosition, charactersZPosition);

        Skateboard *skateboard = new Skateboard(shaderProgram);
        skateboard->Draw(translateMatrix, charactersXPosition, charactersZPosition);

        (new Characters(shaderProgram, skateboard->height, selectedCharacterIndex))
                ->Draw(translateMatrix, -10.0f, charactersZPosition);
//        (new Olaf(shaderProgram))->Draw(
//                renderMode,
//                translateMatrix,
//                charactersXPosition,
//                charactersZPosition,
//                olafScale);

        handleViewInputs(window,
                         shaderProgram,
                         controller,
                         translateMatrix,
                         dt);
        handleActionInputs(
                window,
                &charactersXPosition,
                &charactersZPosition,
                &olafScale,
                &renderMode,
                &selectedCharacterIndex
        );
        glfwSwapBuffers(window);
        glfwWaitEvents();
    }

    glfwTerminate();

    return 0;
}
