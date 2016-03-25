#include "Shader.h"

Shader::Shader(const char *vertexShaderFileLocation, const char *fragmentShaderFileLocation) {
    this->shaderProgram = glCreateProgram();

    unsigned int vertexShader = compileShader(vertexShaderFileLocation, GL_VERTEX_SHADER);
    unsigned int fragmentShader = compileShader(fragmentShaderFileLocation, GL_FRAGMENT_SHADER);

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
}

unsigned int Shader::compileShader(const char *fileName, int shaderType) {
    const char *shaderStr = Util::readFile(fileName).c_str();

    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderStr, NULL);
    glCompileShader(shader);

    int params = -1;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &params);
    if (params != GL_TRUE) {
        // TODO -- add better logging
        Util::log(Severity::ERROR, "Could not compile shader: " + std::string(fileName));
        char *shader_log = new char[2048];
        int length;
        glGetShaderInfoLog(shader, 2048, &length, shader_log);
        Util::log(Severity::ERROR, "Shader log:\n" + std::string(shader_log));
    }

    return shader;
}


void Shader::bind() {
    glUseProgram(shaderProgram);
}

void Shader::unbind() {
    glUseProgram(0);
}
