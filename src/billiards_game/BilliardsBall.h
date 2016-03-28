#ifndef BILLIARDS_BALL_H
#define BILLIARDS_BALL_H

#include "Object3D.h"
#include "ObjLoader.h"
#include "ResourceManager.h"

class BilliardsBall {
    private:
        Object3D *ball;

        Vector3 velocity;
    public:
        BilliardsBall(int num);

        Object3D *getObject();

        void update(float dt);

        Vector3 *getVelocity();
};

#endif
