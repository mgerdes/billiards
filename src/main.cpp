#include "Window.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "ObjLoader.h"

int main() {
    Window window = Window("opengl", 1000, 1000);

    ResourceManager::installResources();
    Object3D *table = ObjLoader::loadObject("resources/models/table.obj");

    Geometry *triangleGeometry = new Geometry(6);
    triangleGeometry->addVertex(1, 1, 0);
    triangleGeometry->addVertex(1, 0, 0);
    triangleGeometry->addVertex(-1, 0, 0);
    triangleGeometry->addVertex(1, 1, 0);
    triangleGeometry->addVertex(-1, 1, 0);
    triangleGeometry->addVertex(-1, 0, 0);

    Shader *triangleShader = ResourceManager::getShader(Shaders::BASIC);
    Material *triangleMaterial = new Material(triangleShader);

    Mesh *triangleMesh = new Mesh(triangleGeometry, triangleMaterial);

    Scene *scene = new Scene(1);
    scene->addObject(table);

    Camera *camera = new Camera(45, 1, 0.1, 100);

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
