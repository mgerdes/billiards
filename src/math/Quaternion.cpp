#include "Quaternion.h"

Quaternion::Quaternion() {
    w = x = y = z = 0;
    normalizeThis();
}

Quaternion::Quaternion(float angle, Vector3 *rotationAxis) {
    this->w = cos(angle / 2.0);
    float temp = sin(angle / 2.0);
    this->x = temp * rotationAxis->x;
    this->y = temp * rotationAxis->y;
    this->z = temp * rotationAxis->z;
    normalizeThis();
}

Quaternion::Quaternion(float angle, float x, float y, float z) {
    this->w = cos(angle / 2.0);
    float temp = sin(angle / 2.0);
    this->x = temp * x;
    this->y = temp * y;
    this->z = temp * z;
    normalizeThis();
}

Matrix4 Quaternion::getMatrix() {
    return Matrix4(1.0 - 2.0 * y * y - 2.0 * z * z, 2.0 * x * y + 2.0 * w * z, 2.0 * x * z - 2.0 * w * y, 0.0,
            2.0 * x * y - 2.0 * w * z, 1.0 - 2.0 * x * x - 2.0 * z * z, 2.0 * y * z + 2.0 * w * x, 0.0, 
            2.0 * x * z + 2.0 * w * y, 2.0 * y * z - 2.0 * w * x, 1.0 - 2.0 * x * x - 2.0 * y * y, 0.0, 
            0.0, 0.0, 0.0, 1.0);
}

void Quaternion::normalizeThis() {
    float mag = sqrt(w*w + x*x + y*y + z*z);

    if (mag == 0) {
        return;
    }

    setThis(this->w/mag, this->x/mag, this->y/mag, this->z/mag);
}

void Quaternion::multiplyThisBy(Quaternion *q) {
    float w = this->w * q->w - this->x * q->x - this->y * q->y - this->z * q->z;
    float x = this->w * q->x + this->x * q->w - this->y * q->z + this->z * q->y;
    float y = this->w * q->y + this->x * q->z + this->y * q->w - this->z * q->x;
    float z = this->w * q->z - this->x * q->y + this->y * q->x + this->z * q->w;
    setThis(w, x, y, z);
    normalizeThis();
}

void Quaternion::setThis(Quaternion *q) {
    this->setThis(q->w, q->x, q->y, q->z);
}

void Quaternion::setThis(float w, float x, float y, float z) {
    this->w = w;
    this->x = x;
    this->y = y;
    this->z = z;
}
