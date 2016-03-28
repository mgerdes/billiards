#include "Vector3.h"

Vector3::Vector3() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vector3::Vector3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector3::scaleThis(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
}

float Vector3::length() {
    return sqrt(x * x + y * y + z * z);
}

void Vector3::setThis(Vector3 *v) {
    this->setThis(v->x, v->y, v->z);
}

void Vector3::setThis(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector3::normalizeThis() {
    float l = this->length();
    if (l != 0) {
        x /= l;
        y /= l;
        z /= l;
    }
}

Vector3 Vector3::subtract(Vector3 *v1, Vector3 *v2) {
    float x = v1->x - v2->x;
    float y = v1->y - v2->y;
    float z = v1->z - v2->z;
    return Vector3(x, y, z);
}

Vector3 Vector3::add(Vector3 *v1, Vector3 *v2) {
    float x = v1->x + v2->x;
    float y = v1->y + v2->y;
    float z = v1->z + v2->z;
    return Vector3(x, y, z);
}

Vector3 Vector3::cross(Vector3 *v1, Vector3 *v2) {
    float x = v1->y * v2->z - v1->z * v2->y;
    float y = v1->z * v2->x - v1->x * v2->z;
    float z = v1->x * v2->y - v1->y * v2->x;
    return Vector3(x, y, z);
}

void Vector3::applyMatrix(Matrix4 *m) {
    float x = m->m[0] * this->x + m->m[4] * this->y + m->m[8] * this->z + m->m[12];
    float y = m->m[1] * this->x + m->m[5] * this->y + m->m[9] * this->z + m->m[13];
    float z = m->m[2] * this->x + m->m[6] * this->y + m->m[10] * this->z + m->m[14];
    this->setThis(x, y, z);
}

float Vector3::distanceBetween(Vector3 *v1, Vector3 *v2) {
    float a = v1->x - v2->x;
    float b = v1->y - v2->y;
    float c = v1->z - v2->z;
    return sqrt(a*a + b*b + c*c);   
}

float Vector3::dot(Vector3 *v1, Vector3* v2) {
    return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

void Vector3::addToThis(Vector3 *v) {
    this->addToThis(v->x, v->y, v->z);
}

void Vector3::addToThis(float x, float y, float z) {
    this->x += x;
    this->y += y;
    this->z += z;
}
