#include "Matrix.h"

Matrix::Matrix(float m11, float m12, float m13, float m14,
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

Matrix::Matrix() : Matrix(1, 0, 0, 0,
                          0, 1, 0, 0,
                          0, 0, 1, 0,
                          0, 0, 0, 1) { }

Matrix::Matrix(const Vector &rotationAxis, float theta) {
    float c = cos(theta);
    float s = sin(theta);
    float x1 = c + rotationAxis.x * rotationAxis.x * (1 - c);
    float x2 = rotationAxis.x * rotationAxis.y * (1 - c) - rotationAxis.z * s;
    float x3 = rotationAxis.x * rotationAxis.z * (1 - c) + rotationAxis.y * s;
    float y1 = rotationAxis.y * rotationAxis.x * (1 - c) + rotationAxis.z * s;
    float y2 = c + rotationAxis.y * rotationAxis.y * (1 - c);
    float y3 = rotationAxis.y * rotationAxis.z * (1 - c) - rotationAxis.x * s;
    float z1 = rotationAxis.z * rotationAxis.x * (1 - c) - rotationAxis.y * s;
    float z2 = rotationAxis.z * rotationAxis.y * (1 - c) + rotationAxis.x * s;
    float z3 = c + rotationAxis.z * rotationAxis.z * (1 - c);
    *this = Matrix(x1, y1, z1, 0,
                   x2, y2, z2, 0,
                   x3, y3, z3, 0,
                   0, 0, 0, 1);
}

Matrix::Matrix(float scale) : Matrix(scale, 0.0, 0.0, 0.0,
                                     0.0, scale, 0.0, 0.0,
                                     0.0, 0.0, scale, 0.0,
                                     0.0, 0.0, 0.0, 1.0) { }

Matrix::Matrix(const Vector &translationVector) : Matrix(1.0, 0.0, 0.0, translationVector.x,
                                                         0.0, 1.0, 0.0, translationVector.y,
                                                         0.0, 0.0, 1.0, translationVector.z,
                                                         0.0, 0.0, 0.0, 1.0) { }

Matrix Matrix::scaleMatrix(const Vector &scaleVector) {
    return Matrix(scaleVector.x, 0.0, 0.0, 0.0,
                  0.0, scaleVector.y, 0.0, 0.0,
                  0.0, 0.0, scaleVector.z, 0.0,
                  0.0, 0.0, 0.0, 1.0);
}

Matrix operator*(const Matrix &m1, const Matrix &m2) {
    Matrix m;
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            float sum = 0;
            for (int i = 0; i < 4; i++) {
                sum += m1.m[row + i * 4] * m2.m[i + col * 4];
            }
            m.m[row + col * 4] = sum;
        }
    }
    return Matrix(m.m[0], m.m[4], m.m[8], m.m[12],
                  m.m[1], m.m[5], m.m[9], m.m[13],
                  m.m[2], m.m[6], m.m[10], m.m[14],
                  m.m[3], m.m[7], m.m[11], m.m[15]);
}

bool operator==(const Matrix &m1, const Matrix &m2) {
    for (int i = 0; i < 16; i++) {
        if (std::abs(m1.m[i] - m2.m[i]) > Util::EPSILON) {
            return false;
        }
    }
    return true;
}

std::ostream &operator<<(std::ostream &stream, Matrix const &m) {
    return stream << "\n"
           << "[" << m.m[0] << ", " << m.m[4] << ", " << m.m[8] << ", " << m.m[12] << "]\n"
           << "[" << m.m[1] << ", " << m.m[5] << ", " << m.m[9] << ", " << m.m[13] << "]\n"
           << "[" << m.m[2] << ", " << m.m[6] << ", " << m.m[10] << ", " << m.m[14] << "]\n"
           << "[" << m.m[3] << ", " << m.m[7] << ", " << m.m[11] << ", " << m.m[15] << "]";
}

void Matrix::print() {
    printf("\n");
    printf("[%f, %f, %f, %f]\n", m[0], m[4], m[8], m[12]);
    printf("[%f, %f, %f, %f]\n", m[1], m[5], m[9], m[13]);
    printf("[%f, %f, %f, %f]\n", m[2], m[6], m[10], m[14]);
    printf("[%f, %f, %f, %f]\n", m[3], m[7], m[11], m[15]);
}

