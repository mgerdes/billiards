#include "Scene.h"

Scene::Scene(int maxNumMeshes) {
    this->numMeshes = 0;
    this->maxNumMeshes = maxNumMeshes;
    this->meshes = new Mesh*[maxNumMeshes];    
}

Scene::~Scene() {
    delete[] meshes;
}

void Scene::addMesh(Mesh *mesh) {
    this->meshes[this->numMeshes++] = mesh;
}

int Scene::getNumMeshes() {
    return this->numMeshes;
}

Mesh **Scene::getMeshes() {
    return this->meshes;
}

