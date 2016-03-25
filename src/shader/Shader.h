#ifndef BILLIARDS_SHADER_H
#define BILLIARDS_SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Util.h"
#include <unordered_map>

class Shader {
    private:
        unsigned int shaderProgram;
        std::unordered_map<string, GLint> properties;

        unsigned int compileShader(const char *fileName, int shaderType);
    public:
        Shader(const char *vertexShaderLocation, const char *fragmentShaderLocation);

        void addProperty(const char *propertyName);

        void setMatProperty(const char* propertyName, float m[16]);

        void bind();

        void unbind();
};


#endif //BILLIARDS_SHADER_H
