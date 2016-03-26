#ifndef BILLIARDS_OBJECT_3D_H
#define BILLIARDS_OBJECT_3D_H

#include "Matrix4.h"
#include "Vector3.h"

class Object3D {
    private:
        int numChildren, maxNumChildren;
        bool isMesh;
        Object3D **children;
        Matrix4 *modelMat;
    public:
        Vector3 *translation, *scale, *rotation;

        Object3D(int maxNumChildren, bool isMesh);

        void addChildObject(Object3D *object);

        int getNumChildren();

        Object3D **getChildren();

        bool getIsMesh();

        void updateModelMat();

        Matrix4 *getModelMat();
};

#endif
