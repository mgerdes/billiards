#ifndef BILLIARDS_SCENE_H
#define BILLIARDS_SCENE_H

#include "Mesh.h"

class Scene {
    private:
        int maxNumObjects, numObjects;
        Object3D **objects;
    public:
        Scene(int maxNumObjects);

        ~Scene();

        void addObject(Object3D *object);

        Object3D** getObjects();

        int getNumObjects();
};

#endif
