#ifndef BILLIARDS_CAMERA_H
#define BILLIARDS_CAMERA_H

#include "Matrix.h"
#include "Vector.h"

class Camera {
private:
    void updateProjectionMatrix();

    void updateViewMatrix();

public:
    Vector position, center, up;
    Matrix projectionMatrix, viewMatrix;

    Camera(Vector position, Vector center, Vector up);
};

#endif //BILLIARDS_CAMERA_H
