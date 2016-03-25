#include "ObjLoader.h"

Object3D *ObjLoader::loadObject(const char *fileName) {
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(fileName, aiProcess_Triangulate);

    if (!scene) {
        Util::log(Severity::ERROR, "Cannot open scene file: " + std::string(fileName));
        return NULL;
    }

    Util::log(Severity::INFO, "Loading model: " + std::string(fileName));
    Util::log(Severity::INFO, std::to_string(scene->mNumAnimations) + " animations");
    Util::log(Severity::INFO, std::to_string(scene->mNumCameras) + " cameras");
    Util::log(Severity::INFO, std::to_string(scene->mNumLights) + " lights");
    Util::log(Severity::INFO, std::to_string(scene->mNumMaterials) + " materials");
    Util::log(Severity::INFO, std::to_string(scene->mNumMeshes) + " meshes");
    Util::log(Severity::INFO, std::to_string(scene->mNumTextures) + " textures");

    Object3D *object = new Object3D(scene->mNumMeshes, false);

    aiNode *rootNode = scene->mRootNode;
    for (int i = 0; i < rootNode->mNumChildren; i++) {
        aiNode *node = rootNode->mChildren[i];
        for (int j = 0; j < node->mNumMeshes; j++) {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[j]];
            object->addChildObject(processMesh(mesh, scene));
        }
    }

    Util::log(Severity::INFO, "Finished loading model: " + std::string(fileName));

    return object;
}

Mesh *ObjLoader::processMesh(aiMesh *mesh, const aiScene *scene) {
    Geometry *meshGeometry = new Geometry(mesh->mNumVertices);

    for (int i = 0; i < mesh->mNumVertices; i++) {
        aiVector3D position = mesh->mVertices[i];
        meshGeometry->addVertex(position.x, position.y, position.z);
    }

    Shader *meshShader = ResourceManager::getShader(Shaders::BASIC);
    Material *meshMaterial = new Material(meshShader);
    
    return new Mesh(meshGeometry, meshMaterial);
}
