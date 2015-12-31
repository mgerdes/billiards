#ifndef BILLIARDS_SHADER_H
#define BILLIARDS_SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "Util.h"
#include "Vec.h"

using namespace std;

class Shader {
private:
    GLuint shaderProgram;
    unordered_map<string, GLint> properties;
public:
    Shader(string vertexShaderLocation, string fragmentShaderLocation);

    void setVec3Property(string propertyName, double x, double y, double z);
};


#endif //BILLIARDS_SHADER_H
