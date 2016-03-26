#include "BilliardsBall.h"

BilliardsBall::BilliardsBall(int num) {
    this->ball = ObjLoader::loadObject("resources/models/ball.obj");
    this->ball->scale->setThis(0.013, 0.013, 0.013);
    this->ball->translation->y = 0.013;
    this->ball->updateModelMat();

    this->velocity = new Vector3(0.5, 0, 0);
}

Object3D *BilliardsBall::getObject() {
    return this->ball;
}

void BilliardsBall::update(float dt) {
    this->ball->translation->x += this->velocity->x * dt;
    this->ball->translation->y += this->velocity->y * dt;
    this->ball->translation->z += this->velocity->z * dt;

    this->ball->updateModelMat();
}
