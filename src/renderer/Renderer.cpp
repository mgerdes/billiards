#include "Renderer.h"

Renderer::Renderer(Scene *scene, Camera *camera) {
    this->scene = scene;
    this->camera = camera;
}

void Renderer::render() {
    Mesh** meshes = this->scene->getMeshes();
    int numMeshes = this->scene->getNumMeshes();

    for (int i = 0; i < numMeshes; i++) {
        meshes[i]->getMaterial()->getShader()->bind();
        meshes[i]->draw();
        meshes[i]->getMaterial()->getShader()->unbind();
    }
}
