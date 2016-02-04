#ifndef BILLIARDS_MATRIX_H
#define BILLIARDS_MATRIX_H

#include <cmath>
#include <iostream>
#include "Vector.h"
#include "Util.h"

class Vector;

class Matrix {
public:
    float m[16];

    /*
     * stored column-major:
     * a e i m
     * b f j n
     * c g k o
     * d h l p
     */
    Matrix();

    Matrix(float m11, float m12, float m13, float m14,
           float m21, float m22, float m23, float m24,
           float m31, float m32, float m33, float m34,
           float m41, float m42, float m43, float m44);

    Matrix(float scale);

    Matrix(const Vector &rotationAxis, float theta);

    Matrix(const Vector &translationVector);

    static Matrix scaleMatrix(const Vector &scaleVector);

    void print();
};


Matrix operator*(const Matrix &m1, const Matrix &m2);

bool operator==(const Matrix &m1, const Matrix &m2);

// For googletest
std::ostream &operator<<(std::ostream &stream, Matrix const &v);

#endif //BILLIARDS_MATRIX_H
