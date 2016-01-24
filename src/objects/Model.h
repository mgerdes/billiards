#ifndef BILLIARDS_MODEL_H
#define BILLIARDS_MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"
#include "Texture.h"
#include "ResourceManager.h"

class Model {
private:
    vector<Mesh *> meshes;

    void processNode(aiNode *node, const aiScene *scene);

    Mesh *processMesh(aiMesh *mesh, const aiScene *scene);

public:
    Model(string fileName);

    void draw(Shader *shader, Matrix &modelMatrix);
};

#endif //BILLIARDS_MODEL_H
