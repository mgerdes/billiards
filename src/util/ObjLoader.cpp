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

    Object3D *object = new Object3D(scene->mNumMeshes);

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

    // Process vertices
    for (int i = 0; i < mesh->mNumVertices; i++) {
        aiVector3D position = mesh->mVertices[i];
        meshGeometry->addVertex(position.x, position.y, position.z);
    }

    // Process normals
    if (mesh->HasNormals()) {
        meshGeometry->setMaxNumNormals(mesh->mNumVertices);
        for (int i = 0; i < mesh->mNumVertices; i++) {
            aiVector3D normal = mesh->mNormals[i];
            meshGeometry->addNormal(normal.x, normal.y, normal.z);
        }
    } 

    // Process texture coordinates
    if (mesh->HasTextureCoords(0)) {
        meshGeometry->setMaxNumTextureCoords(mesh->mNumVertices);
        for (int i = 0; i < mesh->mNumVertices; i++) {
            aiVector3D texture = mesh->mTextureCoords[0][i];
            meshGeometry->addTextureCoord(texture.x, texture.y);
        }
    } 

    // Process material
    Texture *texture;
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        aiString path;
        aiGetMaterialTexture(material, aiTextureType_DIFFUSE, 0, &path, 0, 0, 0, 0, 0, 0);
        if (path.length > 0) {
            texture = ResourceManager::getTexture(path.data);
        }

        aiColor4D color;
        aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &color);
        aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &color);
        aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &color);

        float shininess;
        aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &shininess);
    }

    Shader *meshShader = ResourceManager::getShader("basic_texture");
    Material *meshMaterial = new Material(meshShader);
    if (texture) {
        meshMaterial->setTexture(texture);
    }
    
    return new Mesh(meshGeometry, meshMaterial);
}
