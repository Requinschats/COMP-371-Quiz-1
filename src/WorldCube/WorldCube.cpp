#include "WorldCube.h"
#include "../Cube/Cube.h"

WorldCube::WorldCube(int shaderProgram) {
    this->shaderProgram = shaderProgram;
}

void WorldCube::Draw(TranslateMatrix *translateMatrix) {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    Cube *cube = new Cube(135.0f, 206.0f, 235.0f, RenderMode::triangles);
    translateMatrix->setPosition(0, 0, 0);
    translateMatrix->setSize(51, 50, 50);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();
}