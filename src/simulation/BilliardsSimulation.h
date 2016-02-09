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

enum class BilliardsSimState {
    POSITIONING_CUE_STICK, ANIMATING_CUE_STICK, SIMULATING_BALLS_MOVING, TRANSITIONING_CAMERA
};

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

    int timesCameraMovedInTransition;
    BilliardsSimState stateAfterCameraTransition;
    Vector cameraTransitionPositionDelta;
    Vector cameraTransitionCenterDelta;
    Vector cameraTransitionUpDelta;

    void drawBoundingObjects();

    bool noBallsColliding();

    bool noBallsMoving();

    void manageCollisions();

    void enterCameraTransitionState(Vector cameraTransitionEndPosition, 
            Vector cameraTransitionEndCenter, 
            Vector cameraTransitionEndUp, 
            BilliardsSimState stateAfterCameraTransition);

    BilliardsSimState currentState = BilliardsSimState::SIMULATING_BALLS_MOVING;
public:
    BilliardsSimulation(Window &window);

    void update(double timeDelta);

    void draw();
};

#endif //BILLIARDS_BILLIARDSSIMULATION_H
