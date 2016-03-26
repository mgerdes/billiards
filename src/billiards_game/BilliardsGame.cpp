#include "BilliardsGame.h"

BilliardsGame::BilliardsGame() {
    this->initScene();    
    this->initCamera();
}

void BilliardsGame::initScene() {
    this->table = ObjLoader::loadObject("resources/models/table.obj");
    this->table->translation->y = -0.26;
    this->table->translation->x = -0.155;
    this->table->updateModelMat();
    this->cueStick = new CueStick();

    this->scene = new Scene(3);
    this->scene->addObject(this->table);
    this->scene->addObject(this->cueStick->getObject());

    for (int i = 0; i < 1; i++) {
        this->balls[i] = new BilliardsBall(i);
        this->scene->addObject(this->balls[i]->getObject());
    }
}

void BilliardsGame::initCamera() {
    this->camera = new Camera(45.0, 1.0, 0.1, 100);

    this->camera->position = new Vector3(1.0, 1.0, 1.0);
    this->camera->lookAt = new Vector3(0.0, 0.0, 0.0);
    this->camera->up = new Vector3(0.0, 1.0, 0.0);

    this->camera->updateViewMatrix();
}

void BilliardsGame::handleKeyInput() {

    if (this->isLeftKeyDown) {
        this->cueStick->decreaseAngle();
    }
    if (this->isRightKeyDown) {
        this->cueStick->increaseAngle();
    }
    if (this->isUpKeyDown) {
        this->cueStick->increaseHitPower();
    }
    if (this->isDownKeyDown) {
        this->cueStick->decreaseHitPower();
    }
    if (this->isWKeyDown) {
    }
    if (this->isSKeyDown) {
    }
    if (this->isAKeyDown) {
    }
    if (this->isDKeyDown) {
    }
    this->cueStick->getObject()->updateModelMat();

    this->camera->position = new Vector3(1.0, 0.5, 0.0); 
    this->camera->position->applyMatrix(Matrix4::eulerRotation(0.0, 0.0, this->cueStick->getAngle() + 3.1415));
    this->camera->updateViewMatrix();
}

void BilliardsGame::handleCollisions() {
    for (int i = 0; i < 1; i++) {
        
    }
}

void BilliardsGame::update(float dt) {
    this->handleKeyInput();
    for (int i = 0; i < 1; i++) {
        //this->balls[i]->update(dt);
    }
    this->handleCollisions();
}

Scene *BilliardsGame::getScene() {
    return this->scene;
}

Camera *BilliardsGame::getCamera() {
    return this->camera;
}
