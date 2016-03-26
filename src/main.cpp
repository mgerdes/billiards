#include "Window.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "ObjLoader.h"

int main() {
    Window window = Window("opengl", 1000, 1000);

    ResourceManager::installResources();
    Object3D *table = ObjLoader::loadObject("resources/models/table.obj");
    Scene *scene = new Scene(1);
    scene->addObject(table);

    Camera *camera = new Camera(45.0, 1.0, 0.1, 100);

    Renderer *renderer = new Renderer(scene, camera);

    table->updateModelMat();

    static double lastTime = glfwGetTime(); 
    while (!window.shouldClose()) {
        window.clearBufferAndColor();

        double currentTime = glfwGetTime();
        double timeDelta = currentTime - lastTime;
        lastTime = currentTime;

        renderer->render();

        window.swapBuffers();
    }

    glfwTerminate();

    return 0;
}
