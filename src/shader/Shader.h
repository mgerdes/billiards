#ifndef BILLIARDS_SHADER_H
#define BILLIARDS_SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Util.h"

class Shader {
    private:
        unsigned int shaderProgram;

        unsigned int compileShader(const char *fileName, int shaderType);
    public:
        Shader(const char *vertexShaderLocation, const char *fragmentShaderLocation);

        void bind();

        void unbind();
};


#endif //BILLIARDS_SHADER_H
