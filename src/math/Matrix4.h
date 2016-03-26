#ifndef BILLIARDS_MATRIX4_H
#define BILLIARDS_MATRIX4_H

#include "Vector3.h"

class Matrix4 {
    public:
        /*
         * stored column-major:
         * a e i m
         * b f j n
         * c g k o
         * d h l p
         */
        float m[16];

        Matrix4();

        Matrix4(float m11, float m12, float m13, float m14,
                float m21, float m22, float m23, float m24,
                float m31, float m32, float m33, float m34,
                float m41, float m42, float m43, float m44);

        void zeroOut();

        static Matrix4 *identity();

        static Matrix4 *multiply(Matrix4 *m1, Matrix4 *m2);

        static Matrix4 *translation(float x, float y, float z);
};

#endif 