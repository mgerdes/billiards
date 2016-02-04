#ifndef BILLIARDS_BILLIARDSBALL_H
#define BILLIARDS_BILLIARDSBALL_H

#include "ResourceManager.h"
#include "Quaternion.h"

class BilliardsBall {
    Quaternion rotationQuaternion;
public:
    static constexpr float radius = 0.0300f;
    static constexpr float smallestSpeed = 0.0001f;
    int ballNumber;
    Vector position, velocity;
    CircleBoundingObject boundingCircle;

    Model* model;

    BilliardsBall(Vector position, Vector velocity, int ballNumber);

    void draw();

    void update();
};

#endif //BILLIARDS_BILLIARDSBALL_H
