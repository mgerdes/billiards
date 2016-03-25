#include "Object3D.h"

Object3D::Object3D(int maxNumChildren, bool isMesh) {
    this->maxNumChildren = maxNumChildren;
    this->numChildren = 0;
    this->children = new Object3D*[maxNumChildren];
    this->isMesh = isMesh;
}

void Object3D::addChildObject(Object3D *object) {
    children[numChildren++] = object;
}

int Object3D::getNumChildren() {
    return this->numChildren;
}

Object3D **Object3D::getChildren() {
    return this->children;
}

bool Object3D::getIsMesh() {
    return this->isMesh;
}
