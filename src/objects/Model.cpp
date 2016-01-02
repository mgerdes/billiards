#include "Model.h"

Model::Model(string fileName, Shader &shader) {
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(fileName.c_str(), aiProcess_Triangulate);

    if (!scene) {
        Util::log(Severity::ERROR, "Cannot open scene file: " + fileName);
        return;
    }

    printf("%d\n", scene->mNumAnimations);

    Util::log(Severity::INFO, "Loading model: " + fileName);
    Util::log(Severity::INFO, std::to_string(scene->mNumAnimations) + " animations");
    Util::log(Severity::INFO, std::to_string(scene->mNumCameras) + " cameras");
    Util::log(Severity::INFO, std::to_string(scene->mNumLights) + " lights");
    Util::log(Severity::INFO, std::to_string(scene->mNumMaterials) + " materials");
    Util::log(Severity::INFO, std::to_string(scene->mNumMeshes) + " meshes");
    Util::log(Severity::INFO, std::to_string(scene->mNumTextures) + " textures");

    this->processNode(scene->mRootNode, scene, shader);

    Util::log(Severity::INFO, "Finished loading model: " + fileName);
}

void Model::processNode(aiNode *node, const aiScene *scene, Shader &shader) {
    for (int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene, shader));
    }

    for (int i = 0; i < node->mNumChildren; i++) {
        this->processNode(node->mChildren[i], scene, shader);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene, Shader &shader) {
    vector<Vector> meshVertices;
    vector<Vector> meshNormals;

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

    Vector ambientColor, diffuseColor, specularColor;

    // Process material
    if (mesh->mMaterialIndex >= 0) {
        aiString path;
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        aiColor4D color;
        aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &color);
        diffuseColor = Vector(color.r, color.g, color.b);

        aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &color);
        ambientColor = Vector(color.r, color.g, color.b);

        aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &color);
        specularColor = Vector(color.r, color.g, color.b);
    } else {
        Util::log(INFO, "A mesh was processed with no material.");
    }

    Material meshMaterial = Material(ambientColor, diffuseColor, specularColor, 0.0);

    return Mesh(meshVertices, meshNormals, meshMaterial, shader);
}

void Model::draw() {
    for (Mesh mesh : meshes) {
        mesh.draw();
    }
}
