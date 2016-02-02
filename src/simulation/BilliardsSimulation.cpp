#include "BilliardsSimulation.h"

BilliardsSimulation::BilliardsSimulation(Window &window)
        : window(window),
          camera(Vector(2.1, 2, 2.1), Vector(0, 0, 0), Vector(0, 1, 0)),
          table(RectangleBoundingObject(tableY, tableY, tableWidth, tableHeight)) {
    Light light = Light(Vector(0, 4, 0), Vector(0.1, 0.1, 0.1), Vector(0.3, 0.3, 0.3), Vector(0.0, 0.0, 0.0));

    ResourceManager::getShader("default")->setLightProperty(light);
    ResourceManager::getShader("default")->setMatProperty("proj_mat", camera.projectionMatrix.m);
    ResourceManager::getShader("default")->setMatProperty("view_mat", camera.viewMatrix.m);

    ResourceManager::getShader("bounding_object")->setMatProperty("proj_mat", camera.projectionMatrix.m);
    ResourceManager::getShader("bounding_object")->setMatProperty("view_mat", camera.viewMatrix.m);

    float tableTopX = tableX - (tableWidth / 2.0f);
    float tableTopY = tableY - (tableHeight / 2.0f);

    pockets.push_back(BilliardsPocket(CircleBoundingObject(tableTopX + cornerHoleDeltaX,
                                                           tableTopY + cornerHoleDeltaY,
                                                           pocketRadius)));
    pockets.push_back(BilliardsPocket(CircleBoundingObject(tableTopX + tableWidth - cornerHoleDeltaX,
                                                           tableTopY + cornerHoleDeltaY,
                                                           pocketRadius)));
    pockets.push_back(BilliardsPocket(CircleBoundingObject(tableTopX + cornerHoleDeltaX,
                                                           tableTopY + tableHeight - cornerHoleDeltaY,
                                                           pocketRadius)));
    pockets.push_back(BilliardsPocket(CircleBoundingObject(tableTopX + tableWidth - cornerHoleDeltaX,
                                                           tableTopY + tableHeight - cornerHoleDeltaY,
                                                           pocketRadius)));
    pockets.push_back(BilliardsPocket(CircleBoundingObject(tableTopX + middleHoleDeltaX,
                                                           tableTopY + (tableHeight / 2.0f),
                                                           pocketRadius)));
    pockets.push_back(BilliardsPocket(CircleBoundingObject(tableTopX + tableWidth - middleHoleDeltaX,
                                                           tableTopY + (tableHeight / 2.0f),
                                                           pocketRadius)));

    balls.push_back(BilliardsBall(Vector(0.4f, -0.1f, 0.0f), Vector(0.008f, 0.008f, 0.0f), 0));
    balls.push_back(BilliardsBall(Vector(0.0f, 0.0f, 0.0f), Vector(0.008f, 0.008f, 0.0f), 1));
    balls.push_back(BilliardsBall(Vector(0.1f, 0.0f, 0.0f), Vector(0.008f, 0.008f, 0.0f), 2));
    balls.push_back(BilliardsBall(Vector(0.2f, 0.0f, 0.0f), Vector(0.008f, 0.008f, 0.0f), 3));
    balls.push_back(BilliardsBall(Vector(0.3f, 0.0f, 0.0f), Vector(0.008f, 0.008f, 0.0f), 4));
    balls.push_back(BilliardsBall(Vector(0.4f, 0.0f, 0.0f), Vector(0.008f, 0.008f, 0.0f), 5));
    balls.push_back(BilliardsBall(Vector(-0.1f, 0.0f, 0.0f), Vector(0.008f, 0.008f, 0.0f), 6));
    balls.push_back(BilliardsBall(Vector(-0.2f, 0.0f, 0.0f), Vector(0.008f, 0.008f, 0.0f), 7));
    balls.push_back(BilliardsBall(Vector(-0.2f, 0.0f, 0.0f), Vector(0.008f, 0.008f, 0.0f), 8));
    balls.push_back(BilliardsBall(Vector(-0.3f, 0.0f, 0.0f), Vector(0.008f, 0.008f, 0.0f), 9));
    balls.push_back(BilliardsBall(Vector(-0.4f, 0.0f, 0.0f), Vector(0.008f, 0.008f, 0.0f), 10));
    balls.push_back(BilliardsBall(Vector(0.0f, 0.1f, 0.0f), Vector(0.008f, 0.008f, 0.0f), 11));
    balls.push_back(BilliardsBall(Vector(0.1f, 0.1f, 0.0f), Vector(0.008f, 0.008f, 0.0f), 12));
    balls.push_back(BilliardsBall(Vector(0.2f, 0.1f, 0.0f), Vector(0.008f, 0.008f, 0.0f), 13));
    balls.push_back(BilliardsBall(Vector(0.3f, 0.1f, 0.0f), Vector(0.008f, 0.008f, 0.0f), 14));
    balls.push_back(BilliardsBall(Vector(0.4f, 0.1f, 0.0f), Vector(0.008f, 0.008f, 0.0f), 15));
}

bool BilliardsSimulation::noBallsMoving() {
    for (int i = 0; i < balls.size(); i++) {
        double speed = balls[i].velocity.length();
        if (speed > BilliardsBall::smallestSpeed) {
            return false;
        }
    }
    return true;
}

bool BilliardsSimulation::noBallsColliding() {
    for (int i = 0; i < balls.size(); i++) {
        for (int j = i + 1; j < balls.size(); j++) {
            BilliardsBall &ball1 = balls[i];
            BilliardsBall &ball2 = balls[j];

            double x1 = ball1.position.x;
            double x2 = ball2.position.x;
            double y1 = ball1.position.y;
            double y2 = ball2.position.y;

            double radius = ball1.radius;

            double distanceSquared = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
            if (distanceSquared < 4 * radius * radius) {
                return false;
            }
        }
    }
    return true;
}

void BilliardsSimulation::manageCollisions() {
    for (int i = 0; i < balls.size(); i++) {
        BilliardsBall &ball = balls[i];
        // Check for collision with table
        float tableRightBorder = table.boundingRectangle.x + (table.boundingRectangle.width / 2.0f);
        float tableLeftBorder = table.boundingRectangle.x - (table.boundingRectangle.width / 2.0f);
        float tableTopBorder = table.boundingRectangle.y + (table.boundingRectangle.height / 2.0f);
        float tableBottomBorder = table.boundingRectangle.x - (table.boundingRectangle.height / 2.0f);
        float radius = ball.boundingCircle.radius;
        if (ball.boundingCircle.x + radius > tableRightBorder) {
            ball.velocity.x *= -1;
            ball.position.x = ball.boundingCircle.x = tableRightBorder - radius - (float) Util::EPSILON;
        }
        if (ball.boundingCircle.x - radius < tableLeftBorder) {
            ball.velocity.x *= -1;
            ball.position.x = ball.boundingCircle.x = tableLeftBorder + radius + (float) Util::EPSILON;
        }
        if (ball.boundingCircle.y + radius > tableTopBorder) {
            ball.velocity.y *= -1;
            ball.position.y = ball.boundingCircle.y = tableTopBorder - radius - (float) Util::EPSILON;
        }
        if (ball.boundingCircle.y - radius < tableBottomBorder) {
            ball.velocity.y *= -1;
            ball.position.y = ball.boundingCircle.y = tableBottomBorder + radius + (float) Util::EPSILON;
        }

        // Check for collision with other balls
        for (int j = i + 1; j < balls.size(); j++) {
            BilliardsBall &otherBall = balls[j];

            Vector p1 = ball.position;
            Vector p2 = otherBall.position;

            double distanceSquared = (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
            if (distanceSquared < 4 * radius * radius) {
                // Found a collision
                Vector v1 = ball.velocity;
                Vector v2 = otherBall.velocity;

                ball.velocity = v1 - (((v1 - v2) * (p1 - p2)) / ((p1 - p2) * (p1 - p2))) * (p1 - p2);
                otherBall.velocity = v2 - (((v2 - v1) * (p2 - p1)) / ((p2 - p1) * (p2 - p1))) * (p2 - p1);

                v1 = ball.velocity;
                v2 = otherBall.velocity;

                // Make sure they are no longer colliding
                double a = (v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y);
                double b = 2 * (p1.x - p2.x) * (v1.x - v2.x) + 2 * (p1.y - p2.y) * (v1.y - v2.y);
                double c = (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) - 4 * radius * radius;

                double t1 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
                double t2 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);

                double t;

                if (t1 >= 0) {
                    t = t1 + Util::EPSILON;
                } else {
                    t = t2 + Util::EPSILON;
                }

                ball.position = p1 + t * v1;
                otherBall.position = p2 + t * v2;
            }
        }
    }
}

void BilliardsSimulation::drawBoundingObjects() {
    for (BilliardsPocket &pocket : pockets) {
        pocket.boundingCircle.draw();
    }
    for (BilliardsBall &ball : balls) {
        ball.boundingCircle.draw();
    }
    table.boundingRectangle.draw();
}

void BilliardsSimulation::update() {
    if (currentState == BilliardsSimState::POSITIONING_CUE_STICK) 
    {
        if (glfwGetKey(window.glfwWindow, GLFW_KEY_LEFT)) {
            stick.increaseAngle();
        }
        if (glfwGetKey(window.glfwWindow, GLFW_KEY_RIGHT)) {
            stick.decreaseAngle();
        }
        if (glfwGetKey(window.glfwWindow, GLFW_KEY_UP)) {
            stick.increaseHitPower();
        }
        if (glfwGetKey(window.glfwWindow, GLFW_KEY_DOWN)) {
            stick.decreaseHitPower();
        }
        if (glfwGetKey(window.glfwWindow, GLFW_KEY_SPACE)) {
            stick.beforeAnimiationHitPower = stick.hitPower;
            currentState = BilliardsSimState::ANIMATING_CUE_STICK;
        }

        camera.position = Vector(balls[0].position.x, 0.4f, balls[0].position.y) +
            Vector(-1.0f, 0.0f, 0.0f).rotate(Vector::yAxis, stick.angle);
        camera.up = Vector(0.0f, 1.0f, 0.0f);
        camera.center = Vector(balls[0].position.x, 0.0f, balls[0].position.y);
        camera.updateViewMatrix();
    } 
    else if (currentState == BilliardsSimState::ANIMATING_CUE_STICK) 
    {
        if (stick.hitPower > 0.0f) {
            stick.hitPower -= 0.1 * stick.beforeAnimiationHitPower;
        } else {
            balls[0].velocity = Vector(0.036f * stick.beforeAnimiationHitPower, 0.0f, 0.0f).rotate(Vector::zAxis, stick.angle);
            balls[0].velocity.y *= -1;
            currentState = BilliardsSimState::SIMULATING_BALLS_MOVING;
        }

        camera.position = Vector(0.0f, 2.4f, 0.0f);
        camera.up = Vector(1.0f, 0.0f, 0.0f);
        camera.center = Vector(0.0f, 0.0f, 0.0f);
        camera.updateViewMatrix();
    } 
    else if (currentState == BilliardsSimState::SIMULATING_BALLS_MOVING) 
    {
        for (int i = 0; i < balls.size(); i++) {
            BilliardsBall &ball = balls[i];
            ball.update();
        }

        manageCollisions();

        if (noBallsMoving()) {
            currentState = BilliardsSimState::POSITIONING_CUE_STICK;
        }

        camera.position = Vector(0.0f, 2.4f, 0.0f);
        camera.up = Vector(1.0f, 0.0f, 0.0f);
        camera.center = Vector(0.0f, 0.0f, 0.0f);
        camera.updateViewMatrix();
    }

    ResourceManager::getShader("default")->setMatProperty("view_mat", camera.viewMatrix.m);
    ResourceManager::getShader("default")->setMatProperty("view_mat", camera.viewMatrix.m);

    ResourceManager::getShader("bounding_object")->setMatProperty("view_mat", camera.viewMatrix.m);
    ResourceManager::getShader("bounding_object")->setMatProperty("view_mat", camera.viewMatrix.m);
}

void BilliardsSimulation::draw() {
    drawBoundingObjects();
    for (BilliardsBall &ball : balls) {
        ball.draw();
    }
    table.draw();
    if (currentState == BilliardsSimState::POSITIONING_CUE_STICK
            || currentState == BilliardsSimState::ANIMATING_CUE_STICK) {
        stick.draw(balls[0].position);
    }
}
