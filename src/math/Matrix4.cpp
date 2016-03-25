#include "Matrix4.h"

Matrix4::Matrix4() { }

Matrix4::Matrix4(float m11, float m12, float m13, float m14,
               float m21, float m22, float m23, float m24,
               float m31, float m32, float m33, float m34,
               float m41, float m42, float m43, float m44) {
    m[0] = m11;
    m[1] = m21;
    m[2] = m31;
    m[3] = m41;
    m[4] = m12;
    m[5] = m22;
    m[6] = m32;
    m[7] = m42;
    m[8] = m13;
    m[9] = m23;
    m[10] = m33;
    m[11] = m43;
    m[12] = m14;
    m[13] = m24;
    m[14] = m34;
    m[15] = m44;
}

void Matrix4::clear() {
    for (int i = 0; i < 16; i++) {
        m[i] = 0;
    }
}

Matrix4 *Matrix4::multiply(Matrix4 *m1, Matrix4 *m2) {
    Matrix4 *m = new Matrix4();
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            float sum = 0;
            for (int i = 0; i < 4; i++) {
                sum += m1->m[row + i * 4] * m2->m[i + col * 4];
            }
            m->m[row + col * 4] = sum;
        }
    }
    return m;
}

Matrix4 *Matrix4::translation(Vector3 *translation) {
    return new Matrix4(
            1, 0, 0, translation->x,
            0, 1, 0, translation->y,
            0, 0, 1, translation->z,
            0, 0, 0, 1);
}

