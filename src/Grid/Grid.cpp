#include "Grid.h"
#include "random"

using namespace std;

// [0,2]: position, [3,5]: color
const GLfloat vertices[] = {
        0.5f, 0.0f, -0.5f, 0.75f, 1.0f, 0.5f, 1.0f,
        -0.5f, 0.0f, -0.5f, 0.75f, 1.0f, 0.5f, 1.0f,
        -0.5f, 0.0f, -0.5f, 0.75f, 1.0f, 0.5f, 1.0f,
        -0.5f, 0.0f, 0.5f, 0.75f, 1.0f, 0.5f, 1.0f,
        -0.5f, 0.0f, 0.5f, 0.75f, 1.0f, 0.5f, 1.0f,
        0.5f, 0.0f, 0.5f, 0.75f, 1.0f, 0.5f, 1.0f,
        0.5f, 0.0f, 0.5f, 0.75f, 1.0f, 0.5f, 1.0f,
        0.5f, 0.0f, -0.5f, 0.75f, 1.0f, 0.5f, 1.0f
};

Grid::Grid(int shaderProgram) {

    // Generate a buffer object to store the vertex data on the GPU
    this->shaderProgram = shaderProgram;
    GLuint VertexBufferObject;
    glGenVertexArrays(1, &this->gridVAO_);
    glGenBuffers(1, &VertexBufferObject);

    glBindVertexArray(this->gridVAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Dictates the layout of the vertex data
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *) 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *) (3 * sizeof(float)));

    glBindVertexArray(0);
}

void Grid::Draw(TranslateMatrix *translateMatrix) {
    for (int i = -50; i < 50; i++) { //rows
        for (int j = -50; j < 50; j++) { //columns
            translateMatrix->setPosition(i, 0.0f, j);
            //default size
            translateMatrix->setSize(1.0f, 1.0f, 1.0f);
            translateMatrix->bindTranslationMatrix(this->shaderProgram);

            glBindVertexArray(this->gridVAO_);
            glLineWidth(6.0f);

            // Draw what is stored in the buffer with lines
            glDrawArrays(GL_LINES, 0, 8);
            glBindVertexArray(0);
        }
    }
}

// utility function for generating random numbers, help from https://stackoverflow.com/questions/440144/how-do-i-create-a-random-alpha-numeric-string-in-c
int Grid::getRandomGridCoordinate() {
    random_device randomDevice;
    std::mt19937 gen(randomDevice());
    //[-50,50] matches the range of the grid, look at range in Draw()
    std::uniform_int_distribution<> distribution(-50, 50);
    return distribution(gen);
}

