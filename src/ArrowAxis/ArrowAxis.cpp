#include "GL/glew.h"
#include "ArrowAxis.h"
#include "../initialization/initialization.h"

const GLfloat axisVertices[] = {
        0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, //position, color
        5.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        5.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, //arrow
        4.5f, 0.0f, 0.2f, 1.0f, 0.0f, 0.0f, 1.0f,
        5.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        4.5f, 0.0f, -0.2f, 1.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, //line
        0.0f, 5.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 5.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, //arrow
        0.2f, 4.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 5.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.2f, 4.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, //line
        0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 1.0f, 1.0f, //arrow
        0.2f, 0.0f, 4.5f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.2f, 0.0f, 4.5f, 0.0f, 0.0f, 1.0f, 1.0f,
};

ArrowAxis::ArrowAxis() {
    // Stores the vertices in a buffer
    GLuint VertexBufferObject;
    glGenVertexArrays(1, &this->arrowAxisVAO_);
    glGenBuffers(1, &VertexBufferObject);

    glBindVertexArray(this->arrowAxisVAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(axisVertices), axisVertices, GL_STATIC_DRAW);

    //dictates the layout of the data in the buffer
    //position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *) 0);

    //color
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *) (3 * sizeof(float)));

    glBindVertexArray(0);
}

void ArrowAxis::Draw(TranslateMatrix *translateMatrix, GLuint shaderProgram) {
    //sets transformation matrix to default and binds it to the state machine
    translateMatrix->setDefaultPosition();
    translateMatrix->setDefaultSize();
    translateMatrix->bindTranslationMatrix(shaderProgram);
    glBindVertexArray(this->arrowAxisVAO_);

    //draws the axis with lines
    glDrawArrays(GL_LINES, 0, 18);
    glBindVertexArray(0);
}