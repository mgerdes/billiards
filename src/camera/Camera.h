#ifndef BILLIARDS_CAMERA_H
#define BILLIARDS_CAMERA_H

#include <math.h>
#include "Matrix4.h"
#include "Vector3.h"

class Camera {
    private:
        float fieldOfView, aspectRatio, near, far;
        Vector3 *position, *lookAt, *up;
        Matrix4 *projectionMatrix, *viewMatrix;
    public:
        Camera(float fieldOfView, float aspectRatio, float near, float far);

        void updateProjectionMatrix();

        void updateViewMatrix();
};

#endif 
