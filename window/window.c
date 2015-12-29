#include "window.h"

Window* create_window(char* title, int width, int height) {
    Window* window = malloc(sizeof(Window));

    window->title = title;
    window->width = width;
    window->height = height;

    if (!glfwInit()) {
        gl_log(ERROR, "Could not start GLFW3");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window->glfwWindow = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!window->glfwWindow) {
        gl_log(ERROR, "Could not create window");
    }

    glfwMakeContextCurrent(window->glfwWindow);
    glewExperimental = GL_TRUE;
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    return window;
}

