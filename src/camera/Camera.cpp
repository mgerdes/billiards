#include "Camera.h"

Camera::Camera(Vector position, Vector center, Vector up) : position(position),
                                                            center(center),
                                                            up(up) {
    updateProjectionMatrix();
    updateViewMatrix();
}

void Camera::updateViewMatrix() {

}

void Camera::updateProjectionMatrix() {

}
