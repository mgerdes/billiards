#ifndef BILLIARDS_QUATERNION_H
#define BILLIARDS_QUATERNION_H

#include <math.h>
#include "Matrix.h"

class Quaternion {
    public:
        float w, x, y, z;

        Quaternion();

        Quaternion(float angle, Vector rotationAxis);

        Quaternion(float angle, float x, float y, float z);

        Matrix getMatrix();

        void normalize();
};

Quaternion operator*(const Quaternion &q1, const Quaternion &q2);

#endif //BILLIARDS_QUATERNION_H
