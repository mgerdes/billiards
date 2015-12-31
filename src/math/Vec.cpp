#include "Vec.h"

Vec::Vec(double _x, double _y, double _z) {
    x = _x;
    y = _y;
    z = _z;
}

double Vec::length() {
    return sqrt(*this * *this);
}

Vec Vec::normalize() {
    double l = (*this).length();
    return Vec((*this).x / l, (*this).y / l, (*this).z / l);
}

Vec operator^(const Vec &v1, const Vec &v2) {
    double x = v1.y * v2.z - v1.z * v2.y;
    double y = v1.z * v2.x - v1.x * v2.z;
    double z = v1.x * v2.y - v1.y * v2.x;
    return Vec(x, y, z);
}

double operator*(const Vec &v1, const Vec &v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vec operator*(double s, const Vec &v) {
    return Vec(v.x * s, v.y * s, v.z * s);
}

Vec operator+(const Vec &v1, const Vec &v2) {
    return Vec(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vec operator-(const Vec &v1, const Vec &v2) {
    return Vec(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

bool operator==(const Vec &v1, const Vec &v2) {
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

// For googletest
std::ostream &operator<<(std::ostream &stream, Vec const &v) {
    return stream << "[" << v.x << " , " << v.y << " , " << v.z << "]";
}
