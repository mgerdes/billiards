#ifndef BILLIARDS_BILLIARDSSIMULATION_H
#define BILLIARDS_BILLIARDSSIMULATION_H

#include <vector>
#include "Window.h"
#include "BoundingObject.h"
#include "Camera.h"
#include "ResourceManager.h"

class BilliardsBall {
private:
    float ballRadius = 0.0250f;
    CircleBoundingObject boundingCircle;
};

class BilliardsPocket {
public:
    CircleBoundingObject boundingCircle;

    BilliardsPocket(CircleBoundingObject boundingCircle) : boundingCircle(boundingCircle) { }
};

class BilliardsTable {
public:
    RectangleBoundingObject boundingRectangle;

    BilliardsTable(RectangleBoundingObject boundingRectangle) : boundingRectangle(boundingRectangle) { }
};

class BilliardsSimulation {
private:
    float pocketRadius = 0.1f;
    float tableTopX = -0.5f;
    float tableTopY = -1.0f;
    float tableWidth = 1.0f;
    float tableHeight = 2.0f;
    float cornerHoleDeltaX = -0.028f;
    float cornerHoleDeltaY = -0.01f;
    float middleHoleDeltaX = -0.10f;

    Window &window;
    ResourceManager &resourceManager;

    Camera camera;
    BilliardsTable table;
    vector<BilliardsBall> balls;
    vector<BilliardsPocket> pockets;
public:
    BilliardsSimulation(Window &window, ResourceManager &resourceManger);

    void update();

    void draw();
};

#endif //BILLIARDS_BILLIARDSSIMULATION_H
