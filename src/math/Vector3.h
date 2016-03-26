#ifndef BILLIARDS_VECTOR3_H
#define BILLIARDS_VECTOR3_H

#include <math.h>

class Vector3 {
    public:
        float x, y, z;

        Vector3(float x, float y, float z);

        float length();

        void normalizeThis();

        void setThis(float x, float y, float z);

        void scale(float scalar);

        Vector3 *clone();

        static Vector3 *subtract(Vector3 *v1, Vector3 *v2);

        static Vector3 *cross(Vector3 *v1, Vector3 *v2);
};

#endif 
