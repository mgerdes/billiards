#ifndef BILLIARDS_BILLIARDSSTICK_H
#define BILLIARDS_BILLIARDSSTICK_H

#include "ResourceManager.h"
#include "Window.h"

class BilliardsStick {
private:
    static constexpr float stickDelta = -0.7900f;
    static constexpr float angleDelta = 0.01f;
    static constexpr float hitPowerDelta = 0.01f;

public:
    float angle = 0.0f;
    float hitPower = 0.0f;
    float beforeAnimiationHitPower = 0.0f;
    Model* model;

    BilliardsStick();

    void draw(Vector positionOfCueBall);

    void increaseHitPower();
    void decreaseHitPower();

    void increaseAngle();
    void decreaseAngle();
};

#endif //BILLIARDS_BILLIARDSSTICK_H
