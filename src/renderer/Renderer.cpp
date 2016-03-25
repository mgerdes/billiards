#include "Renderer.h"

Renderer::Renderer(Scene *scene, Camera *camera) {
    this->scene = scene;
    this->camera = camera;
}

void Renderer::renderObject(Object3D *object) {
    if (object->getIsMesh()) {
        Mesh *mesh = (Mesh*) object;
        mesh->getMaterial()->getShader()->bind();
        mesh->draw();
        mesh->getMaterial()->getShader()->unbind();
    }

    Object3D **children = object->getChildren();
    for (int i = 0; i < object->getNumChildren(); i++) {
        renderObject(children[i]);
    }
}

void Renderer::render() {
    Object3D** objects = this->scene->getObjects();
    int numObjects = this->scene->getNumObjects();

    for (int i = 0; i < numObjects; i++) {
        renderObject(objects[i]);
    }
}
