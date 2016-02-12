#include "Window.h"

Window::Window(string title, int width, int height) {
    if (!glfwInit()) {
        Util::log(ERROR, "Could not start GLFW3");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    if (!glfwWindow) {
        Util::log(ERROR, "Could not create window");
    }

    glfwMakeContextCurrent(glfwWindow);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        Util::log(ERROR, "Could not start GLEW");
    }
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

bool Window::shouldClose() {
    return (bool) glfwWindowShouldClose(glfwWindow);
}

void Window::clearBufferAndColor() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::swapBuffers() {
    glfwPollEvents();
    glfwSwapBuffers(glfwWindow);
}

int Window::getWidth() {
    int width, height;
    glfwGetFramebufferSize(glfwWindow, &width, &height);
    return width;
}

int Window::getHeight() {
    int width, height;
    glfwGetFramebufferSize(glfwWindow, &width, &height);
    return height;
}
