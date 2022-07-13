#include "../TranslateMatrix/TranslateMatrix.h"

class WorldCube {

public:
    WorldCube(int shaderProgram);

    ~WorldCube();

    void Draw(TranslateMatrix *translateMatrix);

    int shaderProgram;
};
