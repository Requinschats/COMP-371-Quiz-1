#include <iostream>

#define GLEW_STATIC 1

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "./initialization/initialization.h"
#include "Cube/Cube.h"
#include "Shaders/shaders.h"
#include "sources/generalShader/GeneralShader.h"
#include "ArrowAxis/ArrowAxis.h"
#include "Grid/Grid.h"
#include "inputs/inputs.h"
#include "WorldCube/WorldCube.h"
#include "skateboard/Skateboard.h"
#include "characters/Characters.h"

using namespace glm;

int main(int argc, char *argv[]) {

    //handles the creation of the window and the OpenGL context
    GLFWwindow *window = initializeWindow();

    // sets shaders used in all rendering
    int shaderProgram = compileAndLinkShaders(getVertexShaderSource(), getFragmentShaderSource());
    glUseProgram(shaderProgram);

    // enables depth testing
    glEnable(GL_DEPTH_TEST);

    //enables face culling. It allows to render only the front face of the triangles. This is changed for the skybox to render the back face.
    glEnable(GL_CULL_FACE);

    //creates the controller object that handles the camera position and rotation
    Controller *controller = new Controller(&shaderProgram);
    TranslateMatrix *translateMatrix = new TranslateMatrix(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
    RenderMode renderMode = RenderMode::triangles;

    float charactersXPosition = -10.0f;
    float charactersZPosition = -10.0f;
    float olafScale = 1.0f;

    int selectedCharacterIndex = 0;

    float lastFrameTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        controller->bindCameraPosition();

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

        handleViewInputs(window,
                         shaderProgram,
                         controller,
                         translateMatrix,
                         dt);
        handleActionInputs(
                window,
                translateMatrix,
                controller,
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
