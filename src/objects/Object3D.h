#ifndef BILLIARDS_OBJECT_3D_H
#define BILLIARDS_OBJECT_3D_H

#include "Matrix4.h"
#include "Vector3.h"
#include "Quaternion.h"

enum MatrixMultOrder {
    T_R_S, R_T_S
};

class Object3D {
    private:
        int numChildren, maxNumChildren;
        Object3D **children;
        Matrix4 modelMat;
        MatrixMultOrder matrixMultOrder;
        Quaternion quaternion;
        Vector3 translation, scale, rotation;
    public:
        bool isMesh, isVisible;

        Object3D(int maxNumChildren);

        void addChildObject(Object3D *object);

        int getNumChildren();

        Object3D **getChildren();

        void updateModelMat();

        Matrix4 *getModelMat();

        void setMatrixMultOrder(MatrixMultOrder matrixMultOrder);

        Quaternion *getQuaternion();

        Vector3 *getTranslation();

        Vector3 *getScale();

        Vector3 *getRotation();
};

#endif
