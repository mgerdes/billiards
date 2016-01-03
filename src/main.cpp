#include <vector>
#include "Shader.h"
#include "Mesh.h"
#include "Model.h"
#include "GeometricObjects.h"
#include "Camera.h"
#include "Window.h"
#include "BoundingObject.h"

using namespace std;

int main() {
    Window window = Window("opengl", 1000, 1000);

    Camera camera = Camera(Vector(2, 2, 2), Vector(0, 0, 0), Vector(0, 1, 0));

    Light light = Light(Vector(2, 2, 2), Vector(0.2, 0.2, 0.2), Vector(0.8, 0.8, 0.8), Vector(0.0, 0.0, 0.0));

    Material material = Material(Vector(1, 1, 0), Vector(1, 1, 0), Vector(0, 0, 0), 0.2);

    Shader shader = Shader("resources/shaders/vert.glsl", "resources/shaders/frag.glsl");
    shader.setLightProperty(light);
    shader.setVec3Property("camera_position", camera.position);
    shader.setMatProperty("proj_mat", camera.projectionMatrix.m);
    shader.setMatProperty("view_mat", camera.viewMatrix.m);

    Model cat = Model("resources/models/cat.obj", shader);

    Mesh square = Mesh(GeometricObjects::getCubeVertices(),
                       GeometricObjects::getCubeNormals(),
                       material,
                       shader);

    float pocketRadius = 0.1f;
    float x = -0.5f;
    float y = -1.0f;
    float width = 1.0f;
    float height = 2.0f;

    RectangleBoundingObject rectangle = RectangleBoundingObject(x, y, width, height, material, shader);

    CircleBoundingObject circle1 = CircleBoundingObject(x, y, pocketRadius, material, shader);
    CircleBoundingObject circle2 = CircleBoundingObject(x + width, y, pocketRadius, material, shader);
    CircleBoundingObject circle3 = CircleBoundingObject(x, y + height, pocketRadius, material, shader);
    CircleBoundingObject circle4 = CircleBoundingObject(x + width, y + height, pocketRadius, material, shader);
    CircleBoundingObject circle5 = CircleBoundingObject(x, y + (height / 2.0f), pocketRadius, material, shader);
    CircleBoundingObject circle6 = CircleBoundingObject(x + width, y + (height / 2.0f), pocketRadius, material, shader);

    float theta = 0;
    Matrix modelMatrix;
    Matrix rotationMatrix;
    Matrix translationMatrix;
    Matrix scaleMatrix;

    while (!window.shouldClose()) {
        window.clearBufferAndColor();

        translationMatrix = Matrix(Vector(0.0, 0.0, 0.0));
        rotationMatrix = Matrix(Vector(0, 1, 0), theta += 0.01);
        scaleMatrix = Matrix(1.0);
        modelMatrix = translationMatrix * scaleMatrix * rotationMatrix;

        circle1.draw();
        circle2.draw();
        circle3.draw();
        circle4.draw();
        circle5.draw();
        circle6.draw();
        rectangle.draw();
        square.shader.setMatProperty("model_mat", modelMatrix.m);
        //square.draw();

        cat.draw();

        window.swapBuffers();
    }

    glfwTerminate();

    return 0;
}
