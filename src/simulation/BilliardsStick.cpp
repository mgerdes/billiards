#include "BilliardsStick.h"

BilliardsStick::BilliardsStick()
        : model(ResourceManager::getModel("billiards_stick")) { }

void BilliardsStick::draw(Vector positionOfCueBall) {
    Matrix translation1 = Matrix(Vector(stickDelta - hitPower * 0.3f, 0.0f, 0.0f));
    Vector rotationVector = Vector(0, 1, 0);
    Matrix translation2 = Matrix(Vector(positionOfCueBall.x, 0.032f, positionOfCueBall.y));
    Matrix rotate = Matrix(rotationVector, angle);
    Matrix modelMat = translation2 * rotate * translation1;

    model->draw(ResourceManager::getShader("default"), modelMat);
}

void BilliardsStick::update(Window &window) {
    if (glfwGetKey(window.glfwWindow, GLFW_KEY_LEFT)) {
        angle += angleDelta;
    }
    if (glfwGetKey(window.glfwWindow, GLFW_KEY_RIGHT)) {
        angle -= angleDelta;
    }
    if (glfwGetKey(window.glfwWindow, GLFW_KEY_UP)) {
        if (hitPower < 1.0f) {
            hitPower += hitPowerDelta;
        }
    }
    if (glfwGetKey(window.glfwWindow, GLFW_KEY_DOWN)) {
        if (hitPower > 0.0f) {
            hitPower -= hitPowerDelta;
        }
    }
}

