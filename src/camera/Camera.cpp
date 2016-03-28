#include "Camera.h"

static const float ONE_DEG_IN_RAD = 0.01744444; 
static const float ONE_RAD_IN_DEG = 57.2957795; 

Camera::Camera(float fieldOfView, float aspectRatio, float near, float far) {
    this->fieldOfView = fieldOfView;
    this->aspectRatio = aspectRatio;
    this->near = near;
    this->far = far;

    this->position = Vector3(1.2, 1.2, 1.2);
    this->lookAt = Vector3(0.0, 0.0, 0.0);
    this->up = Vector3(0.0, 1.0, 0.0);

    this->viewMatrix = Matrix4();
    this->projectionMatrix = Matrix4();

    this->updateViewMatrix();
    this->updateProjectionMatrix();
}

void Camera::updateViewMatrix() {
    Matrix4 p = Matrix4::translation(-position.x, -position.y, -position.z); 

    Vector3 f = Vector3::subtract(&lookAt, &position);
    f.normalizeThis();

    Vector3 r = Vector3::cross(&f, &up);
    r.normalizeThis();

    Vector3 u = Vector3::cross(&r, &f);
    u.normalizeThis();

    Matrix4 ori = Matrix4::identity();
    ori.m[0] = r.x;
    ori.m[4] = r.y;
    ori.m[8] = r.z;
    ori.m[1] = u.x;
    ori.m[5] = u.y;
    ori.m[9] = u.z;
    ori.m[2] = -f.x;
    ori.m[6] = -f.y;
    ori.m[10] = -f.z;

    viewMatrix = Matrix4::multiply(&ori, &p);
}

void Camera::updateProjectionMatrix() {
    projectionMatrix.zeroOut();

    float fieldOfViewRadians = fieldOfView * ONE_DEG_IN_RAD;
    float range = tan(fieldOfViewRadians / 2.0f) * near;
    float sx = (2.0f * near) / (range * aspectRatio + range * aspectRatio);
    float sy = near / range;
    float sz = -(far + near) / (far - near);
    float pz = -(2.0f * far * near) / (far - near);

    projectionMatrix.m[0] = sx;
    projectionMatrix.m[5] = sy;
    projectionMatrix.m[10] = sz;
    projectionMatrix.m[14] = pz;
    projectionMatrix.m[11] = -1.0f;
}

Matrix4 *Camera::getProjectionMatrix() {
    return &projectionMatrix;
}

Matrix4 *Camera::getViewMatrix() {
    return &viewMatrix;
}

Vector3 *Camera::getPosition() {
    return &position;
}

Vector3 *Camera::getLookAt() {
    return &lookAt;
}

Vector3 *Camera::getUp() {
    return &up;
}
