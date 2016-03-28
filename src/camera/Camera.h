#ifndef BILLIARDS_CAMERA_H
#define BILLIARDS_CAMERA_H

#include <math.h>
#include "Matrix4.h"
#include "Vector3.h"

class Camera {
    private:
        float fieldOfView, aspectRatio, near, far;
        Matrix4 projectionMatrix, viewMatrix;
        Vector3 position, lookAt, up;
    public:
        Camera(float fieldOfView, float aspectRatio, float near, float far);

        void updateProjectionMatrix();

        void updateViewMatrix();

        Matrix4 *getProjectionMatrix();

        Matrix4 *getViewMatrix();

        Vector3 *getPosition();

        Vector3 *getLookAt();

        Vector3 *getUp();
};

#endif 
