#include "CueStick.h"

CueStick::CueStick() {
    this->hitPower = 0.0;
    this->angle = 0;

    this->object = new Object3D(1);
    this->object->getTranslation()->y = 0.10;
    this->object->getTranslation()->x = -0.535;
    this->object->getRotation()->y = -0.175;
    this->object->getScale()->setThis(0.7, 0.7, 0.7);
    this->object->updateModelMat();

    this->cueStick = ObjLoader::loadObject("resources/models/cue.obj");
    this->object->addChildObject(this->cueStick);
}

Object3D *CueStick::getObject() {
    return this->object;
}

void CueStick::increaseHitPower() {
    if (this->hitPower < 1.0) {
        this->hitPower += 0.01;
    }
    this->object->getTranslation()->x = -0.535 - hitPower * 0.3;
    this->object->updateModelMat();
}

void CueStick::decreaseHitPower() {
    if (this->hitPower > 0.0) {
        this->hitPower -= 0.01;
    }
    this->object->getTranslation()->x = -0.535 - hitPower * 0.3;
    this->object->updateModelMat();
}

void CueStick::increaseAngle() {
    this->angle += 0.01;
    this->cueStick->getRotation()->z = angle;
    this->cueStick->updateModelMat();
}

void CueStick::decreaseAngle() {
    this->angle -= 0.01;
    this->cueStick->getRotation()->z = angle;
    this->cueStick->updateModelMat();
}

float CueStick::getAngle() {
    return this->angle;
}

float CueStick::getHitPower() {
    return this->hitPower;
}
