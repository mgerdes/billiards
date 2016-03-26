#ifndef BILLIARDS_GAME_H
#define BILLIARDS_GAME_H

#include "ObjLoader.h"
#include "Scene.h"
#include "Camera.h"
#include "CueStick.h"

class BilliardsGame {
    private:
        Scene *scene;
        Camera *camera;
        CueStick *cueStick;
        Object3D *table;

        void initScene();

        void initCamera();

        void handleKeyInput();
    public:
        bool isLeftKeyDown, isRightKeyDown, isUpKeyDown, isDownKeyDown;

        BilliardsGame();        

        void update(float dt);

        Scene *getScene();

        Camera *getCamera();
};

#endif
