#ifndef BILLIARDS_SHADER_H
#define BILLIARDS_SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "Util.h"
#include "Vector.h"
#include "Material.h"
#include "Light.h"

using namespace std;

class Shader {
private:
    GLuint shaderProgram;
    unordered_map<string, GLint> properties;
public:
    Shader();

    Shader(string vertexShaderLocation, string fragmentShaderLocation);

    void enable();

    void disable();

    void addProperty(string propertyName);

    void setMaterialProperty(Material &material);

    void setLightProperty(Light &light);

    void setMatProperty(string propertyName, float m[16]);

    void setVec3Property(string propertyName, Vector &v);

    void setVec3Property(string propertyName, float x, float y, float z);

    void setFloatProperty(string propertyName, float f);
};


#endif //BILLIARDS_SHADER_H
