#include <vector>
#include "Shader.h"
#include "Window.h"
#include "BilliardsSimulation.h"

using namespace std;

int main() {
    Window window = Window("opengl", 1000, 1000);

    ResourceManager::installResources();
    BilliardsSimulation simulation = BilliardsSimulation(window);

    while (!window.shouldClose()) {
        window.clearBufferAndColor();

        simulation.draw();

        window.swapBuffers();
    }

    glfwTerminate();

    return 0;
}
