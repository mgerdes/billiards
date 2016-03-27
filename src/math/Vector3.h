#ifndef BILLIARDS_VECTOR3_H
#define BILLIARDS_VECTOR3_H

#include <math.h>
#include "Matrix4.h"

class Matrix4;

class Vector3 {
    public:
        float x, y, z;

        Vector3(float x, float y, float z);

        float length();

        void normalizeThis();

        void setThis(float x, float y, float z);

        void scaleThis(float scalar);

        void addToThis(float x, float y, float z);

        void applyMatrix(Matrix4 *m);

        Vector3 *clone();

        static Vector3 *subtract(Vector3 *v1, Vector3 *v2);

        static Vector3 *cross(Vector3 *v1, Vector3 *v2);

        static float dot(Vector3 *v1, Vector3 *v2);

        static float distanceSqrdBetween(Vector3 *v1, Vector3 *v2);
};

#endif 
