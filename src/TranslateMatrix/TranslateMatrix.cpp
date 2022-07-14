#include "TranslateMatrix.h"
#include "GL/glew.h"
#include "glm/ext/matrix_transform.hpp"

using namespace glm;

TranslateMatrix::TranslateMatrix(float x_position,
                                 float y_position,
                                 float z_position,
                                 float x_size,
                                 float y_size,
                                 float z_size) {
    this->setPosition(x_position, y_position, z_position);
    this->setSize(x_size, y_size, z_size);
    this->setWorldRotationAngle(0.0f);
    this->setObjectRotationAngle(0);
    this->worldCenterPosition = vec3(0, 0, 0);
}

void TranslateMatrix::bindTranslationMatrix(int shaderProgram, bool shouldRotateObject) {
    glm::mat4 translationMatrix = translate(mat4(1.0f), this->worldCenterPosition);
    translationMatrix =
            translationMatrix * rotate(mat4(1.0f), radians(this->worldRotationAngle), vec3(0.0f, 1.0f, 0.0f));
    translationMatrix = translationMatrix * translate(mat4(1.0f), worldCenterPosition * -1.0f);


    translationMatrix = translationMatrix * translate(mat4(1.0f), vec3(position.x, position.y, position.z));

    if (shouldRotateObject) {
        translationMatrix = translationMatrix * translate(mat4(1.0f), pathToRotationMatrix);
        translationMatrix = translationMatrix * rotate(mat4(1.0f),
                                                       radians(this->objectRotationAngle),
                                                       vec3(0, 1, 0));
        translationMatrix = translationMatrix * translate(mat4(1.0f), pathToRotationMatrix * -1.0f);
    }

    translationMatrix = translationMatrix * scale(mat4(5.0f), vec3(size.x, size.y, size.z));
    GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
    glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &translationMatrix[0][0]);

    this->resetObjectRotationAngle();
}

void TranslateMatrix::setObjectRotationAngle(float rotationAngle, vec3 pathToRotationAxis) {
    this->objectRotationAngle = rotationAngle;
}

void TranslateMatrix::setPathToRotationMatrix(vec3 pathToRotationAxis) {
    this->pathToRotationMatrix = pathToRotationAxis;
}

void TranslateMatrix::resetObjectRotationAngle() {
//    this->objectRotationAngle = 0;
    this->pathToRotationMatrix = vec3(0, 0, 0);
}

void TranslateMatrix::setPosition(float x_position, float y_position, float z_position) {
    this->position.x = x_position;
    this->position.y = y_position;
    this->position.z = z_position;
}

void TranslateMatrix::setSize(float x_size, float y_size, float z_size) {
    this->size.x = x_size;
    this->size.y = y_size;
    this->size.z = z_size;
}

void TranslateMatrix::setWorldRotationAngle(float rotationAngle) {
    this->worldRotationAngle = rotationAngle;
}

void TranslateMatrix::setDefaultRotationAngle() {
    this->worldRotationAngle = 0.0f;
}

void TranslateMatrix::setDefaultPosition() {
    this->setPosition(0.0f, 0.0f, 0.0f);
}

void TranslateMatrix::setDefaultSize() {
    this->setSize(1.0f, 1.0f, 1.0f);
}

void TranslateMatrix::resetDefault() {
    this->setDefaultSize();
    this->setDefaultPosition();
    this->setDefaultRotationAngle();
}