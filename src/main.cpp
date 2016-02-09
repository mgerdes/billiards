#include <vector>
#include "Shader.h"
#include "Window.h"
#include "BilliardsSimulation.h"

using namespace std;

int main() {
    Window window = Window("opengl", 1000, 1000);

    ResourceManager::installResources();
    BilliardsSimulation simulation = BilliardsSimulation(window);

    static double lastTime = glfwGetTime(); 
    while (!window.shouldClose()) {
        window.clearBufferAndColor();

        double currentTime = glfwGetTime();
        double timeDelta = currentTime - lastTime;
        lastTime = currentTime; 

        simulation.update(timeDelta);
        simulation.draw();

        window.swapBuffers();
    }

    glfwTerminate();

    return 0;
}
