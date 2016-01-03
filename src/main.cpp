#include <vector>
#include "Shader.h"
#include "Window.h"
#include "BilliardsSimulation.h"

using namespace std;

int main() {
    Window window = Window("opengl", 1000, 1000);

    ResourceManager resourceManager;

    BilliardsSimulation simulation = BilliardsSimulation(window, resourceManager);

    while (!window.shouldClose()) {
        window.clearBufferAndColor();

        simulation.draw();

        window.swapBuffers();
    }

    glfwTerminate();

    return 0;
}
