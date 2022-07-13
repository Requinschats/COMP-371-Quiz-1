#pragma once

#include <glm/glm.hpp>
using namespace glm;

class TranslateMatrix {
    struct Size {
        float x;
        float y;
        float z;
    };

    struct Position {
        float x;
        float y;
        float z;
    };
public:
    TranslateMatrix(float x_position,
                    float y_position,
                    float z_position,
                    float x_size,
                    float y_size,
                    float z_size);

    void bindTranslationMatrix(int shaderProgram, float objectRotationAngle=0);

    Position position;
    Size size;
    float worldRotationAngle;
    float objectRotationAngle;
    vec3 pathToRotationMatrix;

    void setPosition(float x_position, float y_position, float z_position);

    void setSize(float x_size, float y_size, float z_size);

    void setWorldRotationAngle(float rotationAngle);

    void setObjectRotationAngle(float rotationAngle, vec3 pathToRotationAxis = vec3(0, 0, 0));

    void resetObjectRotationAngle();

    void setDefaultPosition();

    void setDefaultSize();

    void setDefaultRotationAngle();

    void resetDefault();
};
