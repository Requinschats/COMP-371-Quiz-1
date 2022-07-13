#include "../TranslateMatrix/TranslateMatrix.h"

class Characters {
public:
    Characters(int shaderProgram, float baseHeight, int selectedCharacterIndex);

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
    int selectedCharacterIndex;

    float getLetterXPosition(float x_position);

    void DrawF(
            TranslateMatrix *translateMatrix,
            float x_position,
            float z_position,
            int letterIndex
    );

    void DrawR(
            TranslateMatrix *translateMatrix,
            float x_position,
            float z_position,
            int letterIndex
    );

    void DrawA(
            TranslateMatrix *translateMatrix,
            float x_position,
            float z_position,
            int letterIndex
    );

    void DrawD(
            TranslateMatrix *translateMatrix,
            float x_position,
            float z_position,
            int letterIndex
    );

    void DrawE(
            TranslateMatrix *translateMatrix,
            float x_position,
            float z_position,
            int letterIndex
    );

    void DrawT(
            TranslateMatrix *translateMatrix,
            float x_position,
            float z_position,
            int letterIndex
    );

    float baseHeight;

    vec3 getColorFromState(int characterIndex);
};