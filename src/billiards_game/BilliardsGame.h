#ifndef BILLIARDS_GAME_H
#define BILLIARDS_GAME_H

#include "ObjLoader.h"
#include "Scene.h"
#include "Camera.h"
#include "CueStick.h"
#include "BilliardsBall.h"

enum BilliardsGameState {
    POSITIONING_CUE_STICK, ANIMATING_CUE_STICK, SIMULATING_BALLS_MOVING, TRANSITIONING_CAMERA
};

class BilliardsGame {
    private:
        Scene *scene;
        Camera *camera;
        CueStick *cueStick;
        Object3D *table;
        BilliardsBall *balls[16];
        BilliardsGameState currentState;

        void initScene();

        void initCamera();

        void handleKeyInput();

        void handleCollisions();

        void updateCueStick();

        void updateCamera();

        bool isAnyBallsMoving();
    public:
        bool isLeftKeyDown, isRightKeyDown, isUpKeyDown, isDownKeyDown;
        bool isWKeyDown, isAKeyDown, isSKeyDown, isDKeyDown;
        bool isSpaceKeyDown;

        BilliardsGame();        

        void update(float dt);

        Scene *getScene();

        Camera *getCamera();
};

#endif
