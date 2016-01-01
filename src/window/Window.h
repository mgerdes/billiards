#ifndef BILLIARDS_WINDOW_H
#define BILLIARDS_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Util.h"

class Window {
private:
    GLFWwindow *glfwWindow;
public:
    Window(string name, int width, int height);

    bool shouldClose();

    void clearBufferAndColor();

    void swapBuffers();
};

#endif //BILLIARDS_WINDOW_H
