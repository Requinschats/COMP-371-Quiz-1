#include "GL/glew.h"
#include "ArrowAxis.h"

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
    GLuint VertexBufferObject;
    glGenVertexArrays(1, &this->axisVAO_);
    glGenBuffers(1, &VertexBufferObject);

    glBindVertexArray(this->axisVAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(axisVertices), axisVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *) 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *) (3 * sizeof(float)));

    glBindVertexArray(0);
}

void ArrowAxis::Draw() {
    glBindVertexArray(this->axisVAO_);
    glLineWidth(6.0f);
    glDrawArrays(GL_LINES, 0, 9 * 2);
    glBindVertexArray(0);
}