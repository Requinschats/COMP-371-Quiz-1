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

    // sets shaders used in all rendering and returns them as a shader program
    int shaderProgram = compileAndLinkShaders(getVertexShaderSource(), getFragmentShaderSource());
    //bind the program to the state machine
    glUseProgram(shaderProgram);

    // enables depth testing
    // from the doc: OpenGL tests the depth value of a fragment against the content of the depth buffer. OpenGL performs a depth test and if this test passes, the fragment is rendered and the depth buffer is updated with the new depth value. If the depth test fails, the fragment is discarded.
    glEnable(GL_DEPTH_TEST);

    //enables face culling. It allows to render only the front face of the triangles. This is changed for the skybox to render the back face.
    glEnable(GL_CULL_FACE);

    //creates the controller object that handles the camera position and rotation. It allows centralizing the state of the view.
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
        //swaps the buffers. Double buffering. The back buffer is the one that is visible.
        glfwSwapBuffers(window);

        //polls for events. If the window is closed, the loop is broken. Otherwise, I had performance issues.
        glfwWaitEvents();
    }

    //terminates the window and frees the memory allocated for it.
    glfwTerminate();

    return 0;
}
