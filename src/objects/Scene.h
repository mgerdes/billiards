#ifndef BILLIARDS_SCENE_H
#define BILLIARDS_SCENE_H

#include "Mesh.h"

class Scene {
    private:
        int maxNumMeshes, numMeshes;
        Mesh **meshes;
    public:
        Scene(int maxNumMeshes);

        ~Scene();

        void addMesh(Mesh *mesh);

        Mesh** getMeshes();

        int getNumMeshes();
};

#endif
