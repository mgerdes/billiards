#ifndef BILLIARDS_RENDERER_H
#define BILLIARDS_RENDERER_H

#include "Scene.h"
#include "Camera.h"

class Renderer {
    private:
        Scene *scene;
        Camera *camera;
    public:
        Renderer(Scene *scene, Camera *camera);

        void render();
};

#endif
