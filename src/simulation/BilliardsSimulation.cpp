#include "BilliardsSimulation.h"

BilliardsPocket::BilliardsPocket(CircleBoundingObject boundingCircle) : boundingCircle{boundingCircle} { }

BilliardsTable::BilliardsTable(RectangleBoundingObject boundingRectangle) : boundingRectangle{boundingRectangle}, model("resources/models/table.obj", ResourceManager::tableModelShader) { }

BilliardsSimulation::BilliardsSimulation(Window &window)
        : window(window),
          camera(Vector(2.1, 2, 2.1), Vector(0, 0, 0), Vector(0, 1, 0)),
          table(RectangleBoundingObject(tableTopX, tableTopY, tableWidth, tableHeight)) {
    Light light = Light(Vector(0, 4, 0), Vector(0.1, 0.1, 0.1), Vector(0.3, 0.3, 0.3), Vector(0.0, 0.0, 0.0));

    ResourceManager::tableModelShader.setLightProperty(light);
    ResourceManager::tableModelShader.setMatProperty("proj_mat", camera.projectionMatrix.m);
    ResourceManager::tableModelShader.setMatProperty("view_mat", camera.viewMatrix.m);

    ResourceManager::boundingObjectShader.setMatProperty("proj_mat", camera.projectionMatrix.m);
    ResourceManager::boundingObjectShader.setMatProperty("view_mat", camera.viewMatrix.m);

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
}

void BilliardsSimulation::update() {

}

void BilliardsSimulation::draw() {
    static float theta = 0.0;

    Matrix translationMatrix = Matrix(Vector(0.0, 0.0, 0.0));
    Matrix rotationMatrix = Matrix(Vector(0.0, 1.0, 0.0), theta);
    Matrix scaleMatrix = Matrix(1.0);
    Matrix modelMatrix = rotationMatrix * translationMatrix * scaleMatrix;
    ResourceManager::boundingObjectShader.setMatProperty("model_mat", modelMatrix.m);

    for (BilliardsPocket pocket : pockets) {
        pocket.boundingCircle.draw();
    }

    table.boundingRectangle.draw();

    translationMatrix = Matrix(Vector(tableModelDeltaX, tableModelDeltaY, 0.0));
    rotationMatrix = Matrix(Vector(0.0, 1.0, 0.0), theta + (float) (M_PI / 2.0));
    scaleMatrix = Matrix::scaleMatrix(Vector(tableModelScaleX,
                                             (tableModelScaleX + tableModelScaleY) / 2.0,
                                             tableModelScaleY));
    modelMatrix = rotationMatrix * translationMatrix * scaleMatrix;
    ResourceManager::tableModelShader.setMatProperty("model_mat", modelMatrix.m);

    table.model.draw();

    theta += 0.01;
}
