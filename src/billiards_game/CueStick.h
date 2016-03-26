#ifndef BILLIARDS_CUE_STICK_H
#define BILLIARDS_CUE_STICK_H

#include "Object3D.h"
#include "ObjLoader.h"

class CueStick {
    private:
        Object3D *object, *cueStick;
        float hitPower, angle;

    public:
        CueStick();

        Object3D *getObject();

        void increaseHitPower();

        void decreaseHitPower();

        void increaseAngle();

        void decreaseAngle();

        float getAngle();
};

#endif
