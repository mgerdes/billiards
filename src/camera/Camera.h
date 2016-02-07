#ifndef BILLIARDS_CAMERA_H
#define BILLIARDS_CAMERA_H

#include "Matrix.h"
#include "Vector.h"

class Camera {
public:
    Vector position, center, up;
    Matrix projectionMatrix, viewMatrix;

    void updateProjectionMatrix();

    void updateViewMatrix();

    Camera();

    Camera(Vector position, Vector center, Vector up);
};

#endif //BILLIARDS_CAMERA_H
