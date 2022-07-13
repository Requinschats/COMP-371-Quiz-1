#include "Characters.h"
#include "../Cube/Cube.h"

Characters::Characters(int shaderProgram) {
    this->shaderProgram = shaderProgram;
    this->letterHeight = 4.0f;
    this->letterWidth = 2.0f;
    this->letterSpacing = 3.0f;
    this->lineWidth = 0.5f;
    this->letterIndex=0;
}

float Characters::getLetterXPosition(float x_position) {
    return x_position + (letterWidth + letterSpacing) * letterIndex;
}

void Characters::Draw(TranslateMatrix *translateMatrix, float x_position, float z_position) {
    this->DrawF(translateMatrix, getLetterXPosition(x_position), z_position);
    this->DrawR(translateMatrix, getLetterXPosition(x_position), z_position);
    this->DrawA(translateMatrix, getLetterXPosition(x_position), z_position);
    this->DrawD(translateMatrix, getLetterXPosition(x_position), z_position);
    this->DrawE(translateMatrix, getLetterXPosition(x_position), z_position);
    this->DrawT(translateMatrix, getLetterXPosition(x_position), z_position);
    this->DrawT(translateMatrix, getLetterXPosition(x_position), z_position);
    this->DrawE(translateMatrix, getLetterXPosition(x_position), z_position);
}

void Characters::DrawF(TranslateMatrix *translateMatrix, float x_position, float z_position) {
    Cube *cube = new Cube(255.0f, 255.0f, 255.0f, RenderMode::triangles);
    translateMatrix->setPosition(x_position, this->letterHeight, z_position);
    translateMatrix->setSize(this->lineWidth, this->letterHeight, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    translateMatrix->setPosition(x_position+letterWidth-lineWidth, this->letterHeight+1, z_position);
    translateMatrix->setSize(letterWidth, this->lineWidth, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    translateMatrix->setPosition(x_position+letterWidth-lineWidth, this->letterHeight + 3.5f, z_position);
    translateMatrix->setSize(letterWidth, this->lineWidth, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    this->letterIndex++;
}

void Characters::DrawR(TranslateMatrix *translateMatrix, float x_position, float z_position) {
    Cube *cube = new Cube(255.0f, 255.0f, 255.0f, RenderMode::triangles);
    translateMatrix->setPosition(x_position, this->letterHeight, z_position);
    translateMatrix->setSize(this->lineWidth, this->letterHeight, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    translateMatrix->setPosition(x_position + letterWidth + lineWidth*2, this->letterHeight, z_position);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    translateMatrix->setPosition(x_position+letterWidth-lineWidth, this->letterHeight+1, z_position);
    translateMatrix->setSize(letterWidth, this->lineWidth, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    translateMatrix->setPosition(x_position+letterWidth-lineWidth, this->letterHeight + 3.5f, z_position);
    translateMatrix->setSize(letterWidth -this->lineWidth, this->lineWidth, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    this->letterIndex++;
}

void Characters::DrawA(TranslateMatrix *translateMatrix, float x_position, float z_position) {
    Cube *cube = new Cube(255.0f, 255.0f, 255.0f, RenderMode::triangles);
    translateMatrix->setPosition(x_position, this->letterHeight, z_position);
    translateMatrix->setSize(this->lineWidth, this->letterHeight, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    translateMatrix->setPosition(x_position + letterWidth + lineWidth*2, this->letterHeight, z_position);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    translateMatrix->setPosition(x_position+letterWidth-lineWidth, this->letterHeight+1, z_position);
    translateMatrix->setSize(letterWidth, this->lineWidth, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    translateMatrix->setPosition(x_position+letterWidth-lineWidth, this->letterHeight + 3.5f, z_position);
    translateMatrix->setSize(letterWidth -this->lineWidth, this->lineWidth, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    this->letterIndex++;
}

void Characters::DrawD(TranslateMatrix *translateMatrix, float x_position, float z_position) {
    Cube *cube = new Cube(255.0f, 255.0f, 255.0f, RenderMode::triangles);
    translateMatrix->setPosition(x_position, this->letterHeight, z_position);
    translateMatrix->setSize(this->lineWidth, this->letterHeight, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    translateMatrix->setPosition(x_position+letterWidth + 2*lineWidth, this->letterHeight, z_position);
    translateMatrix->setSize(this->lineWidth, this->letterHeight, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    translateMatrix->setPosition(x_position+letterWidth-lineWidth, this->letterHeight + 3.5f, z_position);
    translateMatrix->setSize(letterWidth, this->lineWidth, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    translateMatrix->setPosition(x_position+letterWidth-lineWidth, lineWidth, z_position);
    translateMatrix->setSize(letterWidth, this->lineWidth, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();


    this->letterIndex++;
}

void Characters::DrawE(TranslateMatrix *translateMatrix, float x_position, float z_position) {
    Cube *cube = new Cube(255.0f, 255.0f, 255.0f, RenderMode::triangles);
    translateMatrix->setPosition(x_position, this->letterHeight, z_position);
    translateMatrix->setSize(this->lineWidth, this->letterHeight, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    translateMatrix->setPosition(x_position+letterWidth-lineWidth, this->letterHeight + 3.5f, z_position);
    translateMatrix->setSize(letterWidth, this->lineWidth, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    translateMatrix->setPosition(x_position+letterWidth-lineWidth, this->letterHeight/2+2.5, z_position);
    translateMatrix->setSize(letterWidth, this->lineWidth, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    translateMatrix->setPosition(x_position+letterWidth-lineWidth, lineWidth, z_position);
    translateMatrix->setSize(letterWidth, this->lineWidth, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    this->letterIndex++;
}

void Characters::DrawT(TranslateMatrix *translateMatrix, float x_position, float z_position) {
    Cube *cube = new Cube(255.0f, 255.0f, 255.0f, RenderMode::triangles);
    translateMatrix->setPosition(x_position + letterWidth/2 + lineWidth, this->letterHeight, z_position);
    translateMatrix->setSize(this->lineWidth, this->letterHeight, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    translateMatrix->setPosition(x_position+letterWidth-lineWidth, this->letterHeight + 3.5f, z_position);
    translateMatrix->setSize(letterWidth, this->lineWidth, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    this->letterIndex++;
}
