#include "Quaternion.h"

Quaternion::Quaternion() {
    this->w = this->x = this->y = this->z = 1;
    this->normalize();
}

Quaternion::Quaternion(float angle, Vector rotationAxis) {
    this->w = cos(angle / 2.0f);
    float temp = sin(angle / 2.0f);
    this->x = temp * rotationAxis.x;
    this->y = temp * rotationAxis.y;
    this->z = temp * rotationAxis.z;
    this->normalize();
}

Quaternion::Quaternion(float angle, float x, float y, float z) {
    this->w = cos(angle / 2.0f);
    float temp = sin(angle / 2.0f);
    this->x = temp * x;
    this->y = temp * y;
    this->z = temp * z;
    this->normalize();
}

Matrix Quaternion::getMatrix() {
    return Matrix(1.0f - 2.0f * y * y - 2.0f * z * z, 2.0f * x * y + 2.0f * w * z, 2.0f * x * z - 2.0f * w * y, 0.0f,
            2.0f * x * y - 2.0f * w * z, 1.0f - 2.0f * x * x - 2.0f * z * z, 2.0f * y * z + 2.0f * w * x, 0.0f, 
            2.0f * x * z + 2.0f * w * y, 2.0f * y * z - 2.0f * w * x, 1.0f - 2.0f * x * x - 2.0f * y * y, 0.0f, 
            0.0f, 0.0f, 0.0f, 1.0f);
}

void Quaternion::normalize() {
	float mag = sqrt(w*w + x*x + y*y + z*z);

    this->w = this->w / mag;
    this->x = this->x / mag;
    this->y = this->y / mag;
    this->z = this->z / mag;
}

Quaternion operator*(const Quaternion &q1, const Quaternion &q2) {
    Quaternion q = Quaternion();
    q.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
    q.x = q1.w * q2.x + q1.x * q2.w - q1.y * q2.z + q1.z * q2.y;
    q.y = q1.w * q2.y + q1.x * q2.z + q1.y * q2.w - q1.z * q2.x;
    q.z = q1.w * q2.z - q1.x * q2.y + q1.y * q2.x + q1.z * q2.w;
    q.normalize();
    return q;
}
