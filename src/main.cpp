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

    Light light = Light(Vector(2, 2, 2), Vector(0.1, 0.1, 0.1), Vector(0.4, 0.4, 0.4), Vector(0.2, 0.2, 0.2));

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
    float cornerHoleDelta = 0.05f;

    RectangleBoundingObject rectangle = RectangleBoundingObject(x, y, width, height, material, shader);
    CircleBoundingObject pocket1 = CircleBoundingObject(x + cornerHoleDelta, y + cornerHoleDelta, pocketRadius, material, shader);
    CircleBoundingObject pocket2 = CircleBoundingObject(x + width - cornerHoleDelta, y + cornerHoleDelta, pocketRadius, material, shader);
    CircleBoundingObject pocket3 = CircleBoundingObject(x + cornerHoleDelta, y + height - cornerHoleDelta, pocketRadius, material, shader);
    CircleBoundingObject pocket4 = CircleBoundingObject(x + width - cornerHoleDelta, y + height - cornerHoleDelta, pocketRadius, material, shader);
    CircleBoundingObject pocket5 = CircleBoundingObject(x, y + (height / 2.0f), pocketRadius, material, shader);
    CircleBoundingObject pocket6 = CircleBoundingObject(x + width, y + (height / 2.0f), pocketRadius, material, shader);
    Model table = Model("resources/models/table.obj", shader);


    float ballRadius = 0.0250f;
    CircleBoundingObject ball1 = CircleBoundingObject(0, 0, ballRadius, material, shader);

    float theta = 0.0f;
    Matrix modelMatrix;
    Matrix rotationMatrix;
    Matrix translationMatrix;
    Matrix scaleMatrix;

    float delta_x = -0.31f;
    float delta_y = -0.54f;
    float scale = 2.05f;

    double lastKeyPress = 0.0;
    double keyLag = 0.05;
    double currentTime = 0.0;

    while (!window.shouldClose()) {
        window.clearBufferAndColor();

        translationMatrix = Matrix(Vector(0.0, 0.0, 0.0));
        rotationMatrix = Matrix(Vector(0.0, 1.0, 0.0), theta += 0.01);
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
        scaleMatrix = Matrix(scale);
        modelMatrix = rotationMatrix * translationMatrix * scaleMatrix;
        shader.setMatProperty("model_mat", modelMatrix.m);

        table.draw();

        window.swapBuffers();
    }

    glfwTerminate();

    return 0;
}
