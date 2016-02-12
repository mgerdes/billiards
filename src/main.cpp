#include <vector>
#include "Shader.h"
#include "Window.h"
#include "BilliardsSimulation.h"

using namespace std;

int main() {
    Window window = Window("opengl", 1000, 1000);

    ResourceManager::installResources();
    Camera camera = Camera(Vector(2.1, 2, 2.1), Vector(0, 0, 0), Vector(0, 1, 0));
    BilliardsSimulation simulation = BilliardsSimulation(window, camera);

    static double lastTime = glfwGetTime(); 
    while (!window.shouldClose()) {
        window.clearBufferAndColor();

        camera.width = window.getWidth();
        camera.height = window.getHeight();
        camera.updateProjectionMatrix();

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
