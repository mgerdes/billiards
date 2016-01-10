#include "BilliardsSimulation.h"

BilliardsBall::BilliardsBall(Vector position, Vector velocity)
        : position(position),
          velocity(velocity),
          boundingCircle(position.x, position.y, radius),
          model("resources/models/ball.obj", ResourceManager::tableModelShader) { }


void BilliardsBall::update() {
    position.x = boundingCircle.x = position.x + velocity.x;
    position.y = boundingCircle.y = position.y + velocity.y;
    double speed = velocity.length();
    if (speed > Util::EPSILON) {
        velocity.x = velocity.x - velocity.x * 0.01f;
        velocity.y = velocity.y - velocity.y * 0.01f;
    } else {
        velocity.x = 0;
        velocity.y = 0;
    }
}

void BilliardsBall::draw() {
    Matrix translation = Matrix(Vector(position.x, radius, position.y));
    Matrix scale = Matrix::scaleMatrix(Vector(1.0, 1.0, 1.0));
    Matrix modelMat = translation * scale;
    ResourceManager::tableModelShader.setMatProperty("model_mat", modelMat.m);
    model.draw();
}

BilliardsPocket::BilliardsPocket(CircleBoundingObject boundingCircle)
        : boundingCircle{boundingCircle} { }

BilliardsTable::BilliardsTable(RectangleBoundingObject boundingRectangle)
        : boundingRectangle{boundingRectangle},
          model("resources/models/table.obj", ResourceManager::tableModelShader) { }

void BilliardsTable::draw() {
    Matrix translation = Matrix(Vector(tableModelDeltaX, tableModelDeltaY, 0.0));
    Matrix rotation = Matrix(Vector(0.0, 1.0, 0.0), (float) (M_PI / 2.0));
    Matrix scale = Matrix::scaleMatrix(Vector(tableModelScaleX,
                                              (tableModelScaleX + tableModelScaleY) / 2.0f,
                                              tableModelScaleY));
    Matrix modelMat = rotation * translation * scale;
    ResourceManager::tableModelShader.setMatProperty("model_mat", modelMat.m);
    model.draw();
}

BilliardsSimulation::BilliardsSimulation(Window &window)
        : window(window),
          camera(Vector(2.1, 2, 2.1), Vector(0, 0, 0), Vector(0, 1, 0)),
          table(RectangleBoundingObject(tableY, tableY, tableWidth, tableHeight)) {
    Light light = Light(Vector(0, 4, 0), Vector(0.1, 0.1, 0.1), Vector(0.3, 0.3, 0.3), Vector(0.0, 0.0, 0.0));

    ResourceManager::tableModelShader.setLightProperty(light);
    ResourceManager::tableModelShader.setMatProperty("proj_mat", camera.projectionMatrix.m);
    ResourceManager::tableModelShader.setMatProperty("view_mat", camera.viewMatrix.m);

    ResourceManager::boundingObjectShader.setMatProperty("proj_mat", camera.projectionMatrix.m);
    ResourceManager::boundingObjectShader.setMatProperty("view_mat", camera.viewMatrix.m);

    float tableTopX = tableX - (tableWidth / 2.0f);
    float tableTopY = tableY - (tableHeight / 2.0f);

    CircleBoundingObject pocket1BoundingCircle = CircleBoundingObject(tableTopX + cornerHoleDeltaX,
                                                                      tableTopY + cornerHoleDeltaY,
                                                                      pocketRadius);
    BilliardsPocket pocket1 = BilliardsPocket(pocket1BoundingCircle);
    CircleBoundingObject pocket2BoundingCircle = CircleBoundingObject(tableTopX + tableWidth - cornerHoleDeltaX,
                                                                      tableTopY + cornerHoleDeltaY,
                                                                      pocketRadius);
    BilliardsPocket pocket2 = BilliardsPocket(pocket2BoundingCircle);
    CircleBoundingObject pocket3BoundingCircle = CircleBoundingObject(tableTopX + cornerHoleDeltaX,
                                                                      tableTopY + tableHeight - cornerHoleDeltaY,
                                                                      pocketRadius);
    BilliardsPocket pocket3 = BilliardsPocket(pocket3BoundingCircle);
    CircleBoundingObject pocket4BoundingCircle = CircleBoundingObject(tableTopX + tableWidth - cornerHoleDeltaX,
                                                                      tableTopY + tableHeight - cornerHoleDeltaY,
                                                                      pocketRadius);
    BilliardsPocket pocket4 = BilliardsPocket(pocket4BoundingCircle);
    CircleBoundingObject pocket5BoundingCircle = CircleBoundingObject(tableTopX + middleHoleDeltaX,
                                                                      tableTopY + (tableHeight / 2.0f),
                                                                      pocketRadius);
    BilliardsPocket pocket5 = BilliardsPocket(pocket5BoundingCircle);
    CircleBoundingObject pocket6BoundingCircle = CircleBoundingObject(tableTopX + tableWidth - middleHoleDeltaX,
                                                                      tableTopY + (tableHeight / 2.0f),
                                                                      pocketRadius);
    BilliardsPocket pocket6 = BilliardsPocket(pocket6BoundingCircle);

    pockets.push_back(pocket1);
    pockets.push_back(pocket2);
    pockets.push_back(pocket3);
    pockets.push_back(pocket4);
    pockets.push_back(pocket5);
    pockets.push_back(pocket6);

    BilliardsBall ball1 = BilliardsBall(Vector(0.0f, 0.0f, 0.0f), Vector(0.008f, 0.008f, 0.0f));
    BilliardsBall ball2 = BilliardsBall(Vector(0.1f, 0.0f, 0.0f), Vector(0.008f, 0.008f, 0.0f));
    BilliardsBall ball3 = BilliardsBall(Vector(0.2f, 0.0f, 0.0f), Vector(0.008f, 0.008f, 0.0f));
    BilliardsBall ball4 = BilliardsBall(Vector(0.3f, 0.0f, 0.0f), Vector(0.008f, 0.008f, 0.0f));
    BilliardsBall ball5 = BilliardsBall(Vector(0.4f, 0.0f, 0.0f), Vector(0.008f, 0.008f, 0.0f));
    BilliardsBall ball6 = BilliardsBall(Vector(-0.1f, 0.0f, 0.0f), Vector(0.008f, 0.008f, 0.0f));
    BilliardsBall ball7 = BilliardsBall(Vector(-0.2f, 0.0f, 0.0f), Vector(0.008f, 0.008f, 0.0f));
    BilliardsBall ball8 = BilliardsBall(Vector(-0.2f, 0.0f, 0.0f), Vector(0.008f, 0.008f, 0.0f));
    BilliardsBall ball9 = BilliardsBall(Vector(-0.3f, 0.0f, 0.0f), Vector(0.008f, 0.008f, 0.0f));
    BilliardsBall ball10 = BilliardsBall(Vector(-0.4f, 0.0f, 0.0f), Vector(0.008f, 0.008f, 0.0f));
    BilliardsBall ball11 = BilliardsBall(Vector(0.0f, 0.1f, 0.0f), Vector(0.008f, 0.008f, 0.0f));
    BilliardsBall ball12 = BilliardsBall(Vector(0.1f, 0.1f, 0.0f), Vector(0.008f, 0.008f, 0.0f));
    BilliardsBall ball13 = BilliardsBall(Vector(0.2f, 0.1f, 0.0f), Vector(0.008f, 0.008f, 0.0f));
    BilliardsBall ball14 = BilliardsBall(Vector(0.3f, 0.1f, 0.0f), Vector(0.008f, 0.008f, 0.0f));
    BilliardsBall ball15 = BilliardsBall(Vector(0.4f, 0.1f, 0.0f), Vector(0.008f, 0.008f, 0.0f));
    balls.push_back(ball1);
    balls.push_back(ball2);
    balls.push_back(ball3);
    balls.push_back(ball4);
    balls.push_back(ball5);
    balls.push_back(ball6);
    balls.push_back(ball7);
    balls.push_back(ball8);
    balls.push_back(ball9);
    balls.push_back(ball10);
    balls.push_back(ball11);
    balls.push_back(ball12);
    balls.push_back(ball13);
    balls.push_back(ball14);
    balls.push_back(ball15);
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
            if (distanceSquared < radius * radius) {
                return false;
            }
        }
    }
    return true;
}

void BilliardsSimulation::update() {
    for (int i = 0; i < balls.size(); i++) {
        BilliardsBall &ball = balls[i];
        ball.update();
    }
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
            if (distanceSquared < radius * radius) {
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
                double c = (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) - radius * radius;

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

void BilliardsSimulation::draw() {
    drawBoundingObjects();
    for (BilliardsBall &ball : balls) {
        ball.draw();
    }
    table.draw();
}
