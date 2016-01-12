#ifndef BILLIARDS_BILLIARDSSIMULATION_H
#define BILLIARDS_BILLIARDSSIMULATION_H

#include <vector>
#include "Window.h"
#include "BoundingObject.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "Model.h"

class BilliardsStick {
private:
    static constexpr float stickDelta = -0.7900f;
    static constexpr float angleDelta = 0.01f;
    static constexpr float hitPowerDelta = 0.01f;

public:
    float angle = 0.0f;
    float hitPower = 0.0f;
    Model model;

    BilliardsStick();

    void draw(Vector positionOfCueBall);

    void update(Window &window);
};

class BilliardsBall {
    static constexpr float angleDelta = 0.01f;
public:
    static constexpr float radius = 0.0300f;
    float angle = 0.0f;
    int ballNumber;
    Vector position, velocity;
    CircleBoundingObject boundingCircle;

    Model model;

    BilliardsBall(Vector position, Vector velocity, int ballNumber);

    void draw();

    void update();
};

class BilliardsPocket {
public:
    CircleBoundingObject boundingCircle;

    BilliardsPocket(CircleBoundingObject boundingCircle);
};

class BilliardsTable {
private:
    float tableModelDeltaX = -0.325f;
    float tableModelDeltaY = -0.61f;
    float tableModelScaleX = 2.16f;
    float tableModelScaleY = 2.55f;

public:
    RectangleBoundingObject boundingRectangle;

    Model model;

    BilliardsTable(RectangleBoundingObject boundingRectangle);

    void draw();
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

    void drawBoundingObjects();

    bool noBallsColliding();

public:
    BilliardsSimulation(Window &window);

    void update();

    void draw();
};

#endif //BILLIARDS_BILLIARDSSIMULATION_H
