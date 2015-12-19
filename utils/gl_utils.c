#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include "gl_utils.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "camera.h"
#include "maths.h"

#define COLOR_RED "\x1b[31m"
#define COLOR_RESET "\x1b[0m"

void gl_log(int severity_level, char* message, ...) {
    va_list argptr;
    FILE* file = fopen(GL_LOG_FILE, "a");
    if (!file) {
        fprintf(stderr, "ERROR: could not open GL_LOG_FILE %s file\n", GL_LOG_FILE);
    }

    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);

    fprintf(file, "[%d-%d-%d %2d:%2d] ", 
            timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, 
            timeinfo->tm_hour, timeinfo->tm_min);
    if (severity_level == ERROR) {
        fprintf(file, "ERROR: ");
    } else if (severity_level == INFO) {
        fprintf(file, "INFO: ");
    }
    va_start(argptr, message);
    vfprintf(file, message, argptr);
    va_end(argptr);
    fprintf(file, "\n");

    // Also print to stderr if there is an error.
    if (severity_level == ERROR) {
        fprintf(stderr, "[%d-%d-%d %2d:%2d] ", 
                timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, 
                timeinfo->tm_hour, timeinfo->tm_min);
        fprintf(stderr, COLOR_RED "ERROR: " COLOR_RESET);
        va_start(argptr, message);
        vfprintf(stderr, message, argptr);
        va_end(argptr);
        fprintf(stderr, "\n");
    }

    fclose(file);
}

void init_gl(char* window_title) {
    if (!glfwInit()) {
        gl_log(ERROR, "Could not start GLFW3");
    } 

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(window_width, window_height, window_title, NULL, NULL);

    if (!window) {
        gl_log(ERROR, "Could not create window");
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();
    glEnable(GL_DEPTH_TEST); 
    glDepthFunc(GL_LESS);
}

GLuint compile_shader(char* filename, GLenum shader_type) {
    gl_log(INFO, "Started compiling shader: %s", filename);

    const char* shader_str = read_file(filename);
    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &shader_str, NULL);
    glCompileShader(shader);
    free((char*) shader_str);

    int params = -1;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &params);
    if (params != GL_TRUE) {
        gl_log(ERROR, "Could not compile shader: %s.", filename);
        char* shader_log = malloc(sizeof(char)*2048);
        int length;
        glGetShaderInfoLog(shader, 2048, &length, shader_log);
        gl_log(ERROR, "Shader log: %s", shader_log);
    }

    gl_log(INFO, "Finished compiling shader: %s", filename);
    return shader;
}

GLuint create_shader_program(char* frag_shader_filename, char* vert_shader_filename) {
    GLuint frag_shader = compile_shader(frag_shader_filename, GL_FRAGMENT_SHADER);
    GLuint vert_shader = compile_shader(vert_shader_filename, GL_VERTEX_SHADER);

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, frag_shader);
    glAttachShader(shader_program, vert_shader);
    glLinkProgram(shader_program);
    glUseProgram(shader_program);

    return shader_program;
}

const char* read_file(char* filename) {
    char* buffer = 0;
    long length;
    FILE* f = fopen(filename, "rb");

    if (!f) {
        gl_log(ERROR, "Could not read file %s\n", filename); 
        return 0;
    } 

    fseek(f, 0, SEEK_END);
    length = ftell (f);
    fseek(f, 0, SEEK_SET);
    buffer = malloc (length);
    if (buffer) {
        fread (buffer, 1, length, f);
    }
    fclose(f);
    buffer[length] = 0;

    return buffer;
}

GLuint create_texture(char* file_name) {
    int x, y, n;
    int force_channels = 3;
    unsigned char* image_data = stbi_load(file_name, &x, &y, &n, force_channels);
    if (!image_data) {
        gl_log(ERROR, "Could not load texture image file, %s", file_name); 
        return 0;
    }

    GLuint tex = 0;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    return tex;
}
