#include "Scene.h"

Scene::Scene(int maxNumObjects) {
    this->numObjects = 0;
    this->maxNumObjects = maxNumObjects;
    this->objects = new Object3D*[maxNumObjects];    
}

void Scene::addObject(Object3D *object) {
    this->objects[this->numObjects++] = object;
}

int Scene::getNumObjects() {
    return this->numObjects;
}

Object3D **Scene::getObjects() {
    return this->objects;
}
