#include "Vector3.h"

Vector3::Vector3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3 *Vector3::clone() {
    return new Vector3(this->x, this->y, this->z);
}

void Vector3::scale(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
}

float Vector3::length() {
    return sqrt(x * x + y * y + z * z);
}

void Vector3::normalize() {
    float l = this->length();
    if (l != 0) {
        x /= l;
        y /= l;
        z /= l;
    }
}

Vector3 *Vector3::subtract(Vector3 *v1, Vector3 *v2) {
    float x = v1->x - v2->x;
    float y = v1->y - v2->y;
    float z = v1->z - v2->z;
    return new Vector3(x, y, z);
}

Vector3 *Vector3::cross(Vector3 *v1, Vector3 *v2) {
    float x = v1->y * v2->z - v1->z * v2->y;
    float y = v1->z * v2->x - v1->x * v2->z;
    float z = v1->x * v2->y - v1->y * v2->x;
    return new Vector3(x, y, z);
}
