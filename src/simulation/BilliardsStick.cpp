#include "BilliardsStick.h"

BilliardsStick::BilliardsStick()
        : model(ResourceManager::getModel("billiards_stick")) { }

void BilliardsStick::draw(Vector positionOfCueBall) {
    Matrix translation1 = Matrix(Vector(stickDelta - hitPower * 0.3f, 0.0f, 0.0f));
    Vector rotationVector = Vector(0, 1, 0);
    Matrix translation2 = Matrix(Vector(positionOfCueBall.x, 0.032f, positionOfCueBall.y));
    Matrix rotate = Matrix(rotationVector, angle);
    Matrix modelMat = translation2 * rotate * translation1;

    model->draw(ResourceManager::getShader("default"), modelMat);
}

void BilliardsStick::increaseHitPower() {
    if (hitPower < 1.0f) {
        hitPower += hitPowerDelta;
    }
}

void BilliardsStick::decreaseHitPower() {
    if (hitPower > 0.0f) {
        hitPower -= hitPowerDelta;
    }
}

void BilliardsStick::increaseAngle() {
    angle += angleDelta;
}

void BilliardsStick::decreaseAngle() {
    angle -= angleDelta;
}
