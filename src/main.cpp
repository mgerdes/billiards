#include <vector>
#include "Shader.h"
#include "Model.h"
#include "Camera.h"
#include "Window.h"
#include "BoundingObject.h"

using namespace std;

int main() {
    Window window = Window("opengl", 1000, 1000);

    Camera camera = Camera(Vector(2.1, 2, 2.1), Vector(0, 0, 0), Vector(0, 1, 0));

    Light light = Light(Vector(2, 2, 2), Vector(0.1, 0.1, 0.1), Vector(0.6, 0.6, 0.6), Vector(0.0, 0.0, 0.0));

    Material material = Material(Vector(0, 0, 0), Vector(0, 0, 0), Vector(0, 0, 0), 1.0);

    Shader shader = Shader("resources/shaders/vert.glsl", "resources/shaders/frag.glsl");
    shader.setLightProperty(light);
    shader.setVec3Property("camera_position", camera.position);
    shader.setMatProperty("proj_mat", camera.projectionMatrix.m);
    shader.setMatProperty("view_mat", camera.viewMatrix.m);

    float pocketRadius = 0.1f;
    float x = -0.5f;
    float y = -1.0f;
    float width = 1.0f;
    float height = 2.0f;
    float cornerHoleDeltaX = -0.028f;
    float cornerHoleDeltaY = -0.01f;
    float middleHoleDeltaX = -0.10f;

    RectangleBoundingObject rectangle = RectangleBoundingObject(x, y, width, height, material, shader);
    CircleBoundingObject pocket1 = CircleBoundingObject(x + cornerHoleDeltaX, y + cornerHoleDeltaY, pocketRadius, material, shader);
    CircleBoundingObject pocket2 = CircleBoundingObject(x + width - cornerHoleDeltaX, y + cornerHoleDeltaY, pocketRadius, material, shader);
    CircleBoundingObject pocket3 = CircleBoundingObject(x + cornerHoleDeltaX, y + height - cornerHoleDeltaY, pocketRadius, material, shader);
    CircleBoundingObject pocket4 = CircleBoundingObject(x + width - cornerHoleDeltaX, y + height - cornerHoleDeltaY, pocketRadius, material, shader);
    CircleBoundingObject pocket5 = CircleBoundingObject(x + middleHoleDeltaX, y + (height / 2.0f), pocketRadius, material, shader);
    CircleBoundingObject pocket6 = CircleBoundingObject(x + width - middleHoleDeltaX, y + (height / 2.0f), pocketRadius, material, shader);
    Model table = Model("resources/models/table.obj", shader);

    float ballRadius = 0.0250f;
    CircleBoundingObject ball1 = CircleBoundingObject(0, 0, ballRadius, material, shader);

    float theta = 0.0f;
    Matrix modelMatrix;
    Matrix rotationMatrix;
    Matrix translationMatrix;
    Matrix scaleMatrix;

    float delta_x = -0.325f;
    float delta_y = -0.61f;
    float scale_x = 2.16f;
    float scale_y = 2.55f;

    double lastKeyPress = 0.0;
    double keyLag = 0.05;
    double currentTime = 0.0;

    bool debugTablePosition = false;

    while (!window.shouldClose()) {
        window.clearBufferAndColor();

        currentTime = glfwGetTime();
        if (debugTablePosition) {
            if (currentTime > lastKeyPress + keyLag) {
                if (glfwGetKey(window.glfwWindow, GLFW_KEY_UP)) {
                    lastKeyPress = currentTime;
                    delta_y += 0.01;
                }
                if (glfwGetKey(window.glfwWindow, GLFW_KEY_DOWN)) {
                    lastKeyPress = currentTime;
                    delta_y -= 0.01;
                }
                if (glfwGetKey(window.glfwWindow, GLFW_KEY_RIGHT)) {
                    lastKeyPress = currentTime;
                    delta_x += 0.01;
                }
                if (glfwGetKey(window.glfwWindow, GLFW_KEY_LEFT)) {
                    lastKeyPress = currentTime;
                    delta_x -= 0.01;
                }
                if (glfwGetKey(window.glfwWindow, GLFW_KEY_W)) {
                    lastKeyPress = currentTime;
                    scale_y += 0.01;
                }
                if (glfwGetKey(window.glfwWindow, GLFW_KEY_S)) {
                    lastKeyPress = currentTime;
                    scale_y -= 0.01;
                }
                if (glfwGetKey(window.glfwWindow, GLFW_KEY_D)) {
                    lastKeyPress = currentTime;
                    scale_x += 0.01;
                }
                if (glfwGetKey(window.glfwWindow, GLFW_KEY_A)) {
                    lastKeyPress = currentTime;
                    scale_x -= 0.01;
                }
                cout << "delta_x = " << delta_x << endl;
                cout << "delta_y = " << delta_y << endl;
                cout << "scale_x = " << scale_x << endl;
                cout << "scale_y = " << scale_y << endl;
            }
        }

        translationMatrix = Matrix(Vector(0.0, 0.0, 0.0));
        rotationMatrix = Matrix(Vector(0.0, 1.0, 0.0), theta);
        scaleMatrix = Matrix(1.0);
        modelMatrix = rotationMatrix * translationMatrix * scaleMatrix;
        shader.setMatProperty("model_mat", modelMatrix.m);

        pocket1.draw();
        pocket2.draw();
        pocket3.draw();
        pocket4.draw();
        pocket5.draw();
        pocket6.draw();
        rectangle.draw();

        ball1.draw();

        translationMatrix = Matrix(Vector(delta_x, delta_y, 0.0));
        rotationMatrix = Matrix(Vector(0.0, 1.0, 0.0), theta + (float) (M_PI / 2.0));
        scaleMatrix = Matrix::scaleMatrix(Vector(scale_x, (scale_x + scale_y) / 2, scale_y));
        modelMatrix = rotationMatrix * translationMatrix * scaleMatrix;
        shader.setMatProperty("model_mat", modelMatrix.m);

        theta += 0.01;

        table.draw();

        window.swapBuffers();
    }

    glfwTerminate();

    return 0;
}
