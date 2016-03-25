#ifndef BILLIARDS_OBJECT_3D_H
#define BILLIARDS_OBJECT_3D_H

class Object3D {
    private:
        int numChildren, maxNumChildren;
        bool isMesh;
    protected:
        Object3D **children;
    public:
        Object3D(int maxNumChildren, bool isMesh);

        void addChildObject(Object3D *object);

        int getNumChildren();
        
        Object3D **getChildren();

        bool getIsMesh();
};

#endif
