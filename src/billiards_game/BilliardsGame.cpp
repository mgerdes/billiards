#include "BilliardsGame.h"

BilliardsGame::BilliardsGame() {
    this->currentState = BilliardsGameState::SIMULATING_BALLS_MOVING;
    this->initScene();    
    this->initCamera();
}

void BilliardsGame::initScene() {
    this->table = ObjLoader::loadObject("resources/models/table.obj");
    this->table->translation->y = -0.26;
    this->table->translation->x = -0.150;
    this->table->updateModelMat();

    this->cueStick = new CueStick();
    this->cueStick->getObject()->setIsVisible(false);

    this->scene = new Scene(18);
    this->scene->addObject(this->table);
    this->scene->addObject(this->cueStick->getObject());

    for (int i = 0; i < 16; i++) {
        this->balls[i] = new BilliardsBall(i);
        this->scene->addObject(this->balls[i]->getObject());
    }
}

void BilliardsGame::initCamera() {
    this->camera = new Camera(45.0, 1.0, 0.1, 100);
}

void BilliardsGame::handleKeyInput() {
    if (this->isLeftKeyDown) {
        this->cueStick->decreaseAngle();
    }
    if (this->isRightKeyDown) {
        this->cueStick->increaseAngle();
    }
    if (this->isUpKeyDown) {
        this->cueStick->increaseHitPower();
    }
    if (this->isDownKeyDown) {
        this->cueStick->decreaseHitPower();
    }
    if (this->isWKeyDown) {

    }
    if (this->isSKeyDown) {

    }
    if (this->isAKeyDown) {

    }
    if (this->isDKeyDown) {

    }
    if (this->isSpaceKeyDown) {
        float hitPower = this->cueStick->getHitPower();
        this->balls[0]->getVelocity()->setThis(hitPower, 0.0, 0.0);
        
        Matrix4 rotationMatrix = Matrix4::eulerRotation(0.0, 0.0, this->cueStick->getAngle());
        this->balls[0]->getVelocity()->applyMatrix(&rotationMatrix);
    }
}

void BilliardsGame::handleCollisions() {
    for (int i = 0; i < 16; i++) {
        Vector3 *p1 = this->balls[i]->getObject()->translation;
        Vector3 *v1 = this->balls[i]->getVelocity();

        if (p1->x < -0.450) {
            v1->x *= -1;
            p1->x = -0.449;
        }
        if (p1->x > 0.450) {
            v1->x *= -1;
            p1->x = 0.449;
        }
        if (p1->z < -0.182) {
            v1->z *= -1;
            p1->z = -0.181;
        }
        if (p1->z > 0.182) {
            v1->z *= -1;
            p1->z = 0.181;
        }

        for (int j = i + 1; j < 16; j++) {
            Vector3 *p2 = this->balls[j]->getObject()->translation;
            Vector3 *v2 = this->balls[j]->getVelocity();

            double radius = 0.014;

            float distance = Vector3::distanceBetween(p1, p2);
            if (distance < 2 * radius) {
                Vector3 temp1 = Vector3::subtract(v1, v2);
                Vector3 temp2 = Vector3::subtract(p1, p2);
                float tempScalar1 = Vector3::dot(&temp1, &temp2) / Vector3::dot(&temp2, &temp2);
                temp2.scaleThis(tempScalar1);

                Vector3 temp3 = Vector3::subtract(v2, v1);
                Vector3 temp4 = Vector3::subtract(p2, p1);
                float tempScalar2 = Vector3::dot(&temp3, &temp4) / Vector3::dot(&temp4, &temp4);
                temp4.scaleThis(tempScalar2);

                Vector3 newV1 = Vector3::subtract(v1, &temp2); 
                v1->setThis(newV1.x, newV1.y, newV1.z);

                Vector3 newV2 = Vector3::subtract(v2, &temp4); 
                v2->setThis(newV2.x, newV2.y, newV2.z);

                // Make sure they are no longer colliding
                float a = (v1->x - v2->x) * (v1->x - v2->x) 
                    + (v1->z - v2->z) * (v1->z - v2->z);
                float b = 2 * (p1->x - p2->x) * (v1->x - v2->x) 
                    + 2 * (p1->z - p2->z) * (v1->z - v2->z);
                float c = (p1->x - p2->x) * (p1->x - p2->x) 
                    + (p1->z - p2->z) * (p1->z - p2->z) - 4 * radius * radius;

                double t1 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
                double t2 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);

                double t;

                if (t1 >= 0.0) {
                    t = t1 + 0.000001;
                } else {
                    t = t2 + 0.000001;
                }

                p1->addToThis(t * v1->x, 0.0, t * v1->z); 
                p2->addToThis(t * v2->x, 0.0, t * v2->z); 
            }
        }
    }
}

bool BilliardsGame::isAnyBallsMoving() {
    for (int i = 0; i < 16; i++) {
        float speed = this->balls[i]->getVelocity()->length();
        if (speed > 0.0) {
            return true;
        }
    }
    return false;
}

void BilliardsGame::updateCueStick() {
    Vector3 *cueStickPosition = this->cueStick->getObject()->getChildren()[0]->translation;
    Vector3 *cueBallPosition = this->balls[0]->getObject()->translation;
    cueStickPosition->x = cueBallPosition->x;
    cueStickPosition->z = cueBallPosition->z;
    this->cueStick->getObject()->getChildren()[0]->updateModelMat();
}

void BilliardsGame::handlePositionCueStickState() {
    this->handleKeyInput();
    this->updateCueStick();

    Vector3 *cueBallPosition = this->balls[0]->getObject()->translation;

    Vector3 temp = Vector3(1.0, 0.5, 0.0);
    Matrix4 rotationMatrix = Matrix4::eulerRotation(0.0, 0.0, this->cueStick->getAngle() + 3.1415);
    temp.applyMatrix(&rotationMatrix);

    this->camera->position = new Vector3(*cueBallPosition); 
    this->camera->position->addToThis(&temp);

    this->camera->lookAt = new Vector3(*cueBallPosition);
    this->camera->updateViewMatrix();

    if (this->isSpaceKeyDown) {
        Vector3 endCameraTransitionPosition = Vector3(1.0, 1.0, 1.0);
        Vector3 *endCameraTransitionLookAt = this->balls[0]->getObject()->translation;

        this->enterCameraTransitionState(&endCameraTransitionPosition, 
                endCameraTransitionLookAt, 
                0, 
                BilliardsGameState::ANIMATING_CUE_STICK);
    }
}

void BilliardsGame::handleAnimatingCueStickState() {
    Vector3 *cueStickPosition = this->cueStick->getObject()->translation;                 
    if (cueStickPosition->x < -0.535) {
        cueStickPosition->x += 0.02 * cueStick->getHitPower();
        this->cueStick->getObject()->updateModelMat();
    }
    else {
        this->cueStick->getObject()->setIsVisible(false);
        this->cueStick->increaseHitPower();
        this->cueStick->decreaseHitPower();
        this->currentState = BilliardsGameState::SIMULATING_BALLS_MOVING;
    }
}

void BilliardsGame::handleSimulatingBallsMovingState(float dt) {
    bool isAnyBallsMoving = this->isAnyBallsMoving();

    for (int i = 0; i < 16; i++) {
        this->balls[i]->update(dt);
    }
    this->handleCollisions();

    if (!isAnyBallsMoving) {
        Vector3 temp = Vector3(1.0, 0.5, 0.0);
        Matrix4 rotationMatrix = Matrix4::eulerRotation(0.0, 0.0, this->cueStick->getAngle() + 3.1415);
        temp.applyMatrix(&rotationMatrix);

        Vector3 *endCameraTransitionPosition = new Vector3(*this->balls[0]->getObject()->translation);
        endCameraTransitionPosition->addToThis(&temp);

        Vector3 endCameraTransitionLookAt = Vector3(0.0, 0.0, 0.0);

        this->enterCameraTransitionState(endCameraTransitionPosition, 
                &endCameraTransitionLookAt, 
                0, 
                BilliardsGameState::POSITIONING_CUE_STICK);

        this->updateCueStick();
        this->cueStick->getObject()->setIsVisible(true);
    }
}

void BilliardsGame::handleTransitioningCameraState() {
    if (this->timesCameraTransitioned >= 25) {
        this->currentState = this->stateAfterCameraTransition;
    } 
    else {
        this->camera->position->addToThis(this->cameraTransitionPositionDelta);
        this->camera->lookAt->addToThis(this->cameraTransitionLookAtDelta);
        this->camera->updateViewMatrix();
        this->timesCameraTransitioned++;
    }
}

void BilliardsGame::update(float dt) {
    if (this->currentState == BilliardsGameState::SIMULATING_BALLS_MOVING) {
        this->handleSimulatingBallsMovingState(dt);
    }
    else if (this->currentState == BilliardsGameState::POSITIONING_CUE_STICK) {
        this->handlePositionCueStickState();
    }
    else if (this->currentState == BilliardsGameState::ANIMATING_CUE_STICK) {
        this->handleAnimatingCueStickState();
    }
    else if (this->currentState == BilliardsGameState::TRANSITIONING_CAMERA) {
        this->handleTransitioningCameraState();
    }
}

Scene *BilliardsGame::getScene() {
    return this->scene;
}

Camera *BilliardsGame::getCamera() {
    return this->camera;
}

void BilliardsGame::enterCameraTransitionState(Vector3 *cameraTransitionEndPosition, 
        Vector3 *cameraTransitionEndLookAt, 
        Vector3 *cameraTransitionEndUp, 
        BilliardsGameState stateAfterCameraTransition) {
    this->timesCameraTransitioned = 0;

    this->cameraTransitionPositionDelta = new Vector3(Vector3::subtract(cameraTransitionEndPosition, this->camera->position));
    this->cameraTransitionPositionDelta->scaleThis(1.0/25.0);

    this->cameraTransitionLookAtDelta = new Vector3(Vector3::subtract(cameraTransitionEndLookAt, this->camera->lookAt));
    this->cameraTransitionLookAtDelta->scaleThis(1.0/25.0);

    this->stateAfterCameraTransition = stateAfterCameraTransition;
    this->currentState = BilliardsGameState::TRANSITIONING_CAMERA;
}
