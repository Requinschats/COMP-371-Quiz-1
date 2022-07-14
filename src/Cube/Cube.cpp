#include "Cube.h"
#include "glm/ext/matrix_transform.hpp"
#include <array>

using namespace glm;
using namespace std;

//utility function to get the color buffer data
static array<GLfloat, 36> getColorBufferData(float rgb1, float rgb2, float rgb3) {
    return {
            rgb1, rgb2, rgb3,
            rgb1, rgb2, rgb3,
            rgb1, rgb2, rgb3,
            rgb1, rgb2, rgb3,
            rgb1, rgb2, rgb3,
            rgb1, rgb2, rgb3,
            rgb1, rgb2, rgb3,
            rgb1, rgb2, rgb3,
            rgb1, rgb2, rgb3,
            rgb1, rgb2, rgb3,
            rgb1, rgb2, rgb3,
            rgb1, rgb2, rgb3
    };
}

//the cube vertices
GLfloat vertices[] = {
        // front
        -1.0, -1.0, 1.0,
        1.0, -1.0, 1.0,
        1.0, 1.0, 1.0,
        -1.0, 1.0, 1.0,
        // back
        -1.0, -1.0, -1.0,
        1.0, -1.0, -1.0,
        1.0, 1.0, -1.0,
        -1.0, 1.0, -1.0
};

//pointers to the cube vertices in order not to duplicate storage in the buffer
GLuint elements[] = {
        // front
        0, 1, 2,
        2, 3, 0,
        // right
        1, 5, 6,
        6, 2, 1,
        // back
        7, 6, 5,
        5, 4, 7,
        // left
        4, 0, 3,
        3, 7, 4,
        // bottom
        4, 5, 1,
        1, 0, 4,
        // top
        3, 2, 6,
        6, 7, 3
};

Cube::Cube(float rgb1, float rgb2, float rgb3, RenderMode renderMode) {
    this->renderMode_ = renderMode;

    //stores the cube vertices in a buffer
    GLuint VertexBufferObject;
    glGenVertexArrays(1, &this->cubeVAO_);
    glGenBuffers(1, &VertexBufferObject);

    glBindVertexArray(this->cubeVAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // dictates the cube vertices layout in the buffer: first three are for position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);

    // dictates the cube vertices layout in the buffer: last three are for color
    GLuint colorBuffer;
    //255 division to from regular rgb to rgba
    array<float, 36> colorBufferData = getColorBufferData(rgb1 / 255, rgb2 / 255, rgb3 / 255);
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colorBufferData), &colorBufferData, GL_STATIC_DRAW);

    //points to color
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

    //buffer for the element array that point to the cube vertices
    GLuint indexBufferObject;
    glGenBuffers(1, &indexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    glBindVertexArray(0);

}

Cube::~Cube() {}

void Cube::Draw() {
    glBindVertexArray(this->cubeVAO_);
    glLineWidth(4.0f);
    //renders elements here instead of vertices directly
    glDrawElements(getGLRenderMode(), 36, GL_UNSIGNED_INT, 0);
}

//utility function to select the openGL render mode based on the state
int Cube::getGLRenderMode() {
    switch (this->renderMode_) {
        case RenderMode::points:
            return GL_POINTS;
        case RenderMode::lines:
            return GL_LINES;
        case RenderMode::triangles:
            return GL_TRIANGLES;
    }
}
