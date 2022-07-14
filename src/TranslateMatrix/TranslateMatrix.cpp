#include "TranslateMatrix.h"
#include "GL/glew.h"
#include "glm/ext/matrix_transform.hpp"

using namespace glm;

//constructor that sets all the state, such as the position and the size to default values
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

// calculates the new translation matrix passed to the shaders from the current state and binds the state so that it is used for render
void TranslateMatrix::bindTranslationMatrix(int shaderProgram, bool shouldRotateObject) {
    // changing the world center position allows rotating around another axis the (0,0,0). My approach is to translate to the world center position, rotate around the world center position and then translate back to the original point for the rendering
    glm::mat4 translationMatrix = translate(mat4(1.0f), this->worldCenterPosition);
    translationMatrix =
            translationMatrix * rotate(mat4(1.0f), radians(this->worldRotationAngle), vec3(0.0f, 1.0f, 0.0f));
    translationMatrix = translationMatrix * translate(mat4(1.0f), worldCenterPosition * -1.0f);

    // translating the object from origin to its position
    translationMatrix = translationMatrix * translate(mat4(1.0f), vec3(position.x, position.y, position.z));

    // rotating the object around its center which is defined by pathToRotationMatrix. Again, my approach is to translate to the pathToRotationMatrix, rotate around the resulting point and then translate back to the original point for the rendering. This allows the letters to rotate on themselves for instance.
    if (shouldRotateObject) {
        translationMatrix = translationMatrix * translate(mat4(1.0f), pathToRotationMatrix);
        translationMatrix = translationMatrix * rotate(mat4(1.0f),
                                                       radians(this->objectRotationAngle),
                                                       vec3(0, 1, 0));
        translationMatrix = translationMatrix * translate(mat4(1.0f), pathToRotationMatrix * -1.0f);
    }

    // scaling the object from the size state
    translationMatrix = translationMatrix * scale(mat4(5.0f), vec3(size.x, size.y, size.z));
    //sets the corresponding uniform (worldMatrix) variable in the shader program
    GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
    glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &translationMatrix[0][0]);

    //resets the object's rotation angle after the bind in order to prevent the object from rotating twice when it is drawn again
    this->resetObjectRotationAngle();
}

//setter
void TranslateMatrix::setObjectRotationAngle(float rotationAngle, vec3 pathToRotationAxis) {
    this->objectRotationAngle = rotationAngle;
}

//setter
void TranslateMatrix::setPathToRotationMatrix(vec3 pathToRotationAxis) {
    this->pathToRotationMatrix = pathToRotationAxis;
}

//reset the path to rotation matrix to the origin
void TranslateMatrix::resetObjectRotationAngle() {
//    this->objectRotationAngle = 0;
    this->pathToRotationMatrix = vec3(0, 0, 0);
}

//setter
void TranslateMatrix::setPosition(float x_position, float y_position, float z_position) {
    this->position.x = x_position;
    this->position.y = y_position;
    this->position.z = z_position;
}

//setter
//note that size maps to scale in the matrix multiplication
void TranslateMatrix::setSize(float x_size, float y_size, float z_size) {
    this->size.x = x_size;
    this->size.y = y_size;
    this->size.z = z_size;
}

//setter
void TranslateMatrix::setWorldRotationAngle(float rotationAngle) {
    this->worldRotationAngle = rotationAngle;
}

//default setter
void TranslateMatrix::setDefaultRotationAngle() {
    this->worldRotationAngle = 0.0f;
}

//default setter
void TranslateMatrix::setDefaultPosition() {
    this->setPosition(0.0f, 0.0f, 0.0f);
}

//default setter
void TranslateMatrix::setDefaultSize() {
    this->setSize(1.0f, 1.0f, 1.0f);
}

//reset the entire state of the translation matrix to default values
void TranslateMatrix::resetDefault() {
    this->setDefaultSize();
    this->setDefaultPosition();
    this->setDefaultRotationAngle();
}