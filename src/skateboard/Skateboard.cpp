#include "Skateboard.h"
#include "../Cube/Cube.h"

Skateboard::Skateboard(int shaderProgram) {
    this->shaderProgram = shaderProgram;
}

void Skateboard::Draw(TranslateMatrix *translateMatrix, float x_position, float z_position) {
    Cube *wheelCube = new Cube(255.0f, 255.0f, 255.0f, RenderMode::triangles);

    const float boardWidth = 2.0f;
    const float boardLength = 4.0f;
    const float frontFaceZPosition = z_position + 1.0f;
    const float backFaceZPosition = z_position - 1.0f;

    //wheels
    float wheelSize = 0.25f;
    //wheel 1
    translateMatrix->setPosition(x_position, wheelSize, backFaceZPosition);
    translateMatrix->setSize(wheelSize, wheelSize, wheelSize);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    wheelCube->Draw();

    //wheel 2
    translateMatrix->setPosition(x_position, wheelSize, frontFaceZPosition);
    translateMatrix->setSize(wheelSize, wheelSize, wheelSize);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    wheelCube->Draw();

    //wheel 3
    translateMatrix->setPosition(x_position+boardLength, wheelSize, frontFaceZPosition);
    translateMatrix->setSize(wheelSize, wheelSize, wheelSize);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    wheelCube->Draw();

    //wheel 4
    translateMatrix->setPosition(x_position+boardLength, wheelSize, backFaceZPosition);
    translateMatrix->setSize(wheelSize, wheelSize, wheelSize);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    wheelCube->Draw();

    //board plank
    Cube *boardCube = new Cube(164,116,73, RenderMode::triangles);
    float plankWidth = boardWidth-0.5f;
    float plankLength = boardLength/2 + 2* wheelSize;
    float plankHeight = 0.1f;
    float plankYPosition = wheelSize + plankHeight + wheelSize;
    translateMatrix->setPosition(x_position+plankLength-2*wheelSize, plankYPosition, z_position);
    translateMatrix->setSize(plankLength, plankHeight, plankWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    boardCube->Draw();
}
