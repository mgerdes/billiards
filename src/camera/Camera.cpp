#include "Camera.h"

static const float ONE_DEG_IN_RAD = (float) ((2.0 * M_PI) / 360.0); // 0.017444444
static const float ONE_RAD_IN_DEG = (float) (360.0 / (2.0 * M_PI)); //57.2957795

Camera::Camera() { 
    updateProjectionMatrix();
    updateViewMatrix();
}

Camera::Camera(Vector position, Vector center, Vector up) : position(position),
                                                            center(center),
                                                            up(up) {
    updateProjectionMatrix();
    updateViewMatrix();
}

//Mat* create_look_at_mat(Vec* cam_pos, Vec* targ_pos, Vec* up) {
void Camera::updateViewMatrix() {
    Matrix p = Matrix(Vector(-1 * position));
    Vector f = (center - position).normalize();
    Vector r = (f ^ up).normalize();
    Vector u = (r ^ f).normalize();

    Matrix ori;
    ori.m[0] = r.x;
    ori.m[4] = r.y;
    ori.m[8] = r.z;
    ori.m[1] = u.x;
    ori.m[5] = u.y;
    ori.m[9] = u.z;
    ori.m[2] = -f.x;
    ori.m[6] = -f.y;
    ori.m[10] = -f.z;

    viewMatrix = ori * p;
}

void Camera::updateProjectionMatrix() {
    // clear projection matrix
    for (int i = 0; i < 16; i++) {
        projectionMatrix.m[i] = 0;
    }

    float fovy = 60;
    float aspect = 1.0;
    float near = 0.1;
    float far = 1000.0;

    float fov_rad = fovy * ONE_DEG_IN_RAD;
    float range = tan(fov_rad / 2.0f) * near;
    float sx = (2.0f * near) / (range * aspect + range * aspect);
    float sy = near / range;
    float sz = -(far + near) / (far - near);
    float pz = -(2.0f * far * near) / (far - near);

    projectionMatrix.m[0] = sx;
    projectionMatrix.m[5] = sy;
    projectionMatrix.m[10] = sz;
    projectionMatrix.m[14] = pz;
    projectionMatrix.m[11] = -1.0f;
}
