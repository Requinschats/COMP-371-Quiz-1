#include "../TranslateMatrix/TranslateMatrix.h"

class Skateboard {
public:
    Skateboard(int shaderProgram);

    void Draw(
            TranslateMatrix *translateMatrix,
            float x_position,
            float z_position
    );

    int shaderProgram;
    float height;
};