#ifndef BILLIARDS_VEC_H
#define BILLIARDS_VEC_H

#include <iostream>
#include <cmath>
#include "Matrix.h"

class Matrix;

class Vector {
public:
    static Vector xAxis, yAxis, zAxis;
    float x, y, z;

    Vector();

    Vector(float x, float y, float z);

    Vector normalize() const;

    float length() const;

    Vector rotate(Vector &axis, float theta) const;
};

Vector operator^(const Vector &v1, const Vector &v2);

Vector operator+(const Vector &v1, const Vector &v2);

Vector operator-(const Vector &v1, const Vector &v2);

float operator*(const Vector &v1, const Vector &v2);

Vector operator*(float s, const Vector &v);

bool operator==(const Vector &v1, const Vector &v2);

Vector operator*(const Matrix &m, const Vector &v);

// for googletest
std::ostream &operator<<(std::ostream &stream, Vector const &v);

#endif //BILLIARDS_VEC_H
