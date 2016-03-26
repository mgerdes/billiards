#ifndef BILLIARDS_RENDERER_H
#define BILLIARDS_RENDERER_H

#include "Scene.h"
#include "Camera.h"

class Renderer {
    private:
        Scene *scene;
        Camera *camera;

        void renderObject(Object3D *object, Matrix4 *modelMat);
    public:
        Renderer(Scene *scene, Camera *camera);

        void render();
};

#endif
