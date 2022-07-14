#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

using namespace glm;

GLFWwindow *initializeWindow() {
    glfwInit();

    // Set all the required options for GLFW including versions and profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow(1024, 768, "Comp371 - Assignment 1", NULL, NULL);

    //error handling
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to create GLEW" << std::endl;
        glfwTerminate();
        return NULL;
    }

    return window;
}

//set the projection matrix to be used in the shader and bind it to the state machine
glm::mat4 setInitialProjectionMatrix(int shaderProgram) {
    // I took a 500 far to not loose the far en grid
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(90.0f),  // field of view in degrees
                                                  800.0f / 600.0f,      // aspect ratio
                                                  0.01f, 500.0f);       // near and far (near > 0)

    GLuint projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
    return projectionMatrix;
}