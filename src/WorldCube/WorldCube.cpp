#include "WorldCube.h"
#include "../Cube/Cube.h"

WorldCube::WorldCube(int shaderProgram) {
    this->shaderProgram = shaderProgram;
}

void WorldCube::Draw(TranslateMatrix *translateMatrix) {
    glEnable(GL_CULL_FACE);
    //culling the front actually draws the back which is essential for the world cube
    glCullFace(GL_FRONT);
    //sky color is passed
    Cube *cube = new Cube(135.0f, 206.0f, 235.0f, RenderMode::triangles);
    //world center is (0,0,0)
    translateMatrix->setPosition(0, 0, 0);
    //same size as the grid
    translateMatrix->setSize(51, 50, 50);
    //binds the translation matrix to the shader program
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();
}