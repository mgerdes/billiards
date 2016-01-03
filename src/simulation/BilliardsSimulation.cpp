#include "BilliardsSimulation.h"

BilliardsSimulation::BilliardsSimulation(Window &window,
                                         Material material,
                                         Shader &shader,
                                         Camera camera) : window(window),
                                                          camera(camera),
                                                          shader(shader),
                                                          table(RectangleBoundingObject(tableTopX, tableTopY,
                                                                                        tableWidth, tableHeight,
                                                                                        material, shader)) {
    Light light = Light(Vector(2, 2, 2), Vector(0.1, 0.1, 0.1), Vector(0.6, 0.6, 0.6), Vector(0.0, 0.0, 0.0));

    shader.setLightProperty(light);
    shader.setVec3Property("camera_position", camera.position);
    shader.setMatProperty("proj_mat", camera.projectionMatrix.m);
    shader.setMatProperty("view_mat", camera.viewMatrix.m);

    CircleBoundingObject pocket1BoundingCircle = CircleBoundingObject(tableTopX + cornerHoleDeltaX,
                                                                      tableTopY + cornerHoleDeltaY,
                                                                      pocketRadius, material, shader);
    BilliardsPocket pocket1 = BilliardsPocket(pocket1BoundingCircle);
    CircleBoundingObject pocket2BoundingCircle = CircleBoundingObject(tableTopX + tableWidth - cornerHoleDeltaX,
                                                                      tableTopY + cornerHoleDeltaY,
                                                                      pocketRadius, material, shader);
    BilliardsPocket pocket2 = BilliardsPocket(pocket2BoundingCircle);
    CircleBoundingObject pocket3BoundingCircle = CircleBoundingObject(tableTopX + cornerHoleDeltaX,
                                                                      tableTopY + tableHeight - cornerHoleDeltaY,
                                                                      pocketRadius, material, shader);
    BilliardsPocket pocket3 = BilliardsPocket(pocket3BoundingCircle);
    CircleBoundingObject pocket4BoundingCircle = CircleBoundingObject(tableTopX + tableWidth - cornerHoleDeltaX,
                                                                      tableTopY + tableHeight - cornerHoleDeltaY,
                                                                      pocketRadius, material, shader);
    BilliardsPocket pocket4 = BilliardsPocket(pocket4BoundingCircle);
    CircleBoundingObject pocket5BoundingCircle = CircleBoundingObject(tableTopX + middleHoleDeltaX,
                                                                      tableTopY + (tableHeight / 2.0f),
                                                                      pocketRadius, material, shader);
    BilliardsPocket pocket5 = BilliardsPocket(pocket5BoundingCircle);
    CircleBoundingObject pocket6BoundingCircle = CircleBoundingObject(tableTopX + tableWidth - middleHoleDeltaX,
                                                                      tableTopY + (tableHeight / 2.0f),
                                                                      pocketRadius, material, shader);
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
    Matrix translationMatrix = Matrix(Vector(0.0, 0.0, 0.0));
    Matrix scaleMatrix = Matrix(1.0);
    Matrix modelMatrix = translationMatrix * scaleMatrix;
    shader.setMatProperty("model_mat", modelMatrix.m);

    for (BilliardsPocket pocket : pockets) {
        pocket.boundingCircle.draw();
    }

    table.boundingRectangle.draw();
}
