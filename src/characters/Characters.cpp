#include "Characters.h"
#include "../Cube/Cube.h"
#include "../skateboard/Skateboard.h"

Characters::Characters(int shaderProgram, float baseHeight, int selectedCharacterIndex) {
    this->shaderProgram = shaderProgram;
    this->letterHeight = 4.0f;
    this->letterWidth = 2.0f;
    this->letterSpacing = 4.0f;
    this->lineWidth = 0.5f;
    this->letterIndex = 0;
    this->baseHeight = baseHeight;
    this->selectedCharacterIndex = selectedCharacterIndex;
}

float Characters::getLetterXPosition(float x_position) {
    return x_position + (letterWidth + letterSpacing) * letterIndex;
}

vec3 Characters::getColorFromState(int characterIndex) {
    if (this->selectedCharacterIndex == characterIndex) {
        return {240, 128, 128};
    }
    return {255.0f, 255.0f, 255.0f};
}

bool Characters::isSelectedCharacter(int characterIndex) {
    return this->selectedCharacterIndex == characterIndex;
}

void Characters::Draw(TranslateMatrix *translateMatrix, float x_position, float z_position) {
    this->DrawF(translateMatrix, getLetterXPosition(x_position), z_position, 1);
    this->DrawR(translateMatrix, getLetterXPosition(x_position), z_position, 2);
    this->DrawA(translateMatrix, getLetterXPosition(x_position), z_position, 3);
    this->DrawD(translateMatrix, getLetterXPosition(x_position), z_position, 4);
    this->DrawE(translateMatrix, getLetterXPosition(x_position), z_position, 5);
    this->DrawT(translateMatrix, getLetterXPosition(x_position), z_position, 6);
    this->DrawT(translateMatrix, getLetterXPosition(x_position), z_position, 7);
    this->DrawE(translateMatrix, getLetterXPosition(x_position), z_position, 8);
}

void Characters::DrawF(TranslateMatrix *translateMatrix, float x_position, float z_position, int characterIndex) {
    bool isSelected = isSelectedCharacter(characterIndex);
    vec3 color = getColorFromState(characterIndex);

    Cube *cube = new Cube(color.x, color.y, color.z, RenderMode::triangles);
    translateMatrix->setPosition(x_position, baseHeight + this->letterHeight, z_position);
    translateMatrix->setSize(this->lineWidth, this->letterHeight, this->lineWidth);
    translateMatrix->setPathToRotationMatrix(vec3(2, 1, 0));
    translateMatrix->bindTranslationMatrix(this->shaderProgram, isSelected);
    cube->Draw();

    translateMatrix->setPosition(x_position + letterWidth - lineWidth, baseHeight + this->letterHeight + 1, z_position);
    translateMatrix->setSize(letterWidth, this->lineWidth, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram, isSelected);
    cube->Draw();

    translateMatrix->setPosition(x_position + letterWidth - lineWidth, baseHeight + this->letterHeight + 3.5f,
                                 z_position);
    translateMatrix->setSize(letterWidth, this->lineWidth, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram, isSelected);
    cube->Draw();

    this->letterIndex++;
}

void Characters::DrawR(TranslateMatrix *translateMatrix, float x_position, float z_position, int characterIndex) {
    bool isSelected = isSelectedCharacter(characterIndex);
    vec3 color = getColorFromState(characterIndex);

    Cube *cube = new Cube(color.x, color.y, color.z, RenderMode::triangles);

    translateMatrix->setPosition(x_position, baseHeight + this->letterHeight, z_position);
    translateMatrix->setSize(this->lineWidth, this->letterHeight, this->lineWidth);
    translateMatrix->setPathToRotationMatrix(vec3(2, 0, 0));
    translateMatrix->bindTranslationMatrix(this->shaderProgram, isSelected);
    cube->Draw();

    //right top column
    translateMatrix->setPosition(x_position + letterWidth + lineWidth * 2, baseHeight + this->letterHeight + 2.75f,
                                 z_position);
    translateMatrix->setSize(this->lineWidth, this->letterHeight / 2 - 0.75f, this->lineWidth);
    translateMatrix->setPathToRotationMatrix(vec3(-1, 0, 0));
    translateMatrix->bindTranslationMatrix(this->shaderProgram, isSelected);
    cube->Draw();

    //right bottom column
    translateMatrix->setPosition(x_position + letterWidth + lineWidth * 2, baseHeight + this->letterHeight / 2 + 0.25,
                                 z_position);
    translateMatrix->setSize(this->lineWidth, this->letterHeight / 2 + 0.25, this->lineWidth);
    translateMatrix->setPathToRotationMatrix(vec3(-1, 0, 0));
    translateMatrix->bindTranslationMatrix(this->shaderProgram, isSelected);
    cube->Draw();

    //middle bar
    translateMatrix->setPosition(x_position + letterWidth - lineWidth, baseHeight + this->letterHeight + 1, z_position);
    translateMatrix->setSize(letterWidth / 2, this->lineWidth, this->lineWidth);
    translateMatrix->setPathToRotationMatrix(vec3(0.5, 1, 0));
    translateMatrix->bindTranslationMatrix(this->shaderProgram, isSelected);
    cube->Draw();

    //top bar
    translateMatrix->setPosition(x_position + letterWidth - lineWidth, baseHeight + this->letterHeight + 3.5f,
                                 z_position);
    translateMatrix->setSize(letterWidth - this->lineWidth, this->lineWidth, this->lineWidth);
    translateMatrix->setPathToRotationMatrix(vec3(0.5, 1, 0));
    translateMatrix->bindTranslationMatrix(this->shaderProgram, isSelected);
    cube->Draw();

    (new Skateboard(shaderProgram))->Draw(translateMatrix, x_position, z_position);

    this->letterIndex++;
}

void Characters::DrawA(TranslateMatrix *translateMatrix, float x_position, float z_position, int characterIndex) {
    bool isSelected = isSelectedCharacter(characterIndex);
    vec3 color = getColorFromState(characterIndex);

    Cube *cube = new Cube(color.x, color.y, color.z, RenderMode::triangles);

    //left column
    translateMatrix->setPosition(x_position, baseHeight + this->letterHeight, z_position);
    translateMatrix->setSize(this->lineWidth, this->letterHeight, this->lineWidth);
    translateMatrix->setPathToRotationMatrix(vec3(1, 0, 0));
    translateMatrix->bindTranslationMatrix(this->shaderProgram, isSelected);
    cube->Draw();

    //right column
    translateMatrix->setPosition(x_position + letterWidth + lineWidth * 2, baseHeight + this->letterHeight, z_position);
    translateMatrix->setPathToRotationMatrix(vec3(-2, 0, 0));
    translateMatrix->bindTranslationMatrix(this->shaderProgram, isSelected);
    cube->Draw();

    //middle bar
    translateMatrix->setPosition(x_position + letterWidth - lineWidth, baseHeight + this->letterHeight + 1, z_position);
    translateMatrix->setSize(letterWidth, this->lineWidth, this->lineWidth);
    translateMatrix->setPathToRotationMatrix(vec3(-0.5, 0, 0));
    translateMatrix->bindTranslationMatrix(this->shaderProgram, isSelected);
    cube->Draw();

    //top bar
    translateMatrix->setPosition(x_position + letterWidth - lineWidth, baseHeight + this->letterHeight + 3.5f,
                                 z_position);
    translateMatrix->setSize(letterWidth - this->lineWidth, this->lineWidth, this->lineWidth);
    translateMatrix->setPathToRotationMatrix(vec3(-0.5, 0, 0));
    translateMatrix->bindTranslationMatrix(this->shaderProgram, isSelected);
    cube->Draw();

    (new Skateboard(shaderProgram))->Draw(translateMatrix, x_position, z_position);

    this->letterIndex++;
}

void Characters::DrawD(TranslateMatrix *translateMatrix, float x_position, float z_position, int characterIndex) {
    bool isSelected = isSelectedCharacter(characterIndex);
    vec3 color = getColorFromState(characterIndex);

    Cube *cube = new Cube(color.x, color.y, color.z, RenderMode::triangles);

    //left column
    translateMatrix->setPosition(x_position, baseHeight + this->letterHeight, z_position);
    translateMatrix->setSize(this->lineWidth, this->letterHeight, this->lineWidth);
    translateMatrix->setPathToRotationMatrix(vec3(2, 0, 0));
    translateMatrix->bindTranslationMatrix(this->shaderProgram, isSelected);
    cube->Draw();

    //right column
    translateMatrix->setPosition(x_position + letterWidth + 2 * lineWidth, baseHeight + this->letterHeight, z_position);
    translateMatrix->setSize(this->lineWidth, this->letterHeight - 2 * lineWidth, this->lineWidth);
    translateMatrix->setPathToRotationMatrix(vec3(-1, 0, 0));
    translateMatrix->bindTranslationMatrix(this->shaderProgram, isSelected);
    cube->Draw();

    //top bar
    translateMatrix->setPosition(x_position + letterWidth - lineWidth, baseHeight + this->letterHeight + 3.5f,
                                 z_position);
    translateMatrix->setSize(letterWidth - lineWidth * 2, this->lineWidth, this->lineWidth);
    translateMatrix->setPathToRotationMatrix(vec3(0.5, 0, 0));
    translateMatrix->bindTranslationMatrix(this->shaderProgram, isSelected);
    cube->Draw();

    //bottom bar
    translateMatrix->setPosition(x_position + letterWidth - lineWidth, baseHeight + lineWidth, z_position);
    translateMatrix->setSize(letterWidth - lineWidth * 2, this->lineWidth, this->lineWidth);
    translateMatrix->setPathToRotationMatrix(vec3(0.5, 0, 0));
    translateMatrix->bindTranslationMatrix(this->shaderProgram, isSelected);
    cube->Draw();

    (new Skateboard(shaderProgram))->Draw(translateMatrix, x_position, z_position);

    this->letterIndex++;
}

void Characters::DrawE(TranslateMatrix *translateMatrix, float x_position, float z_position, int characterIndex) {
    bool isSelected = isSelectedCharacter(characterIndex);
    vec3 color = getColorFromState(characterIndex);
    Cube *cube = new Cube(color.x, color.y, color.z, RenderMode::triangles);

    translateMatrix->setPosition(x_position, baseHeight + this->letterHeight, z_position);
    translateMatrix->setSize(this->lineWidth, this->letterHeight, this->lineWidth);
    translateMatrix->setPathToRotationMatrix(vec3(1.5, 0, 0));
    translateMatrix->bindTranslationMatrix(this->shaderProgram, isSelected);
    cube->Draw();

    translateMatrix->setPosition(x_position + letterWidth - lineWidth, baseHeight + this->letterHeight + 3.5f,
                                 z_position);
    translateMatrix->setSize(letterWidth, this->lineWidth, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram, isSelected);
    cube->Draw();

    translateMatrix->setPosition(x_position + letterWidth - lineWidth, baseHeight + this->letterHeight / 2 + 2.5,
                                 z_position);
    translateMatrix->setSize(letterWidth, this->lineWidth, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram, isSelected);
    cube->Draw();

    translateMatrix->setPosition(x_position + letterWidth - lineWidth, baseHeight + lineWidth, z_position);
    translateMatrix->setSize(letterWidth, this->lineWidth, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram, isSelected);
    cube->Draw();

    (new Skateboard(shaderProgram))->Draw(translateMatrix, x_position, z_position);

    this->letterIndex++;
}

void Characters::DrawT(TranslateMatrix *translateMatrix, float x_position, float z_position, int characterIndex) {
    bool isSelected = isSelectedCharacter(characterIndex);
    vec3 color = getColorFromState(characterIndex);

    Cube *cube = new Cube(color.x, color.y, color.z, RenderMode::triangles);

    translateMatrix->setPosition(x_position + letterWidth / 2 + lineWidth, baseHeight + this->letterHeight, z_position);
    translateMatrix->setSize(this->lineWidth, this->letterHeight, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram, isSelected);
    cube->Draw();

    translateMatrix->setPosition(x_position + letterWidth - lineWidth, baseHeight + this->letterHeight + 3.5f,
                                 z_position);
    translateMatrix->setSize(letterWidth, this->lineWidth, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram, isSelected);
    cube->Draw();

    (new Skateboard(shaderProgram))->Draw(translateMatrix, x_position, z_position);

    this->letterIndex++;
}
