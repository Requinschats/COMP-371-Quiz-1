#include "Characters.h"
#include "../Cube/Cube.h"
#include "../skateboard/Skateboard.h"

Characters::Characters(int shaderProgram, float baseHeight) {
    this->shaderProgram = shaderProgram;
    this->letterHeight = 4.0f;
    this->letterWidth = 2.0f;
    this->letterSpacing = 4.0f;
    this->lineWidth = 0.5f;
    this->letterIndex=0;
    this->baseHeight = baseHeight;
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
    translateMatrix->setPosition(x_position, baseHeight + this->letterHeight, z_position);
    translateMatrix->setSize(this->lineWidth, this->letterHeight, this->lineWidth);
    translateMatrix->setObjectRotationAngle(220, vec3(2, 1, 0));
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    translateMatrix->setPosition(x_position+letterWidth-lineWidth, baseHeight + this->letterHeight+1, z_position);
    translateMatrix->setSize(letterWidth, this->lineWidth, this->lineWidth);
    translateMatrix->setObjectRotationAngle(220);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    translateMatrix->setPosition(x_position+letterWidth-lineWidth, baseHeight + this->letterHeight + 3.5f, z_position);
    translateMatrix->setSize(letterWidth, this->lineWidth, this->lineWidth);
    translateMatrix->setObjectRotationAngle(220);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    this->letterIndex++;
}

void Characters::DrawR(TranslateMatrix *translateMatrix, float x_position, float z_position) {
    Cube *cube = new Cube(255.0f, 255.0f, 255.0f, RenderMode::triangles);
    translateMatrix->setPosition(x_position, baseHeight + this->letterHeight, z_position);
    translateMatrix->setSize(this->lineWidth, this->letterHeight, this->lineWidth);
    translateMatrix->setObjectRotationAngle(220, vec3(2, 0, 0));
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //right top column
    translateMatrix->setPosition(x_position + letterWidth + lineWidth*2, baseHeight + this->letterHeight+ 2.75f, z_position);
    translateMatrix->setSize(this->lineWidth, this->letterHeight/2-0.75f, this->lineWidth);
    translateMatrix->setObjectRotationAngle(220, vec3(-1, 0, 0));
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //right bottom column
    translateMatrix->setPosition(x_position + letterWidth + lineWidth*2, baseHeight + this->letterHeight/2+0.25, z_position);
    translateMatrix->setSize(this->lineWidth, this->letterHeight/2 + 0.25, this->lineWidth);
    translateMatrix->setObjectRotationAngle(220,vec3(-1, 0, 0));
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //middle bar
    translateMatrix->setPosition(x_position+letterWidth-lineWidth, baseHeight + this->letterHeight+1, z_position);
    translateMatrix->setSize(letterWidth/2, this->lineWidth, this->lineWidth);
    translateMatrix->setObjectRotationAngle(220, vec3(0.5, 1, 0));
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //top bar
    translateMatrix->setPosition(x_position+letterWidth-lineWidth, baseHeight + this->letterHeight + 3.5f, z_position);
    translateMatrix->setSize(letterWidth -this->lineWidth, this->lineWidth, this->lineWidth);
    translateMatrix->setObjectRotationAngle(220, vec3(0.5, 1, 0));
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    (new Skateboard(shaderProgram))->Draw(translateMatrix, x_position, z_position);

    this->letterIndex++;
}

void Characters::DrawA(TranslateMatrix *translateMatrix, float x_position, float z_position) {
    Cube *cube = new Cube(255.0f, 255.0f, 255.0f, RenderMode::triangles);

    //left column
    translateMatrix->setPosition(x_position, baseHeight + this->letterHeight, z_position);
    translateMatrix->setSize(this->lineWidth, this->letterHeight, this->lineWidth);
    translateMatrix->setObjectRotationAngle(220,vec3(1, 0, 0));
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //right column
    translateMatrix->setPosition(x_position + letterWidth + lineWidth*2, baseHeight + this->letterHeight, z_position);
    translateMatrix->setObjectRotationAngle(220,vec3(-2, 0, 0));
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //middle bar
    translateMatrix->setPosition(x_position+letterWidth-lineWidth, baseHeight + this->letterHeight+1, z_position);
    translateMatrix->setSize(letterWidth, this->lineWidth, this->lineWidth);
    translateMatrix->setObjectRotationAngle(220, vec3(-0.5, 0, 0));
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //top bar
    translateMatrix->setPosition(x_position+letterWidth-lineWidth, baseHeight + this->letterHeight + 3.5f, z_position);
    translateMatrix->setSize(letterWidth -this->lineWidth, this->lineWidth, this->lineWidth);
    translateMatrix->setObjectRotationAngle(220, vec3(-0.5, 0, 0));
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    (new Skateboard(shaderProgram))->Draw(translateMatrix, x_position, z_position);

    this->letterIndex++;
}

void Characters::DrawD(TranslateMatrix *translateMatrix, float x_position, float z_position) {
    Cube *cube = new Cube(255.0f, 255.0f, 255.0f, RenderMode::triangles);

    //left column
    translateMatrix->setPosition(x_position, baseHeight + this->letterHeight, z_position);
    translateMatrix->setSize(this->lineWidth, this->letterHeight, this->lineWidth);
    translateMatrix->setObjectRotationAngle(220, vec3(2, 0, 0));
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //right column
    translateMatrix->setPosition(x_position+letterWidth + 2*lineWidth, baseHeight + this->letterHeight, z_position);
    translateMatrix->setSize(this->lineWidth, this->letterHeight-2*lineWidth, this->lineWidth);
    translateMatrix->setObjectRotationAngle(220, vec3(-0.5, 0, 0));
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //top bar
    translateMatrix->setPosition(x_position+letterWidth-lineWidth, baseHeight + this->letterHeight + 3.5f, z_position);
    translateMatrix->setSize(letterWidth-lineWidth*2, this->lineWidth, this->lineWidth);
    translateMatrix->setObjectRotationAngle(220, vec3(0.5, 0, 0));
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //bottom bar
    translateMatrix->setPosition(x_position+letterWidth-lineWidth, baseHeight + lineWidth, z_position);
    translateMatrix->setSize(letterWidth-lineWidth*2, this->lineWidth, this->lineWidth);
    translateMatrix->setObjectRotationAngle(220, vec3(0.5, 0, 0));
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    (new Skateboard(shaderProgram))->Draw(translateMatrix, x_position, z_position);

    this->letterIndex++;
}

void Characters::DrawE(TranslateMatrix *translateMatrix, float x_position, float z_position) {
    Cube *cube = new Cube(255.0f, 255.0f, 255.0f, RenderMode::triangles);
    translateMatrix->setPosition(x_position, baseHeight + this->letterHeight, z_position);
    translateMatrix->setSize(this->lineWidth, this->letterHeight, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    translateMatrix->setPosition(x_position+letterWidth-lineWidth, baseHeight + this->letterHeight + 3.5f, z_position);
    translateMatrix->setSize(letterWidth, this->lineWidth, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    translateMatrix->setPosition(x_position+letterWidth-lineWidth, baseHeight + this->letterHeight/2+2.5, z_position);
    translateMatrix->setSize(letterWidth, this->lineWidth, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    translateMatrix->setPosition(x_position+letterWidth-lineWidth, baseHeight + lineWidth, z_position);
    translateMatrix->setSize(letterWidth, this->lineWidth, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    (new Skateboard(shaderProgram))->Draw(translateMatrix, x_position, z_position);

    this->letterIndex++;
}

void Characters::DrawT(TranslateMatrix *translateMatrix, float x_position, float z_position) {
    Cube *cube = new Cube(255.0f, 255.0f, 255.0f, RenderMode::triangles);
    translateMatrix->setPosition(x_position + letterWidth/2 + lineWidth, baseHeight + this->letterHeight, z_position);
    translateMatrix->setSize(this->lineWidth, this->letterHeight, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    translateMatrix->setPosition(x_position+letterWidth-lineWidth, baseHeight + this->letterHeight + 3.5f, z_position);
    translateMatrix->setSize(letterWidth, this->lineWidth, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    (new Skateboard(shaderProgram))->Draw(translateMatrix, x_position, z_position);

    this->letterIndex++;
}
