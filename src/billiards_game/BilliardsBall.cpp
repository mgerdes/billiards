#include "BilliardsBall.h"

BilliardsBall::BilliardsBall(int num) {
    this->ball = ObjLoader::loadObject("resources/models/ball.obj");
    this->ball->scale->setThis(0.013, 0.013, 0.013);
    this->ball->translation->x = 0.3;
    this->ball->translation->y = 0.013;
    this->ball->updateModelMat();
    this->ball->setQuaternion(new Quaternion());

    Texture *texture = ResourceManager::getTexture("resources/textures/1.png");
    Mesh *mesh = (Mesh*) this->ball->getChildren()[0];
    mesh->getMaterial()->setTexture(texture);

    this->velocity = new Vector3(0.1, 0.0, 0.1);
}

Object3D *BilliardsBall::getObject() {
    return this->ball;
}

void BilliardsBall::update(float dt) {
    this->ball->translation->x += this->velocity->x * dt;
    this->ball->translation->y += this->velocity->y * dt;
    this->ball->translation->z += this->velocity->z * dt;

    Vector3 *temp = this->velocity->clone();
    temp->normalizeThis();
    Vector3 yAxis = Vector3(0.0, 1.0, 0.0);
    Vector3 *rotationVector = Vector3::cross(temp, &yAxis);

    Quaternion *q = new Quaternion(2.5 * dt, rotationVector);
    q->multiplyThisBy(this->ball->getQuaternion());
    this->ball->setQuaternion(q);

    this->ball->updateModelMat();
}

Vector3 *BilliardsBall::getVelocity() {
    return this->velocity;
}
