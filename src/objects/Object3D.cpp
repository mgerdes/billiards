#include "Object3D.h"

Object3D::Object3D(int maxNumChildren, bool isMesh) {
    this->maxNumChildren = maxNumChildren;
    this->numChildren = 0;
    if (maxNumChildren > 0) {
        this->children = new Object3D*[maxNumChildren];
    }
    this->isMesh = isMesh;
    this->isVisible = true;

    this->translation = new Vector3(0.0, 0.0, 0.0);
    this->scale = new Vector3(1.0, 1.0, 1.0);
    this->rotation = new Vector3(0.0, 0.0, 0.0);
    this->quaternion = 0;

    this->modelMat = Matrix4::identity();

    this->matrixMultOrder = MatrixMultOrder::T_R_S;
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

bool Object3D::getIsVisible() {
    return this->isVisible;
}

void Object3D::setIsVisible(bool isVisible) {
    this->isVisible = isVisible;
}

void Object3D::updateModelMat() {
    Matrix4 *translationMat = Matrix4::translation(this->translation);
    Matrix4 *rotationMat;
    if (quaternion) {
        rotationMat = quaternion->getMatrix();
    } else {
        rotationMat = Matrix4::eulerRotation(this->rotation);
    }
    Matrix4 *scaleMat = Matrix4::scale(this->scale);

    if (this->matrixMultOrder == MatrixMultOrder::T_R_S) {
        this->modelMat = Matrix4::multiply(Matrix4::multiply(translationMat, rotationMat), scaleMat);
    } else if (this->matrixMultOrder == MatrixMultOrder::R_T_S) {
        this->modelMat = Matrix4::multiply(Matrix4::multiply(rotationMat, translationMat), scaleMat);
    }
}

Matrix4 *Object3D::getModelMat() {
    return this->modelMat;
}

void Object3D::setMatrixMultOrder(MatrixMultOrder order) {
    this->matrixMultOrder = order;
}

Quaternion *Object3D::getQuaternion() {
    return this->quaternion;
}

void Object3D::setQuaternion(Quaternion *quaternion) {
    this->quaternion = quaternion;
}
