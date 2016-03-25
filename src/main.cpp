#include "Window.h"
#include "Renderer.h"
#include "ResourceManager.h"

int main() {
    Window window = Window("opengl", 1000, 1000);

    ResourceManager::installResources();

    Geometry *triangleGeometry = new Geometry(3);
    triangleGeometry->addVertex(0, 1, 0);
    triangleGeometry->addVertex(1, 0, 0);
    triangleGeometry->addVertex(-1, 0, 0);

    Shader *triangleShader = ResourceManager::getShader(Shaders::BASIC);
    Material *triangleMaterial = new Material(triangleShader);

    Mesh *triangleMesh = new Mesh(triangleGeometry, triangleMaterial);

    Scene *scene = new Scene(1);
    scene->addMesh(triangleMesh);

    Camera *camera;

    Renderer *renderer = new Renderer(scene, camera);

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
