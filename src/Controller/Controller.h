#include <string>
#include "glm/vec3.hpp"
#include "glm/fwd.hpp"
#include "GLFW/glfw3.h"

using namespace glm;
using namespace std;

class Controller {
public:
    Controller(int *shaderProgram);

    ~Controller();

    void reset();

    void setCameraPosition(vec3 cameraPosition, vec3 cameraLookAt, vec3 cameraUp);

    mat4 rotateYAxis(float degreeOfRotation);

    void bindCameraPosition();

    void setCameraPositionFromMouse(GLFWwindow *window, float dt);

    void setMousePosition(GLFWwindow *window);

    void handleMouseRightClick(GLFWwindow *window);

    void handleMouseMiddleClick(GLFWwindow *window);

    void zoomOutFromMouse(GLFWwindow *window);

    vec3 cameraPosition;
    vec3 cameraLookAt;
    string lastMouseState;
    vec3 cameraUp;
    vec3 mousePosition;
    float cameraHorizontalAngle;
    float cameraVerticalAngle;
    int shaderProgram;

private:
    void setDefaultLookAt();

    void normalizeCameraHorizontalAngle();
};