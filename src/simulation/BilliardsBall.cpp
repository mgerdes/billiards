#include "BilliardsBall.h"

BilliardsBall::BilliardsBall(Vector position, Vector velocity, int ballNumber)
        : position(position),
          velocity(velocity),
          ballNumber(ballNumber),
          boundingCircle(position.x, position.y, radius),
          model(ResourceManager::getModel("billiards_ball")) { }


void BilliardsBall::update() {
    position.x = boundingCircle.x = position.x + velocity.x;
    position.y = boundingCircle.y = position.y + velocity.y;
    double speed = velocity.length();
    angle += 20 * speed;
    if (speed > smallestSpeed) {
        velocity = velocity -  0.01f * velocity;
    } else {
        velocity = Vector(0.0f, 0.0f, 0.0f);
    }
}

void BilliardsBall::draw() {
    Matrix translation = Matrix(Vector(position.x, radius, position.y));
    Matrix scale = Matrix::scaleMatrix(Vector(1.4f, 1.4f, 1.4f));
    Vector rotationAxis = Vector(velocity.x, 0.0f, velocity.y).normalize() ^Vector(0.0f, 1.0f, 0.0f);

    Matrix rotate;
    if (velocity.length() > 0) {
        rotate = Matrix(rotationAxis, angle);
    }

    Matrix modelMat = translation * scale * rotate;

    ResourceManager::getTexture(std::to_string(ballNumber) + ".png")->enable();
    model->draw(ResourceManager::getShader("default"), modelMat);
    ResourceManager::getTexture(std::to_string(ballNumber) + ".png")->disable();
}

