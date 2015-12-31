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

Shader::Shader(string vertexShaderFileLocation, string fragmentShaderFileLocation) {
    GLuint vertexShader = compileShader(vertexShaderFileLocation, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(fragmentShaderFileLocation, GL_FRAGMENT_SHADER);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
}

void Shader::setVec3Property(string propertyName, double x, double y, double z) {
    if (!properties.count(propertyName)) {
        GLint propertyLocation = glGetUniformLocation(shaderProgram, propertyName.c_str());
        properties[propertyName] = propertyLocation;
    }
    glUniform3f(properties[propertyName], (GLfloat) x, (GLfloat) y, (GLfloat) z);
}
