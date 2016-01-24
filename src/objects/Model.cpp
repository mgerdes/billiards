#include "Model.h"

Model::Model(string fileName) {
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(fileName.c_str(), aiProcess_Triangulate);

    if (!scene) {
        Util::log(Severity::ERROR, "Cannot open scene file: " + fileName);
        return;
    }

    Util::log(Severity::INFO, "Loading model: " + fileName);
    Util::log(Severity::INFO, std::to_string(scene->mNumAnimations) + " animations");
    Util::log(Severity::INFO, std::to_string(scene->mNumCameras) + " cameras");
    Util::log(Severity::INFO, std::to_string(scene->mNumLights) + " lights");
    Util::log(Severity::INFO, std::to_string(scene->mNumMaterials) + " materials");
    Util::log(Severity::INFO, std::to_string(scene->mNumMeshes) + " meshes");
    Util::log(Severity::INFO, std::to_string(scene->mNumTextures) + " textures");

    this->processNode(scene->mRootNode, scene);

    Util::log(Severity::INFO, "Finished loading model: " + fileName);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
    for (int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }

    for (int i = 0; i < node->mNumChildren; i++) {
        this->processNode(node->mChildren[i], scene);
    }
}

Mesh *Model::processMesh(aiMesh *mesh, const aiScene *scene) {
    vector<Vector> meshVertices;
    vector<Vector> meshNormals;
    vector<Vector> meshTextureCoordinates;

    // Process vertices
    if (mesh->HasPositions()) {
        for (int i = 0; i < mesh->mNumVertices; i++) {
            aiVector3D position = mesh->mVertices[i];
            meshVertices.push_back(Vector(position.x, position.y, position.z));
        }
    } else {
        Util::log(INFO, "A mesh was processed with no vertices.");
    }

    // Process normals
    if (mesh->HasNormals()) {
        for (int i = 0; i < mesh->mNumVertices; i++) {
            aiVector3D normal = mesh->mNormals[i];
            meshNormals.push_back(Vector(normal.x, normal.y, normal.z));
        }
    } else {
        Util::log(INFO, "A mesh was processed with no vertices.");
    }

    // Process texture coordinates
    if (mesh->HasTextureCoords(0)) {
        for (int i = 0; i < mesh->mNumVertices; i++) {
            aiVector3D texture = mesh->mTextureCoords[0][i];
            meshTextureCoordinates.push_back(Vector(texture.x, texture.y, texture.z));
        }
    } else {
        for (int i = 0; i < mesh->mNumVertices; i++) {
            meshTextureCoordinates.push_back(Vector(0.0, 0.0, 0.0));
        }
        Util::log(INFO, "A mesh was processed with no texture coordinates.");
    }

    // Process material
    Vector ambientColor, diffuseColor, specularColor;
    float shininess = 1.0;
    Texture *texture = 0;
    if (mesh->mMaterialIndex >= 0) {
        aiString path;
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        aiGetMaterialTexture(material, aiTextureType_DIFFUSE, 0, &path, 0, 0, 0, 0, 0, 0);

        if (path.length > 0) {
            texture = ResourceManager::getTexture(path.data);
        }

        aiColor4D color;
        aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &color);
        diffuseColor = Vector(color.r, color.g, color.b);

        aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &color);
        ambientColor = Vector(color.r, color.g, color.b);

        aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &color);
        specularColor = Vector(color.r, color.g, color.b);

        aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &shininess);
    } else {
        Util::log(INFO, "A mesh was processed with no material.");
    }

    Material *meshMaterial = new Material(texture, ambientColor, diffuseColor, specularColor, shininess);
    return new Mesh(meshVertices, meshNormals, meshTextureCoordinates, meshMaterial);
}

void Model::draw(Shader *shader, Matrix &modelMatrix) {
    for (Mesh *mesh : meshes) {
        mesh->draw(shader, modelMatrix);
    }
}
