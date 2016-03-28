#include "Object3D.h"

Object3D::Object3D(int maxNumChildren) {
    this->maxNumChildren = maxNumChildren;
    this->numChildren = 0;
    if (maxNumChildren > 0) {
        this->children = new Object3D*[maxNumChildren];
    }
    this->isMesh = false;
    this->isVisible = true;

    this->translation = Vector3(0.0, 0.0, 0.0);
    this->scale = Vector3(1.0, 1.0, 1.0);
    this->rotation = Vector3(0.0, 0.0, 0.0);
    this->quaternion = Quaternion();

    this->modelMat = Matrix4::identity();

    this->matrixMultOrder = MatrixMultOrder::T_R_S;
}

void Object3D::addChildObject(Object3D *object) {
    children[numChildren++] = object;
}

int Object3D::getNumChildren() {
    return numChildren;
}

Object3D **Object3D::getChildren() {
    return children;
}

void Object3D::updateModelMat() {
    Matrix4 translationMat = Matrix4::translation(&this->translation);
    Matrix4 rotationMat;

    Matrix4 rotationMat1 = quaternion.getMatrix();
    Matrix4 rotationMat2 = Matrix4::eulerRotation(&this->rotation);
    rotationMat = Matrix4::multiply(&rotationMat1, &rotationMat2);

    Matrix4 scaleMat = Matrix4::scale(&this->scale);

    if (this->matrixMultOrder == MatrixMultOrder::T_R_S) {
        Matrix4 m1 = Matrix4::multiply(&rotationMat, &scaleMat);
        modelMat = Matrix4::multiply(&translationMat, &m1);
    } else if (this->matrixMultOrder == MatrixMultOrder::R_T_S) {
        Matrix4 m1 = Matrix4::multiply(&translationMat, &scaleMat);
        modelMat = Matrix4::multiply(&rotationMat, &m1);
    }
}

Matrix4 *Object3D::getModelMat() {
    return &modelMat;
}

void Object3D::setMatrixMultOrder(MatrixMultOrder order) {
    this->matrixMultOrder = order;
}

Quaternion *Object3D::getQuaternion() {
    return &quaternion;
}

Vector3 *Object3D::getTranslation() {
    return &translation;
}

Vector3 *Object3D::getScale() {
    return &scale;
}

Vector3 *Object3D::getRotation() {
    return &rotation;
}
