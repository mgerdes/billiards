#ifndef BILLIARDS_OBJ_LOADER_H
#define BILLIARDS_OBJ_LOADER_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Object3D.h"
#include "Mesh.h"
#include "ResourceManager.h"

class ObjLoader {
    private:
        static Mesh *processMesh(aiMesh *mesh, const aiScene *scene);
    public:
        static Object3D *loadObject(const char *fileName);
};

#endif
