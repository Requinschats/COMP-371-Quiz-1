#include "GeneralShader.h"

// vertex shader source code. Uniform variables are passed to the shader program and the matrix is multiplied view modifications.
char *getVertexShaderSource() {
    return
            "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;"
            "layout (location = 1) in vec3 aColor;"
            ""
            "uniform mat4 worldMatrix;"
            "uniform mat4 viewMatrix = mat4(1.0f);"
            "uniform mat4 projectionMatrix = mat4(1.0f);"
            ""
            "out vec3 vertexColor;"
            "void main()"
            "{"
            "   vertexColor = aColor;"
            "   gl_Position = projectionMatrix * viewMatrix * worldMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);"
            "}";
}

// default fragment shader source code. The color of the pixel is determined by the color of the vertex.
char *getFragmentShaderSource() {
    return
            "#version 330 core\n"
            "in vec3 vertexColor;"
            "out vec4 FragColor;"
            "void main()"
            "{"
            "   FragColor = vec4(vertexColor.r, vertexColor.g, vertexColor.b, 1.0f);"
            "}";
}
