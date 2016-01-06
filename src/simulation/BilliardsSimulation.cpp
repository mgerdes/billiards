#include "BilliardsSimulation.h"

BilliardsBall::BilliardsBall(Vector position, Vector velocity)
        : position(position),
          velocity(velocity),
          boundingCircle(position.x, position.y, ballRadius) { }


void BilliardsBall::update() {
    boundingCircle.x = boundingCircle.x + velocity.x;
    boundingCircle.y = boundingCircle.y + velocity.y;
}

BilliardsPocket::BilliardsPocket(CircleBoundingObject boundingCircle) : boundingCircle{boundingCircle} { }

BilliardsTable::BilliardsTable(RectangleBoundingObject boundingRectangle) : boundingRectangle{boundingRectangle},
                                                                            model("resources/models/table.obj",
                                                                                  ResourceManager::tableModelShader) { }

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

    BilliardsBall ball1 = BilliardsBall(Vector(0.0f, 0.0f, 0.0f), Vector(0.001f, 0.001f, 0.0f));
    balls.push_back(ball1);
}

void BilliardsSimulation::update() {
    for (BilliardsBall &ball : balls) {
        ball.update();
        float tableRightBorder = table.boundingRectangle.x + (table.boundingRectangle.width / 2.0f);
        float tableLeftBorder = table.boundingRectangle.x - (table.boundingRectangle.width / 2.0f);
        float tableTopBorder = table.boundingRectangle.y + (table.boundingRectangle.height / 2.0f);
        float tableBottomBorder = table.boundingRectangle.x - (table.boundingRectangle.height / 2.0f);
        float radius = ball.boundingCircle.radius;
        if (ball.boundingCircle.x + radius > tableRightBorder) {
            ball.velocity.x *= -1;
            ball.boundingCircle.x = tableRightBorder - radius - (float) Util::EPSILON;
        }
        if (ball.boundingCircle.x - radius < tableLeftBorder) {
            ball.velocity.x *= -1;
            ball.boundingCircle.x = tableLeftBorder + radius + (float) Util::EPSILON;
        }
        if (ball.boundingCircle.y + radius > tableTopBorder) {
            ball.velocity.y *= -1;
            ball.boundingCircle.y = tableTopBorder - radius - (float) Util::EPSILON;
        }
        if (ball.boundingCircle.y - radius < tableBottomBorder) {
            ball.velocity.y *= -1;
            ball.boundingCircle.y = tableBottomBorder +  radius + (float) Util::EPSILON;
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
    table.draw();
}
