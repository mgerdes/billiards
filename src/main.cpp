#include "Window.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "BilliardsGame.h"

int main() {
    Window window = Window("opengl", 1000, 1000);

    ResourceManager::installResources();
    BilliardsGame *billiardsGame = new BilliardsGame();
    Renderer *renderer = new Renderer(billiardsGame->getScene(), billiardsGame->getCamera());

    static double lastTime = glfwGetTime(); 
    while (!window.shouldClose()) {
        window.clearBufferAndColor();

        double currentTime = glfwGetTime();
        double timeDelta = currentTime - lastTime;
        lastTime = currentTime;

        billiardsGame->isLeftKeyDown = glfwGetKey(window.glfwWindow, GLFW_KEY_LEFT);
        billiardsGame->isRightKeyDown = glfwGetKey(window.glfwWindow, GLFW_KEY_RIGHT);
        billiardsGame->isUpKeyDown = glfwGetKey(window.glfwWindow, GLFW_KEY_UP);
        billiardsGame->isDownKeyDown = glfwGetKey(window.glfwWindow, GLFW_KEY_DOWN);
        billiardsGame->isWKeyDown = glfwGetKey(window.glfwWindow, GLFW_KEY_W);
        billiardsGame->isAKeyDown = glfwGetKey(window.glfwWindow, GLFW_KEY_A);
        billiardsGame->isSKeyDown = glfwGetKey(window.glfwWindow, GLFW_KEY_S);
        billiardsGame->isDKeyDown = glfwGetKey(window.glfwWindow, GLFW_KEY_D);
        billiardsGame->isSpaceKeyDown = glfwGetKey(window.glfwWindow, GLFW_KEY_SPACE);

        billiardsGame->update(timeDelta);
        renderer->render();

        window.swapBuffers();
    }

    delete billiardsGame;
    delete renderer;

    glfwTerminate();

    return 0;
}
