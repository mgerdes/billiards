#ifndef BILLIARDS_BILLIARDSSIMULATION_H
#define BILLIARDS_BILLIARDSSIMULATION_H

#include <vector>
#include "BilliardsBall.h"
#include "BilliardsStick.h"
#include "BilliardsPocket.h"
#include "BilliardsTable.h"
#include "Window.h"
#include "BoundingObject.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "Model.h"

class BilliardsSimulation {
private:
    float pocketRadius = 0.1f;
    float tableX = 0.0f;
    float tableY = 0.0f;
    float tableWidth = 1.0f;
    float tableHeight = 2.0f;
    float cornerHoleDeltaX = -0.028f;
    float cornerHoleDeltaY = -0.01f;
    float middleHoleDeltaX = -0.10f;

    Window &window;
    Camera camera;
    BilliardsTable table;
    BilliardsStick stick;
    vector<BilliardsBall> balls;
    vector<BilliardsPocket> pockets;
    bool ballsMoving = true;

    void drawBoundingObjects();

    bool noBallsColliding();

    bool noBallsMoving();

public:
    BilliardsSimulation(Window &window);

    void update();

    void draw();
};

#endif //BILLIARDS_BILLIARDSSIMULATION_H
