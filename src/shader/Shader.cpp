#include "Shader.h"

using namespace std;

GLuint compileShader(string fileName, GLenum shaderType) {
    string shaderStr = Util::readFile(fileName);
    const char *cShaderStr = shaderStr.c_str();

    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &cShaderStr, NULL);
    glCompileShader(shader);

    int params = -1;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &params);
    if (params != GL_TRUE) {
        Util::log(Severity::ERROR, "Could not compile shader: " + fileName);
        char *shader_log = new char[2048];
        int length;
        glGetShaderInfoLog(shader, 2048, &length, shader_log);
        Util::log(Severity::ERROR, "Shader log:\n" + string(shader_log));
    }

    return shader;
}

Shader::Shader() { }

Shader::Shader(string vertexShaderFileLocation, string fragmentShaderFileLocation) : shaderProgram(glCreateProgram()) {
    GLuint vertexShader = compileShader(vertexShaderFileLocation, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(fragmentShaderFileLocation, GL_FRAGMENT_SHADER);

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
}

void Shader::enable() {
    glUseProgram(shaderProgram);
}

void Shader::disable() {
    glUseProgram(0);
}

void Shader::addProperty(string propertyName) {
    GLint propertyLocation = glGetUniformLocation(shaderProgram, propertyName.c_str());
    if (propertyLocation == -1) {
        Util::log(Severity::ERROR, "Attempting to add an invalid property name to shader: " + propertyName);
    }
    properties[propertyName] = propertyLocation;
}

void Shader::setMaterialProperty(Material &material) {
    setVec3Property("material.ambient_color", material.ambientColor);
    setVec3Property("material.diffuse_color", material.diffuseColor);
    setVec3Property("material.specular_color", material.specularColor);
    setFloatProperty("material.shininess", material.shininess);
}

void Shader::setLightProperty(Light &light) {
    setVec3Property("light.position", light.position);
    setVec3Property("light.ambient_color", light.ambientColor);
    setVec3Property("light.diffuse_color", light.diffuseColor);
    setVec3Property("light.specular_color", light.specularColor);
}

void Shader::setVec3Property(string propertyName, Vector &v) {
    setVec3Property(propertyName, v.x, v.y, v.z);
}

void Shader::setVec3Property(string propertyName, float x, float y, float z) {
    enable();

    if (!properties.count(propertyName)) {
        addProperty(propertyName);
    }
    glUniform3f(properties[propertyName], x, y, z);

    disable();
}

void Shader::setFloatProperty(string propertyName, float f) {
    enable();

    if (!properties.count(propertyName)) {
        addProperty(propertyName);
    }
    glUniform1f(properties[propertyName], f);

    disable();
}

void Shader::setMatProperty(string propertyName, float m[16]) {
    enable();

    if (!properties.count(propertyName)) {
        addProperty(propertyName);
    }
    glUniformMatrix4fv(properties[propertyName], 1, GL_FALSE, m);

    disable();
}
