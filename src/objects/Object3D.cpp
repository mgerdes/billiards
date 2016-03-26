#include "Object3D.h"

Object3D::Object3D(int maxNumChildren, bool isMesh) {
    this->maxNumChildren = maxNumChildren;
    this->numChildren = 0;
    if (maxNumChildren > 0) {
        this->children = new Object3D*[maxNumChildren];
    }
    this->isMesh = isMesh;

    this->translation = new Vector3(0.0, 0.0, 0.0);
    this->scale = new Vector3(1.0, 1.0, 1.0);
    this->rotation = new Vector3(0.0, 0.0, 0.0);

    this->modelMat = Matrix4::identity();
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

void Object3D::updateModelMat() {
    Matrix4 *translationMat = Matrix4::translation(this->translation);
    Matrix4 *scaleMat = Matrix4::scale(this->scale);
    Matrix4 *rotationMat = Matrix4::eulerRotation(this->rotation);

    this->modelMat = Matrix4::multiply(
            Matrix4::multiply(translationMat, scaleMat),
            rotationMat);
}

Matrix4 *Object3D::getModelMat() {
    return this->modelMat;
}
