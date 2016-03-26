#include "BilliardsGame.h"

BilliardsGame::BilliardsGame() {
    this->initScene();    
    this->initCamera();
}

void BilliardsGame::initScene() {
    this->table = ObjLoader::loadObject("resources/models/table.obj");
    this->cueStick = new CueStick();

    this->scene = new Scene(2);
    this->scene->addObject(this->table);
    this->scene->addObject(this->cueStick->getObject());
}

void BilliardsGame::initCamera() {
    this->camera = new Camera(45.0, 1.0, 0.1, 100);
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
}

void BilliardsGame::update(float dt) {
    this->handleKeyInput();
}

Scene *BilliardsGame::getScene() {
    return this->scene;
}

Camera *BilliardsGame::getCamera() {
    return this->camera;
}
