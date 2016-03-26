#ifndef BILLIARDS_CAMERA_H
#define BILLIARDS_CAMERA_H

#include <math.h>
#include "Matrix4.h"
#include "Vector3.h"

class Camera {
    private:
        float fieldOfView, aspectRatio, near, far;
        Matrix4 *projectionMatrix, *viewMatrix;
    public:
        Vector3 *position, *lookAt, *up;

        Camera(float fieldOfView, float aspectRatio, float near, float far);

        void updateProjectionMatrix();

        void updateViewMatrix();

        Matrix4 *getProjectionMatrix();

        Matrix4 *getViewMatrix();
};

#endif 
