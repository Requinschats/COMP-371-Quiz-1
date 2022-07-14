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
    // Translate Matrix is given to the objects' renderer and handles the translation and the rotation of the objects.
    TranslateMatrix *translateMatrix = new TranslateMatrix(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
    // Enum that handles the rendering mode of the objects.
    RenderMode renderMode = RenderMode::triangles;

    //default positions of the objects
    float charactersXPosition = -10.0f;
    float charactersZPosition = -10.0f;
    float olafScale = 1.0f; //a1 artefact

    //index that points to the active character
    int selectedCharacterIndex = 0;

    float lastFrameTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        controller->bindCameraPosition();

        //frame delta time calculation
        float dt = glfwGetTime() - lastFrameTime;
        lastFrameTime += dt;

        // clears opengl color and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // instantiation of the objects. The draw function to render on the screen.
        (new Grid(shaderProgram))->Draw(translateMatrix);
        //the axis
        (new ArrowAxis())->Draw(translateMatrix, shaderProgram);
        //the world cube
        (new WorldCube(shaderProgram))->Draw(translateMatrix);
        //the skateboards
        (new Skateboard(shaderProgram))->Draw(translateMatrix, charactersXPosition, charactersZPosition);

        Skateboard *skateboard = new Skateboard(shaderProgram);
        skateboard->Draw(translateMatrix, charactersXPosition, charactersZPosition);

        //the characters
        //Skateboard height is passed so that characters can sit on top of it
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
