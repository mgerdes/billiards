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

    this->ball->getTranslation()->setThis(x, y, z);
    this->ball->getScale()->setThis(0.013, 0.013, 0.013);
    this->ball->getQuaternion()->setThis(1.0, 1.0, 1.0, 1.0);
    this->ball->updateModelMat();

    float vx = (rand() / (float) RAND_MAX) * 2 * 0.500 - 0.500;
    float vz = (rand() / (float) RAND_MAX) * 2 * 0.500 - 0.500;
    this->velocity = new Vector3(vx, 0.0, vz);
}

Object3D *BilliardsBall::getObject() {
    return this->ball;
}

void BilliardsBall::update(float dt) {

    float speed = this->velocity->length();
    if (speed < 0.005) {
        this->velocity->setThis(0.0, 0.0, 0.0);
    } else {
        this->ball->getTranslation()->x += this->velocity->x * dt;
        this->ball->getTranslation()->y += this->velocity->y * dt;
        this->ball->getTranslation()->z += this->velocity->z * dt;

        Vector3 temp = Vector3(*this->velocity);
        temp.normalizeThis();
        Vector3 yAxis = Vector3(0.0, 1.0, 0.0);
        Vector3 rotationVector = Vector3::cross(&temp, &yAxis);

        Quaternion q = Quaternion(25 * dt * speed, &rotationVector);
        q.multiplyThisBy(this->ball->getQuaternion());
        this->ball->getQuaternion()->setThis(&q);

        this->velocity->addToThis(-0.3 * this->velocity->x * dt, 0.0, -0.3 * this->velocity->z * dt);
    }

    this->ball->updateModelMat();
}

Vector3 *BilliardsBall::getVelocity() {
    return this->velocity;
}
