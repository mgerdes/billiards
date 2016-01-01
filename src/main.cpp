#include <vector>
#include "Shader.h"
#include "Mesh.h"
#include "GeometricObjects.h"
#include "Camera.h"

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

    Camera camera = Camera(Vector(2, 2, 2), Vector(0, 0, 0), Vector(0, 1, 0));

    Light light = Light(Vector(2, 2, 2), Vector(0.6, 0.6, 0.6), Vector(0.3, 0.3, 0.3), Vector(0.0, 0.0, 0.0));
    Material material = Material(Vector(1, 1, 0), Vector(1, 1, 0), Vector(1, 1, 0), 0.2);

    Shader shader = Shader("resources/shaders/vert.glsl", "resources/shaders/frag.glsl");
    shader.setLightProperty(light);
    shader.setVec3Property("camera_position", camera.position);
    shader.setMatProperty("proj_mat", camera.projectionMatrix.m);
    shader.setMatProperty("view_mat", camera.viewMatrix.m);

    Mesh square = Mesh(GeometricObjects::getCubeVertices(),
                       GeometricObjects::getCubeNormals(),
                       material, shader);

    float theta = 0;
    Matrix modelMatrix;
    Matrix rotationMatrix;
    Matrix translationMatrix;
    Matrix scaleMatrix;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        translationMatrix = Matrix(Vector(0.0, 0.0, 0.0));
        rotationMatrix = Matrix(Vector(0, 1, 0), theta += 0.01);
        scaleMatrix = Matrix(0.8);
        modelMatrix = translationMatrix * scaleMatrix * rotationMatrix;

        shader.setMatProperty("model_mat", modelMatrix.m);
        square.draw();

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}
