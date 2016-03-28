#include "Renderer.h"

Renderer::Renderer(Scene *scene, Camera *camera) {
    this->scene = scene;
    this->camera = camera;
}

void Renderer::renderObject(Object3D *object, Matrix4 *modelMat) {
    if (!object->isVisible) {
        return;
    }

    Matrix4 temp = Matrix4::multiply(object->getModelMat(), modelMat);
    modelMat = &temp;

    if (object->isMesh) {
        Mesh *mesh = (Mesh*) object;

        // Bind the necessary stuff.
        mesh->getMaterial()->getShader()->bind();
        if (mesh->getMaterial()->getTexture()) {
            mesh->getMaterial()->getTexture()->bind();
        }

        // Send matrices into the shader.
        mesh->getMaterial()->getShader()->setMatProperty("proj_mat", camera->getProjectionMatrix()->m);
        mesh->getMaterial()->getShader()->setMatProperty("view_mat", camera->getViewMatrix()->m);
        mesh->getMaterial()->getShader()->setMatProperty("model_mat", modelMat->m);

        mesh->draw();

        // Unbind what was previously binded.
        if (mesh->getMaterial()->getTexture()) {
            mesh->getMaterial()->getTexture()->unbind();
        }
        mesh->getMaterial()->getShader()->unbind();
    }

    Object3D **children = object->getChildren();
    for (int i = 0; i < object->getNumChildren(); i++) {
        renderObject(children[i], modelMat);
    }
}

void Renderer::render() {
    Object3D** objects = this->scene->getObjects();
    int numObjects = this->scene->getNumObjects();

    for (int i = 0; i < numObjects; i++) {
        Matrix4 identity = Matrix4::identity();
        renderObject(objects[i], &identity);
    }
}
