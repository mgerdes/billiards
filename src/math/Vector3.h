#ifndef BILLIARDS_VECTOR3_H
#define BILLIARDS_VECTOR3_H

#include <math.h>
#include "Matrix4.h"

class Matrix4;

class Vector3 {
    public:
        float x, y, z;

        Vector3();

        Vector3(float x, float y, float z);

        float length();

        void normalizeThis();

        void setThis(float x, float y, float z);

        void setThis(Vector3 *v);

        void lerpThis(Vector3 *v, float t);

        void scaleThis(float scalar);

        void addToThis(float x, float y, float z);

        void addToThis(Vector3 *v);

        void applyMatrix(Matrix4 *m);

        static Vector3 subtract(Vector3 *v1, Vector3 *v2);

        static Vector3 add(Vector3 *v1, Vector3 *v2);

        static Vector3 cross(Vector3 *v1, Vector3 *v2);

        static float dot(Vector3 *v1, Vector3 *v2);

        static float distanceBetween(Vector3 *v1, Vector3 *v2);
};

#endif 
