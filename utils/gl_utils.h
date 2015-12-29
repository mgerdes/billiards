#ifndef GL_UTILS_H
#define GL_UTILS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include "window.h"

#define COLOR_RED "\x1b[31m"
#define COLOR_RESET "\x1b[0m"

#define GL_LOG_FILE "log"

enum SEVERITY_LEVELS { INFO, ERROR };

void gl_log(int severity_level, char* message, ...);
GLuint compile_shader(char* filename, GLenum shader_type);
GLuint create_shader_program(char* frag_shader, char* vert_shader);
const char* read_file(char* filename);
GLuint create_texture(char* texture_file);

#endif
