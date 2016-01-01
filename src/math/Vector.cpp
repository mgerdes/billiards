#include <Util.h>
#include "Vector.h"

Vector::Vector(float x, float y, float z) : x(x), y(y), z(z) { }

float Vector::length() const {
    return sqrt(*this * *this);
}

Vector Vector::normalize() const {
    float l = (*this).length();
    return Vector((*this).x / l, (*this).y / l, (*this).z / l);
}

Vector Vector::rotate(Vector &axis, float theta) const {
    return Matrix(axis, theta) * *this;
}

Vector operator^(const Vector &v1, const Vector &v2) {
    float x = v1.y * v2.z - v1.z * v2.y;
    float y = v1.z * v2.x - v1.x * v2.z;
    float z = v1.x * v2.y - v1.y * v2.x;
    return Vector(x, y, z);
}

float operator*(const Vector &v1, const Vector &v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector operator*(float s, const Vector &v) {
    return Vector(v.x * s, v.y * s, v.z * s);
}

Vector operator+(const Vector &v1, const Vector &v2) {
    return Vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vector operator-(const Vector &v1, const Vector &v2) {
    return Vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

bool operator==(const Vector &v1, const Vector &v2) {
    return std::abs(v1.x - v2.x) < Util::EPSILON
           && std::abs(v1.y - v2.y) < Util::EPSILON
           && std::abs(v1.z - v2.z) < Util::EPSILON;
}

Vector operator*(const Matrix &m, const Vector &v) {
    float x = m.m[0] * v.x + m.m[4] * v.y + m.m[8] * v.z + m.m[12];
    float y = m.m[1] * v.x + m.m[5] * v.y + m.m[9] * v.z + m.m[13];
    float z = m.m[2] * v.x + m.m[6] * v.y + m.m[10] * v.z + m.m[14];
    return Vector(x, y, z);
}

// For googletest
std::ostream &operator<<(std::ostream &stream, Vector const &v) {
    return stream << "[" << v.x << " , " << v.y << " , " << v.z << "]";
}
