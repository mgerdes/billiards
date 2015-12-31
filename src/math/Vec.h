#ifndef BILLIARDS_VEC_H
#define BILLIARDS_VEC_H

#include <math.h>
#include <iostream>

class Vec {
public:
    double x, y, z;

    Vec(double _x, double _y, double _z);

    Vec normalize();

    double length();
};

Vec operator^(const Vec &v1, const Vec &v2);

Vec operator+(const Vec &v1, const Vec &v2);

Vec operator-(const Vec &v1, const Vec &v2);

double operator*(const Vec &v1, const Vec &v2);

Vec operator*(double s, const Vec &v);

bool operator==(const Vec &v1, const Vec &v2);

// for googletest
std::ostream &operator<<(std::ostream &stream, Vec const &v);

#endif //BILLIARDS_VEC_H
