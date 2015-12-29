#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <string.h>
#include "gl_utils.h"

typedef struct Window {
    char* title;
    int width, height;
    GLFWwindow* glfwWindow;
} Window;

Window* create_window(char* title, int width, int height);

#endif
