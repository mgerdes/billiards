#include <vector>
#include "Shader.h"
#include "Vec.h"
#include "Mesh.h"

using namespace std;

int main() {
    if (!glfwInit()) {
        Util::log(ERROR, "Could not start GLFW3");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(1000, 1000, "opengl", NULL, NULL);

    if (!window) {
        Util::log(ERROR, "Could not create window");
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        Util::log(ERROR, "Could not start GLEW");
    }
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    Shader shader = Shader("resources/shaders/vert.glsl", "resources/shaders/frag.glsl");
    shader.setVec3Property("in_color", 1, 1, 0.5);

    vector<Vec> trianglePositions;
    trianglePositions.push_back(Vec(0, 1, 0));
    trianglePositions.push_back(Vec(1, 0, 0));
    trianglePositions.push_back(Vec(-1, 0, 0));
    trianglePositions.push_back(Vec(0, -1, 0));
    trianglePositions.push_back(Vec(1, 0, 0));
    trianglePositions.push_back(Vec(-1, 0, 0));

    Mesh triangle = Mesh(trianglePositions, shader);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        triangle.draw();

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}
