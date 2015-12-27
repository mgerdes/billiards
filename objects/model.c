#include "model.h"

static Mesh* process_mesh(struct aiMesh* mesh, struct aiScene* scene) {
    Vertex **vertices = malloc(sizeof(Vertex *) * mesh->mNumVertices);
    for (int i = 0; i < mesh->mNumVertices; i++) {
        vertices[i] = malloc(sizeof(Vertex));
    }

    // Process vertices
    if (mesh->mVertices && mesh->mNumVertices > 0) {
        for (int i = 0; i < mesh->mNumVertices; i++) {
            struct aiVector3D position = mesh->mVertices[i];
            vertices[i]->position = create_vec(position.x, position.y, position.z, 1.0);
        }
    } else {
        gl_log(INFO, "A mesh was processed with no vertices.");
    }

    // Process normals
    if (mesh->mNormals) {
        for (int i = 0; i < mesh->mNumVertices; i++) {
            struct aiVector3D normal = mesh->mNormals[i];
            vertices[i]->normal = create_vec(normal.x, normal.y, normal.z, 1.0);
        }
    } else {
        gl_log(INFO, "A mesh was processed with no normals.");
    }

    // Process texture coords
    if (mesh->mTextureCoords[0]) {
        for (int i = 0; i < mesh->mNumVertices; i++) {
            struct aiVector3D texture = mesh->mTextureCoords[0][i];
            vertices[i]->texture_coords = create_vec(texture.x, texture.y, texture.z, 1.0);
        }
    } else {
        for (int i = 0; i < mesh->mNumVertices; i++) {
            vertices[i]->texture_coords = 0;
        }
        gl_log(INFO, "A mesh was processed with no texture coordinates.");
    }

    // Process material
    Texture* mesh_texture = malloc(sizeof(Texture));
    Material* mesh_material = malloc(sizeof(Material));
    if (mesh->mMaterialIndex >= 0) {
        struct aiString path;
        struct aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        aiGetMaterialTexture(material, aiTextureType_DIFFUSE, 0, &path, 0, 0, 0, 0, 0, 0);
        mesh_texture->id = create_texture(path.data);

        struct aiColor4D color;
        aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &color);
        mesh_material->diffuse_color = create_vec(color.r, color.g, color.b, color.a);

        aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &color);
        mesh_material->ambient_color = create_vec(color.r, color.g, color.b, color.a);

        aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &color);
        mesh_material->specular_color = create_vec(color.r, color.g, color.b, color.a);
    } else {
        gl_log(INFO, "A mesh was processed with no material.");
    }

    return create_mesh(vertices, mesh->mNumVertices, mesh_texture, mesh_material);
}

static void process_node(Model* model, struct aiNode* node, struct aiScene* scene) {
    for (int i = 0; i < node->mNumMeshes; i++) {
        struct aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        model->meshes[node->mMeshes[i]] = process_mesh(mesh, scene);
    }

    for (int i = 0; i < node->mNumChildren; i++) {
        process_node(model, node->mChildren[i], scene);
    }
}

Model* create_model(char* filename, GLint shader_program) {
    struct aiScene* scene = aiImportFile(filename, aiProcess_Triangulate);
    if (!scene) {
        gl_log(ERROR, "Cannot open scene file: %s", filename);
        return 0;
    }

    gl_log(INFO, "Loading model: %s", filename);
    gl_log(INFO, "%d animations", scene->mNumAnimations);
    gl_log(INFO, "%d cameras", scene->mNumCameras);
    gl_log(INFO, "%d lights", scene->mNumLights);
    gl_log(INFO, "%d materials", scene->mNumMaterials);
    gl_log(INFO, "%d meshes", scene->mNumMeshes);
    gl_log(INFO, "%d textures", scene->mNumTextures);

    Model* model = malloc(sizeof(Model));
    model->num_meshes = scene->mNumMeshes;
    model->meshes = malloc(sizeof(Mesh*) * scene->mNumMeshes);
    model->shader_program = shader_program;
    model->model_mat = identity_mat();

    process_node(model, scene->mRootNode, scene);

    return model;
}

void draw_model(Model* model) {
    GLint light_position = glGetUniformLocation(model->shader_program, "light.position");
    GLint light_ambient = glGetUniformLocation(model->shader_program, "light.ambient_color");
    GLint light_diffuse = glGetUniformLocation(model->shader_program, "light.diffuse_color");
    GLint light_specular = glGetUniformLocation(model->shader_program, "light.specular_color");
    GLint model_mat_position = glGetUniformLocation(model->shader_program, "model_mat");
    GLint camera_position = glGetUniformLocation(model->shader_program, "camera_position");

    glUniform3f(light_position, 0.0, 100.0, 0.0);
    glUniform3f(light_ambient, 1.0f, 1.0f, 1.0f);
    glUniform3f(light_diffuse, 1.0f, 1.0f, 1.0f);
    glUniform3f(light_specular, 1.0f, 1.0f, 1.0f);
    glUniformMatrix4fv(model_mat_position, 1, GL_FALSE, model->model_mat->m);
    glUniform3f(camera_position, 1.0f, 1.0f, 1.0f);

    for (int i = 0; i < model->num_meshes; i++) {
        draw_mesh(model->meshes[i], model->shader_program);
    }
}
