#include <vector>
#include "Shader.h"
#include "Camera.h"
#include "Window.h"
#include "BilliardsSimulation.h"

using namespace std;

int main() {
    Window window = Window("opengl", 1000, 1000);

    Camera camera = Camera(Vector(2.1, 2, 2.1), Vector(0, 0, 0), Vector(0, 1, 0));
    Material material = Material(Vector(1, 1, 1), Vector(1, 1, 1), Vector(1, 1, 1), 1.0);
    Shader shader = Shader("resources/shaders/vert.glsl", "resources/shaders/frag.glsl");

    BilliardsSimulation simulation = BilliardsSimulation(window, material, shader, camera);

    while (!window.shouldClose()) {
        window.clearBufferAndColor();

        simulation.draw();

        window.swapBuffers();
    }

    glfwTerminate();

    return 0;
}
