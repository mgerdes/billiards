#include "BilliardsBall.h"

BilliardsBall::BilliardsBall(int num) {
    this->ball = ObjLoader::loadObject("resources/models/ball.obj");

    std::string textureFileName = "resources/textures/" + std::to_string(num) + ".png"; 
    Texture *texture = ResourceManager::getTexture(textureFileName.c_str());
    Mesh *mesh = (Mesh*) this->ball->getChildren()[0];
    mesh->getMaterial()->setTexture(texture);

    float x = (rand() / (float) RAND_MAX) * 2 * 0.400 - 0.400;
    float y = 0.013;
    float z = (rand() / (float) RAND_MAX) * 2 * 0.120 - 0.120;

    this->ball->translation->setThis(x, y, z);
    this->ball->scale->setThis(0.013, 0.013, 0.013);
    this->ball->setQuaternion(new Quaternion());
    this->ball->updateModelMat();

    this->velocity = new Vector3(0.2, 0.0, 0.2);
}

Object3D *BilliardsBall::getObject() {
    return this->ball;
}

void BilliardsBall::update(float dt) {

    float speed = this->velocity->length();
    if (speed < 0.005) {
        this->velocity->setThis(0.0, 0.0, 0.0);
    } else {
        this->ball->translation->x += this->velocity->x * dt;
        this->ball->translation->y += this->velocity->y * dt;
        this->ball->translation->z += this->velocity->z * dt;

        Vector3 *temp = this->velocity->clone();
        temp->normalizeThis();
        Vector3 yAxis = Vector3(0.0, 1.0, 0.0);
        Vector3 *rotationVector = Vector3::cross(temp, &yAxis);

        Quaternion *q = new Quaternion(25 * dt * speed, rotationVector);
        q->multiplyThisBy(this->ball->getQuaternion());
        this->ball->setQuaternion(q);

        this->velocity->addToThis(-0.3 * this->velocity->x * dt, 0.0, -0.3 * this->velocity->z * dt);
    }

    this->ball->updateModelMat();
}

Vector3 *BilliardsBall::getVelocity() {
    return this->velocity;
}
