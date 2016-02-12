#ifndef BILLIARDS_WINDOW_H
#define BILLIARDS_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Util.h"

class Window {
public:
    GLFWwindow *glfwWindow;

    Window(string name, int width, int height);

    bool shouldClose();

    void clearBufferAndColor();

    void swapBuffers();

    int getWidth();

    int getHeight();
};

#endif //BILLIARDS_WINDOW_H
