#include "../TranslateMatrix/TranslateMatrix.h"

class Characters {
public:
    Characters(int shaderProgram);

    void Draw(
            TranslateMatrix *translateMatrix,
            float x_position,
            float z_position
    );

    int shaderProgram;

private:
    float letterHeight;
    float letterWidth;
    float lineWidth;
    float letterSpacing;
    float letterIndex;

    float getLetterXPosition(float x_position);
    void DrawF(
            TranslateMatrix *translateMatrix,
            float x_position,
            float z_position
    );
    void DrawR(
            TranslateMatrix *translateMatrix,
            float x_position,
            float z_position
    );
    void DrawA(
            TranslateMatrix *translateMatrix,
            float x_position,
            float z_position
    );
    void DrawD(
            TranslateMatrix *translateMatrix,
            float x_position,
            float z_position
    );
    void DrawE(
            TranslateMatrix *translateMatrix,
            float x_position,
            float z_position
    );
    void DrawT(
            TranslateMatrix *translateMatrix,
            float x_position,
            float z_position
    );
};